/*
 * calibrationGimbal.cpp
 *
 *  Created on: Jul 21, 2014
 *      Author: Luis Ariel Valbuena Reyes
 *
 */
#include <iostream>
#include <string.h>
#include <math.h>

#include "driver_pwm_motor.h"
//#include "driver_tty_port.h"
#include "driver_gimbal.h"
#include "ViconGumstix.h"

#define N_ITERATIONS 51

int main()
{
	std::cout <<"Hola Mundo"<<std::endl;

	double x,y,z,p,q,r;
	double x_c,y_c,z_c,p_c,q_c,r_c;
	double x_goal=0,y_goal=0,z_goal=0;
	double tmpx=0,tmpy=0,tmpz=0;

	driver_gimbal *g = new driver_gimbal(PI/2,PI/2); //Angles to the gimbal in radians
	sleep(3);
	g->updatePosition(0.0,0.0);
	sleep(3);
//	g->updatePosition(0.0,PI/2);
//	sleep(1);

	ViconGumstix *v = new  ViconGumstix();

//	for(int a=0;a<22;a++)
//	{
		v->update();
	
		v->returnSubjectPos("quadrotor_2b",x,y,z,p,q,r);	//reported angles in degrees
		std::cout<<"InfoQuadrotor x= "<<x<<", y= "<<y<<", z="<<z<<", p="<<p<<", q="<<q<<", r="<<r<<std::endl;
	
		g->updateRotMat(p,q,r);
		g->point2PositionGoal(x_goal,y_goal,z_goal,x,y,z);
//	}
	sleep(1);
	g->updatePosition(0.0,89*(PI/180));
	sleep(1);


	int p_phi= 3000;
	int p_psi= 3000;

	g->updatePosition(p_phi,p_psi);
	sleep(1);
	int val2=500;
	int val1=2457;

	char BufferPause[30];

	double InfoQuadrotor[N_ITERATIONS][6];
	double InfoCube[N_ITERATIONS][3];
	double ValRange2[N_ITERATIONS];

	std::cout<<std::endl<<"CALIBRATION PROCESS "<<std::endl<<std::endl;
	for(int aa=0;aa<N_ITERATIONS;aa++)
	{
                std::cout<<"Iteration N = "<<aa<<std::endl;
		val2= 500 +(100*aa);
		g->updatePosition(val1,val2);

		std::cout<<"Go and reposition the cube so it gets aligned with the laser and then hit ENTER...";
		fgets (BufferPause, 30, stdin);		

		v->update();

                v->returnSubjectPos("CalibrationCube",x_c,y_c,z_c,p_c,q_c,r_c);        //reported angles in degrees
                std::cout<<"InfoCube x= "<<x_c<<", y= "<<y_c<<", z="<<z_c<<", p="<<p_c<<", q="<<q_c<<", r="<<r_c<<std::endl;
                v->returnSubjectPos("quadrotor_2b",x,y,z,p,q,r);//reported angles in degrees
                std::cout<<"InfoQuadrotor x= "<<x<<", y= "<<y<<", z="<<z<<", p="<<p<<", q="<<q<<", r="<<r<<std::endl<<std::endl;

                InfoQuadrotor[aa][0]=x;
                InfoQuadrotor[aa][1]=y;
                InfoQuadrotor[aa][2]=z;
                InfoQuadrotor[aa][3]=p;
                InfoQuadrotor[aa][4]=q;
                InfoQuadrotor[aa][5]=r;

        	InfoCube[aa][0]=x_c;
                InfoCube[aa][1]=y_c;
                InfoCube[aa][2]=z_c;

		ValRange2[aa]=val1;
	}

	std::cout<<std::endl<<"The consigned data was ..."<<std::endl;

        std::cout<<std::endl<<"InfoQuadrotor = [ "<<std::endl;
        for(int aa=0;aa<N_ITERATIONS;aa++)
        {
                for(int bb=0; bb<6; bb++)
		{
			std::cout<<InfoQuadrotor[aa][bb]<<" ";
		}
		std::cout<<";"<<std::endl;
        }
        std::cout<<std::endl<<"];"<<std::endl;

        std::cout<<std::endl<<"InfoCube = [ "<<std::endl;
        for(int aa=0;aa<N_ITERATIONS;aa++)
        {
                for(int bb=0; bb<3; bb++)             
                {
                        std::cout<<InfoCube[aa][bb]<<" "; 
                }
                std::cout<<";"<<std::endl;
        }
        std::cout<<std::endl<<"];"<<std::endl;

        std::cout<<std::endl<<"ValRange2 = [ "<<std::endl;
        for(int aa=0;aa<N_ITERATIONS;aa++)
        {
                        std::cout<<ValRange2[aa]<<";"<<std::endl;
        }
        std::cout<<std::endl<<"];"<<std::endl;





/*
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
