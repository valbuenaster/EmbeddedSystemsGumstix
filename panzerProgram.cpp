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
#include <stdio.h>

#include "panzer.h"
#include "ViconGumstix.h"

int main()
{
	std::cout <<std::endl<<"Panzer program"<<std::endl;

	double x,y,z,p,q,r;
	double x_goal=0,y_goal=0,z_goal=0;
	double tmpx=0,tmpy=0,tmpz=0;
	double normPlanePos=0;
	char Name1[50];
	char Name2[50];
	int n=0;

	panzer *p_robot = new panzer();
	
	p_robot->navigate2Point(0.0,0.0);
/*
	ViconGumstix *v = new ViconGumstix();

	double ttemp=0;
	//put the robot on the lower part of the Vicon cage.
	v->update();
	v->returnSubjectPos("Panzer",x,y,z,p,q,r);
	std::cout<<"Panzer x= "<<x<<", y= "<<y<<", z="<<z<<", p="<<p<<", q="<<q<<", r="<<r<<std::endl;

	FILE *file1;
	FILE *file2;

	for(int aa=2;aa<=2;aa++)
	{
		n=sprintf(Name1,"Velocity_%d_Forwards.txt",aa);
		n=sprintf(Name2,"Velocity_%d_Backwards.txt",aa);

		file1=fopen(Name1,"w");
		fprintf(file1,"Data=[\n");
		ttemp=0.9;
		p_robot->setVel(ttemp,ttemp);

		do{
			v->update();
			v->returnSubjectPos("Panzer",x,y,z,p,q,r);
                        printf("forward %6.4f %6.4f %6.4f %6.4f %6.4f %6.4f;\n",x,y,z,p,q,r);
			//Print to file 1 here
//			fprintf(file1,"%6.4f %6.4f %6.4f %6.4f %6.4f %6.4f;\n",x,y,z,p,q,r);
			normPlanePos = sqrt( pow(x,2) + pow(y,2) );

		}while(x > -800);
		fprintf(file1,"];");
		fclose(file1);
		p_robot->setVel(0.0,0.0);
		sleep(3);

		file2=fopen(Name2,"w");
		fprintf(file2,"Data=[\n");
		ttemp=-ttemp;
		normPlanePos = 0;
		p_robot->setVel(ttemp,ttemp);

		do{
			v->update();
			v->returnSubjectPos("Panzer",x,y,z,p,q,r);
                        printf("backward %6.4f %6.4f %6.4f %6.4f %6.4f %6.4f;\n",x,y,z,p,q,r);
			//Print to file 2 here
			fprintf(file2,"%6.4f %6.4f %6.4f %6.4f %6.4f %6.4f;\n",x,y,z,p,q,r);
			normPlanePos = sqrt( pow(x,2) + pow(y,2) );
		}while(x < 800);
		fprintf(file2,"];");
		fclose(file2);
		normPlanePos = 0;
		p_robot->setVel(0.0,0.0);
		sleep(3);
	}
*/
/*
	for(int aa=10;aa>=0;aa--)
	{
		ttemp=aa/10.0;
		p_robot->setVelocity(ttemp,ttemp);
		sleep(3);
		std::cout<<"VELOCITY : "<<ttemp<<std::endl<<std::endl;
	}

	p_robot->setVelocity(0.0,0.0);
	sleep(1);


	ViconGumstix *v = new  ViconGumstix();

	for(int a=0;a<2;a++)
	{
		v->update();
	
		v->returnSubjectPos("quadrotor_1b",x,y,z,p,q,r);	//reported angles in degrees
		std::cout<<"doubles x= "<<x<<", y= "<<y<<", z="<<z<<", p="<<p<<", q="<<q<<", r="<<r<<std::endl;
	}

	sleep(1);
*/

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
