/*
 * panzer.h
 *
 *  Created on: Jul 21, 2014
 *      Author: Luis Ariel Valbuena Reyes
 *
 */
#ifndef PANZER_H_
#define PANZER_H_

#define PWM_FREQ 500
#define R 26.52
#define L1 80.00
#define L 126.6
#define LIM_A 1219.2
#define LIM_B 1219.2
#define NORM_DIM 862.1
#define N 4
#define VEL_MAX 0.42
#define VEL_MIN 0.1
#define PI 3.14159265359

#include "ViconGumstix.h"

class panzer
{

  public:
	int directionLeft; 		// 1 for positive dir, 0 for negative dir.
	int directionRight; 		//1 for positive dir, 0 for negative dir.
	int prev_directionLeft; 	// previous state of direction
	int prev_directionRight;	// if it changes, it is required to put the pwm's to 0
	ViconGumstix *v; 
	double magRight;
	double magLeft;

	panzer();
	~panzer();

	void setVel(double rightTread, double leftTread);// ranges from -1 to 1, THIS SHOULD BE PRIVATE
	void setVelocity(double rightTread, double leftTread);// ranges from +-0.1 to +-0.42 m/s
	void navigate2Point(double x_goal, double y_goal);
	double velocityScaling(double x, double y, double x_goal, double y_goal);
};

#endif
