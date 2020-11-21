/*
 * panzer.cpp
 *
 *  Created on: Jul 21, 2014
 *      Author: Luis Ariel Valbuena Reyes
 *
 */
#include <math.h>
#include "panzer.h"
#include <cmath>
#include "driver_pwm_motor.h"
#include "driver_gpio.h"
#include <unistd.h>

panzer::panzer()
{
	directionLeft = 1;
	directionRight = 1;
	prev_directionLeft = directionLeft;
	prev_directionRight = directionRight;
	this->v=new ViconGumstix();

	magLeft = 0;
	magRight = 0;

	setGPIO_PORT147();
	setGPIO_PORT_OUTPUT147();   //Enabling gpio147 and set it to logic 0.
	setGPIO_PORT_VALUE147(directionLeft);

	setGPIO_PORT_VALUE144(directionRight);  //gpio144 is enabled by default as output, set it to logic 0

	clean_PWM10();
	clean_PWM11();

//	setup_PWM10(300);
//	setup_PWM11(300);
}

panzer::~panzer()
{
}

void panzer::setVel(double rightTread, double leftTread)//values between -1 and 1.
{
//	std::cout<<"DATOS QUE LLEGAN ... "<<rightTread<<" "<<leftTread<<std::endl;
	int dutyRight = 0;
	int dutyLeft = 0;

	if(fabs(rightTread) > 1.0)
	{
		std::cout<<"rightTread value outside of range..."<<std::endl;
	}else{
		if(rightTread >= 0.0)
		{
			directionRight = 1;
		}else{
			directionRight = 0;
		}
		magRight = fabs(rightTread);
//		std::cout<<"ENTRA AQUI 1 "<<magRight<<std::endl;
	}

	if(fabs(leftTread) > 1.0)
	{
		std::cout<<"leftTread value outside of range..."<<std::endl;
	}else{
		if(leftTread >= 0.0)
		{
			directionLeft = 1;
		}else{
			directionLeft = 0;
		}
		magLeft = fabs(leftTread);
//		std::cout<<"ENTRA AQUI 2 "<<magLeft<<std::endl;
	}

	if( directionRight!=prev_directionRight )
	{
		clean_PWM10();
		//Put the direction command here! gpio144		
		setGPIO_PORT_VALUE144(directionRight);
		usleep(1000);
	}
	
	if( directionLeft!=prev_directionLeft)
	{
		clean_PWM11();
		//Put the direction command here! gpio147
		setGPIO_PORT_VALUE147(directionLeft);
		usleep(1000);
	}
	setup_PWM10(PWM_FREQ);
	setup_PWM11(PWM_FREQ);
	
//	std::cout<<"magRight "<<magRight<<" magLeft "<<magLeft<<std::endl;
	dutyRight = (int)(100*magRight);
	dutyLeft = (int)(100*magLeft);

//	std::cout<<"DUTY RIGHT AND LEFT "<<dutyRight<<" "<<dutyLeft<<std::endl;
	updatePWM10_DutyCycle(dutyRight);
	updatePWM11_DutyCycle(dutyLeft);
	prev_directionLeft = directionLeft;
	prev_directionRight = directionRight;
}

void panzer::setVelocity(double rightTread, double leftTread)
{
	double mapValRight=0.0;
	double mapValLeft=0.0;


	if( (fabs(rightTread) < 0.1) || (fabs(rightTread) > 0.42) )
	{
		std::cout<<"rightTread value on dead zone or outside domain...velocity set to 0"<<std::endl;
	}else{
		if(rightTread > 0.0)
		{
			mapValRight = -(1.0/15)*( ( 0.9/(rightTread - 0.5) ) - 0.12 );
		}else{
			mapValRight = (1.0/15)*( (-1.0/(rightTread + 0.5)) + 0.11);
		}		
	}
	if( (fabs(leftTread) < 0.1) || (fabs(leftTread) > 0.42) )
	{
		std::cout<<"leftTread value on dead zone or outside domain...velocity set to 0"<<std::endl;
	}else{
		if(leftTread > 0.0)
		{
			mapValLeft = -(1.0/15)*( ( 0.9/(leftTread - 0.5) ) - 0.12 );
		}else{
			mapValLeft = (1.0/15)*( (-1.0/(leftTread + 0.5)) + 0.11); 
		}
	}
	//std::cout<<"Mapped values for right "<<mapValRight<<" and left "<<mapValLeft<<std::endl;
	setVel(mapValRight,mapValLeft);
}

void panzer::navigate2Point(double x_goal, double y_goal)
{
	double Nabla_Varphi_x = 0.0;
	double Nabla_Varphi_y = 0.0;
	double Mag_Nabla_Varphi = 0.0;
	double s_theta = 0.0;
	double c_theta = 0.0;
	double x=0,y=0,z=0,p=0,q=0,theta=0;
        double xM=0,yM=0,zM=0,pM=0,qM=0,thetaM=0;
	double xp=0,yp=0;
	double omega_r=0,omega_l=0;
	double Tran_1=0,Tran_2=0,Tran_3=0,Tran_4=0;
	double scalingVel = 0.0;
	double distanceNorm = 0.0;
	double goal_Orientation = 0.0;

	this->v->update();
        this->v->returnSubjectPos(ROBOT_SUBJECT,x,y,z,p,q,theta);
        this->v->returnSubjectPos("Map_TestBedf",xM,yM,zM,pM,qM,thetaM);

	goal_Orientation = (180/PI)*atan2Mia(y - (y_goal+yM),x - (x_goal+xM));	

	turn_in_Spot(goal_Orientation);

	// A LOOP COMES HERE
	do{
	this->v->update();
	this->v->returnSubjectPos(ROBOT_SUBJECT,x,y,z,p,q,theta);

	s_theta = sin((PI*theta)/180);
	c_theta = cos((PI*theta)/180);
	xp = x + (L1*c_theta);
	yp = y + (L1*s_theta);

	distanceNorm = sqrt( pow(xp - (x_goal+xM),2) + pow(yp - (y_goal+yM),2) );

	Nabla_Varphi_x = N*(1/LIM_A)*pow((xp-(x_goal+xM))/LIM_A,N-1);
	Nabla_Varphi_y = N*(1/LIM_B)*pow((yp-(y_goal+yM))/LIM_B,N-1);
	Mag_Nabla_Varphi = sqrt( pow(Nabla_Varphi_x,2) + pow(Nabla_Varphi_y,2) );

	scalingVel = velocityScaling(xp,yp,x_goal+xM,y_goal+yM);

	Nabla_Varphi_x = scalingVel*(Nabla_Varphi_x/Mag_Nabla_Varphi);
	Nabla_Varphi_y = scalingVel*(Nabla_Varphi_y/Mag_Nabla_Varphi);

	std::cout<<std::endl<<"xp "<<xp<<", yp "<<yp<<", theta "<<theta<<", scalingVel "<<scalingVel<<", NVx "<<Nabla_Varphi_x<<", NVy "<<Nabla_Varphi_y<<std::endl;

	Tran_1 = ( s_theta/2 ) - ( (L1/L)*c_theta );
	Tran_2 = ( c_theta/2 ) + ( (L1/L)*s_theta );
	Tran_3 = ( s_theta/2 ) + ( (L1/L)*c_theta );
	Tran_4 = ( c_theta/2 ) - ( (L1/L)*s_theta );

	omega_r = ( (Nabla_Varphi_x*Tran_1) - (Nabla_Varphi_y*Tran_2) );//(1/R)*(1/L1)*
	omega_l = ( -(Nabla_Varphi_x*Tran_3) + (Nabla_Varphi_y*Tran_4));//(1/R)*(1/L1)*

	std::cout<<"Before windowing, omega_r "<<omega_r<<", omega_l "<<omega_l<<std::endl;

	if( omega_r > 0.0 )
	{
		if( omega_r < VEL_MIN ) omega_r = VEL_MIN;
		if( omega_r > VEL_MAX ) omega_r = VEL_MAX;
	}else{
		if( omega_r > -VEL_MIN ) omega_r = -VEL_MIN;
		if( omega_r < -VEL_MAX ) omega_r = -VEL_MAX;
	}
	if( omega_l > 0.0 )
	{
		if( omega_l < VEL_MIN) omega_l = VEL_MIN;
		if( omega_l > VEL_MAX) omega_l = VEL_MAX;
	}else{
		if( omega_l > -VEL_MIN ) omega_l = -VEL_MIN;
		if( omega_l < -VEL_MAX ) omega_l = -VEL_MAX;
	}
	std::cout<<"After, omega_r "<<omega_r<<", omega_l "<<omega_l<<std::endl;
//	std::cout<<"distance norm "<<distanceNorm<<std::endl;
	this->setVelocity(omega_r,omega_l);
	}while(distanceNorm > 35.0);
	this->setVelocity(0,0);
	sleep(0.1);
	// A LOOP ENDS HERE
}

double panzer::velocityScaling(double x, double y, double x_goal, double y_goal)
{
	return 0.2 + (sqrt( pow(x - x_goal,2) + pow(y - y_goal,2) )/NORM_DIM);
}

void panzer::turn_in_Spot(double goal_Orientation)
{
	double x=0.0,y=0.0,z=0.0,p=0.0,q=0.0,theta=0.0;
	double errorAngle=0.0;

	do{
	        this->v->update();
	        this->v->returnSubjectPos(ROBOT_SUBJECT,x,y,z,p,q,theta);	
		errorAngle = asin( (cos((180/PI)*theta)*sin((180/PI)*goal_Orientation))-(sin((180/PI)*theta)*cos((180/PI)*goal_Orientation)) );
		if( errorAngle > 0.0)
		{
			this->setVelocity(0.25,-0.25);
		}else{
			this->setVelocity(-0.25,0.25);
		}
	}while(fabs(errorAngle)>0.08);
        this->setVelocity(0,0);
        sleep(0.1);
}
