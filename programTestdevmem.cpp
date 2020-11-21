/*
 * programTestdevmem.cpp 
 *
 *  Created on: Jul 21, 2014
 *      Author: Luis Ariel Valbuena Reyes
 *
 */
#include <iostream>
#include <string.h>
#include <math.h>

#include "driver_pwm_motor.h"
//#include "driver_gpio.h"
//#include "driver_tty_port.h"
#include "driver_gimbal.h"
#include "ViconGumstix.h"

int main()
{
	std::cout <<"Hola Mundo"<<std::endl;

	double x,y,z,p,q,r;
	double x_goal=0,y_goal=0,z_goal=0;
	double tmpx=0,tmpy=0,tmpz=0;

	driver_gimbal *g = new driver_gimbal(-PI/2,PI/2); //Angles to the gimbal in radians

	sleep(3);
	g->updatePosition(0.0,0.0);
	sleep(3);
	g->updatePosition(-PI/2,PI/2);
	
	sleep(1);

	ViconGumstix *v = new  ViconGumstix();

	for(int a=0;a<2200;a++)
	{
		v->update();
	
		v->returnSubjectPos("quadrotor_2b",x,y,z,p,q,r);	//reported angles in degrees
//		std::cout<<"doubles x= "<<x<<", y= "<<y<<", z="<<z<<", p="<<p<<", q="<<q<<", r="<<r<<std::endl;
	
		g->updateRotMat(p,q,r);
		g->point2PositionGoal(x_goal,y_goal,z_goal,x,y,z);
	}
	sleep(1);
	g->updatePosition(0.0,PI/2);
	sleep(1);


/*
	int p_phi= 3000;
	int p_psi= 3000;

	g->updatePosition(p_phi,p_psi);


	int Angle_PHI[]= {960,1274,1589,1903,2218,2532,2847,3161,3476,3790,4105,4420};
	int Angle_PSI[]={1020,1339,1658,1977,2296,2615,2934,3253,3572,3891,4210,4530};
	sleep(5);
	for(int aa=0;aa<12;aa++)
	{
		g->updatePosition(Angle_PHI[aa],2600);
		sleep(8);
	}
	for(int aa=0;aa<12;aa++)
	{
		g->updatePosition(4420,Angle_PSI[aa]);
		sleep(8);
	}
*/

//	driver_gimbal *g= new driver_gimbal(0,PI/2);
/*
	driver_tty_port *SerialPort=new driver_tty_port("0",9600);

	char Letter[]={128,1};

	SerialPort->transmit_Info(Letter,2);

*/
//	char LetterA=1;
//	SerialPort->transmit_Info(LetterA);
//	SerialPort->transmit_Info("A");
/*
	setup_PWM10(100);	
	setup_PWM11(100);

	sleep(1);
	
	updatePWM10_DutyCycle(30);
	updatePWM11_DutyCycle(60);

	sleep(5);

	updatePWM11_DutyCycle(30);
	updatePWM10_DutyCycle(60);

	sleep(5);

	updatePWM10_DutyCycle(30);
	updatePWM11_DutyCycle(60);

	sleep(5);

	updatePWM10_DutyCycle(0);
	updatePWM11_DutyCycle(0);
	
	sleep(1);
	int b=0;
	for(int a=0;a<=60;a++)
	{
		b= int( 24 + (5*sin(2*PI*(a/(120.0))) ) );
		updatePWM10_DutyCycle(b);
		updatePWM11_DutyCycle(b);
		sleep(1);
	}

	updatePWM10_DutyCycle(0);
	updatePWM11_DutyCycle(0);

	sleep(1);
*/
	return 0;
}
