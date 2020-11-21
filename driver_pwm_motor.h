/*
 * driver_pwm_motor.h
 *
 *  Created on: Jul 21, 2014
 *      Author: Luis Ariel Valbuena Reyes
 *
 */
#ifndef DRIVER_PWM_MOTOR_H_
#define DRIVER_PWM_MOTOR_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include <string.h>
#include <sstream>
#include <errno.h>
#include <signal.h>
#include <fcntl.h>
#include <ctype.h>
#include <termios.h>
#include <sys/types.h>
#include <sys/mman.h>

#define FATAL do {fprintf(stderr, "Error at line %d, file %s (%d) [%s]\n", \
  __LINE__, __FILE__, errno, strerror(errno)); exit(1); } while(0)

#define PWM10_TCLR "0x48086024"
#define CONTROL_PADCONF_UART2_CTS "0x48002176"
#define PWM10_TLDR "0x4808602C"
#define PWM10_TMAR "0x48086038"
#define PWM10_TCRR "0x48086028"

#define PWM11_TCLR "0x48088024"
#define CONTROL_PADCONF_UART2_TX "0x48002178"
#define PWM11_TLDR "0x4808802C"
#define PWM11_TMAR "0x48088038"
#define PWM11_TCRR "0x48088028"

#define MAP_SIZE 4096UL
#define MAP_MASK (MAP_SIZE - 1)
#define MAX_VALUE 4294967295
#define GPTI_FCLK 32000
//#define PI 3.14159265359

extern unsigned long NumSettings_pwm10;
extern unsigned long NumSettings_pwm11;
extern unsigned long TLDR_pwm10;
extern unsigned long TLDR_pwm11;

int devmem2(const std::string &,int ,const std::string &);
void setup_PWM10(double);
void clean_PWM10();
void updatePWM10_DutyCycle(int);
void setup_PWM11(double);
void clean_PWM11();
void updatePWM11_DutyCycle(int);
std::string ulong2hexaString(unsigned long);

#endif
