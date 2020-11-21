/*
 * driver_gimbal.h
 *
 *  Created on: Jul 21, 2014
 *      Author: Luis Ariel Valbuena Reyes
 *
 */
#ifndef DRIVER_GIMBAL_H_
#define DRIVER_GIMBAL_H_

#define PI 3.14159265359
#define L_STRING 13
#define OFF_AXIS_1 -9.66
#define OFF_AXIS_2  6.00
#define OFF_AXIS_3 -122.61
#define SQRT_1_2  0.707106781186547

#include "driver_tty_port.h"

class driver_gimbal
{
	driver_tty_port *CommS;
  public:

	double R_abs_rel[3][3];


	driver_gimbal(double phi,double psi);//phi -> first joint, psi -> second joint.
	~driver_gimbal();

	void updatePosition(double phi,double psi);
	void updatePosition(int ValRange1,int ValRange2);//values from 500 to 5500.
	void point2PositionGoal(double xg,double yg, double zg,double xr,double yr,double zr);//global coordinates.
	std::string turnIntoBinary(int Number);
	int turnIntoRange(double angle);
	char returnCastedByte(std::string string);

	int calculateValue_Phi(double phi);
	int calculateValue_Psi(double psi);

	void updateRotMat(double alpha,double beta,double theta);
	void absVector2relVector(double &x,double &y, double &z, double &rx, double &ry, double &rz );
};

#endif
