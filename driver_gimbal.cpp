/*
 * driver_gimbal.cpp
 *
 *  Created on: Jul 21, 2014
 *      Author: Luis Ariel Valbuena Reyes
 *
 */
#include <math.h>
#include "driver_gimbal.h"
#include <cmath>

driver_gimbal::driver_gimbal(double phi,double psi)//angles in radians from -pi/2 to pi/2
{
	this->CommS= new driver_tty_port("0",38400);

	char ConfArray_One[]={128,1,0,0,87};
	this->CommS->transmit_Info(ConfArray_One,5);

	char ConfArray_Two[]={128,1,0,1,87};
	this->CommS->transmit_Info(ConfArray_Two,5);
	
	this->updatePosition(phi,psi);

	for(int aa=0;aa<3;aa++)
	{
		for(int bb=0;bb<3;bb++)
		{
			this->R_abs_rel[aa][bb]=0.0;
		}
	}
}

driver_gimbal::~driver_gimbal()
{
}

std::string driver_gimbal::turnIntoBinary(int Number)
{
	char bufferBin[L_STRING];
	int Nc=Number;
	int ratioTemp=0;

	for(int a= L_STRING - 1;a>=0;a--)
	{
		ratioTemp= Nc/(pow(2,a));
		if(ratioTemp==1)
		{
			bufferBin[L_STRING - a -1]='1';
			Nc=Nc-pow(2,a);
		}else{
			bufferBin[L_STRING - a - 1]='0';
		}
	}
	//std::cout<<"Converted number "<<Number<<" into "<<bufferBin<<std::endl;
	std::string returnValue(bufferBin);
	return returnValue;
}

int driver_gimbal::turnIntoRange(double angle)
{
	double ratio=(5*angle)/PI;
	double v= 1000*(ratio + 3);

	if(v>5500)
	{
	     	v=5500;
		std::cout<<"Parameter exceeded range"<<std::endl;	
	}
	if(v<500)
	{
		v=500;
		std::cout<<"Parameter under the range"<<std::endl;
	}

	return (int)v;
}

char driver_gimbal::returnCastedByte(std::string string)
{
	//std::cout<<"Segmented string "<<string<<std::endl;
	double Value=0;
	int bound = string.size();
	double PPower=0;

	for(int a=bound-1; a>=0;a--)
	{
		if(string[bound -1 - a]=='1')
		{
			PPower=pow(2,a);
			Value=Value + PPower;
		}
	}

	return (char)Value;
}

void driver_gimbal::updatePosition(int ValRange1,int ValRange2)
{
	char upper_phi=0;
	char lower_phi=0;
	char upper_psi=0;
	char lower_psi=0;

        std::cout<<"ValRange1 = "<<ValRange1<<" ValRange2 = "<<ValRange2<<std::endl;

	std::string bin_phi(this->turnIntoBinary(ValRange1));
	std::string bin_psi(this->turnIntoBinary(ValRange2));

	upper_phi=this->returnCastedByte(bin_phi.substr(0,6));
	lower_phi=this->returnCastedByte(bin_phi.substr(6));
	upper_psi=this->returnCastedByte(bin_psi.substr(0,6));
	lower_psi=this->returnCastedByte(bin_psi.substr(6));

//	std::cout<<"upper_phi: "<<(int)upper_phi<<" ,lower_phi: "<<(int)lower_phi<<", upper_psi: "<<(int)upper_psi<<", lower_psi: "<<(int)lower_psi<<std::endl;
	char ConfArrayPhi[]={128,1,4,0,upper_phi,lower_phi};
	this->CommS->transmit_Info(ConfArrayPhi,6);

	char ConfArrayPsi[]={128,1,4,1,upper_psi,lower_psi};
	this->CommS->transmit_Info(ConfArrayPsi,6);
}

void driver_gimbal::updatePosition(double phi, double psi)//angles in radians from -pi/2 to pi/2
{
	int int_phi=calculateValue_Phi(phi);
	int int_psi=calculateValue_Psi(psi);
	char upper_phi=0;
	char lower_phi=0;
	char upper_psi=0;
	char lower_psi=0;

	std::cout<<"Angle phi=  "<< int_phi <<", Angle psi=  "<< int_psi << std::endl;

	std::string bin_phi(this->turnIntoBinary(int_phi));
	std::string bin_psi(this->turnIntoBinary(int_psi));

	upper_phi=this->returnCastedByte(bin_phi.substr(0,6));
	lower_phi=this->returnCastedByte(bin_phi.substr(6));
	upper_psi=this->returnCastedByte(bin_psi.substr(0,6));
	lower_psi=this->returnCastedByte(bin_psi.substr(6));

//	std::cout<<"upper_phi: "<<(int)upper_phi<<", lower_phi: "<<(int)lower_phi<<", upper_psi: "<<(int)upper_psi<<", lower_psi: "<<(int)lower_psi<<std::endl;

	char ConfArrayPhi[]={128,1,4,0,upper_phi,lower_phi};
	this->CommS->transmit_Info(ConfArrayPhi,6);
	
	char ConfArrayPsi[]={128,1,4,1,upper_psi,lower_psi};
	this->CommS->transmit_Info(ConfArrayPsi,6);
}

void driver_gimbal::point2PositionGoal(double xg, double yg, double zg, double xr, double yr, double zr)
{
 double relVect_x = R_abs_rel[0][0]*OFF_AXIS_1 + R_abs_rel[0][1]*OFF_AXIS_2 + R_abs_rel[0][2]*OFF_AXIS_3;
 double relVect_y = R_abs_rel[1][0]*OFF_AXIS_1 + R_abs_rel[1][1]*OFF_AXIS_2 + R_abs_rel[1][2]*OFF_AXIS_3;
 double relVect_z = R_abs_rel[2][0]*OFF_AXIS_1 + R_abs_rel[2][1]*OFF_AXIS_2 + R_abs_rel[2][2]*OFF_AXIS_3;

 double v_rel_x = xg - xr - relVect_x;
 double	v_rel_y = yg - yr - relVect_y;
 double	v_rel_z = zg - zr - relVect_z;

 double v_rel_End_Effector_x = -SQRT_1_2*(R_abs_rel[0][0]*v_rel_x - R_abs_rel[0][1]*v_rel_x + R_abs_rel[1][0]*v_rel_y - R_abs_rel[1][1]*v_rel_y + R_abs_rel[2][0]*v_rel_z - R_abs_rel[2][1]*v_rel_z);
 double v_rel_End_Effector_y =  SQRT_1_2*(R_abs_rel[0][0]*v_rel_x + R_abs_rel[0][1]*v_rel_x + R_abs_rel[1][0]*v_rel_y + R_abs_rel[1][1]*v_rel_y + R_abs_rel[2][0]*v_rel_z + R_abs_rel[2][1]*v_rel_z);
 double v_rel_End_Effector_z = - R_abs_rel[0][2]*v_rel_x - R_abs_rel[1][2]*v_rel_y - R_abs_rel[2][2]*v_rel_z;

 double Magnitude= sqrt(pow(v_rel_End_Effector_x,2) + pow(v_rel_End_Effector_y,2) + pow(v_rel_End_Effector_z,2) );
 double sign_Ang_1= (v_rel_End_Effector_x*v_rel_End_Effector_y)/std::abs(v_rel_End_Effector_x*v_rel_End_Effector_y);
 double sign_Ang_2= -(v_rel_End_Effector_y)/std::abs(v_rel_End_Effector_y);

 double angle1=sign_Ang_1*atan2(std::abs(v_rel_End_Effector_x),std::abs(v_rel_End_Effector_y));
 double angle2=sign_Ang_2*acos(v_rel_End_Effector_z/Magnitude);

 updatePosition(angle1,angle2);
}

int driver_gimbal::calculateValue_Phi(double phi)
{
	double phi_f = - phi; //this is to fix the angle according to the proper coordinate system
	double phi_2 = phi_f*phi;
	double phi_3 = phi_f*phi_2;
	double phi_4 = phi_f*phi_3;
	double phi_5 = phi_f*phi_4;
	double P_phi = (9.825*phi_5) + (36.074*phi_4) + (-24.022*phi_3) + (-20.734*phi_2) + (-1143.982*phi_f) +   2526.367;
	//The previous is a regression to correctly match an angle with a discrete
	//value of the polulu card.
	return (int)P_phi;
}

int driver_gimbal::calculateValue_Psi(double psi)
{
	double psi_2 = psi*psi;
	double psi_3 = psi*psi_2;
	double psi_4 = psi*psi_3;
	double psi_5 = psi*psi_4;
	double P_psi = (-9.956*psi_5) + ( 13.028*psi_4) + ( 58.822*psi_3) + ( 5.575*psi_2) + (1042.237*psi) + 2705.448;
	//The previous is a regression with the same porpused expressed before

	return (int)P_psi;
}


void driver_gimbal::updateRotMat(double alpha,double beta,double theta)
{
	double sa,ca,sb,cb,st,ct;

	sa = sin((PI/180)*alpha);
	ca = cos((PI/180)*alpha);

	sb = sin((PI/180)*beta);
	cb = cos((PI/180)*beta);

	st = sin((PI/180)*theta);
	ct = cos((PI/180)*theta);

	R_abs_rel[0][0]=  cb*ct;
        R_abs_rel[0][1]= -cb*st;
        R_abs_rel[0][2]=  sb;
        R_abs_rel[1][0]=  (ca*st) + (ct*sa*sb);
        R_abs_rel[1][1]=  (ca*ct) - (sa*sb*st);
        R_abs_rel[1][2]= -cb*sa;
        R_abs_rel[2][0]=  (sa*st) - (ca*ct*sb);
        R_abs_rel[2][1]=  (ct*sa) + (ca*sb*st);
        R_abs_rel[2][2]= ca*cb;

/*
	std::cout<<"Rotation Matrix"<<std::endl;
        for(int aa=0;aa<3;aa++)
        {
                for(int bb=0;bb<3;bb++)
                {
                        std::cout<<this->R_abs_rel[aa][bb]<<" ";
                }
	std::cout<<" "<<std::endl;
        }
*/
}
