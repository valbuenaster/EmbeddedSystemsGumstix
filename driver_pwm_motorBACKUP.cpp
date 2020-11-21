/*
 * driver_pwm_motorBACKUP.cpp
 *
 *  Created on: Jul 21, 2014
 *      Author: Luis Ariel Valbuena Reyes
 *
 */
#include "driver_pwm_motor.h"

unsigned long NumSettings_pwm10=0;
unsigned long NumSettings_pwm11=0;
unsigned long TLDR_pwm10=0;
unsigned long TLDR_pwm11=0;

int devmem2(const std::string& target,const std::string& access_type,const std::string& writeval)
{
	std::string Array;
	
	Array.append("devmem2 ");
	Array.append(target);
	Array.append(" ");
	Array.append(access_type);
	Array.append(" ");
	Array.append(writeval);

	std::cout<<"string to write "<<Array<<std::endl; 

	return system(Array.data());
}

void setup_PWM10(double frequency)
{
	int a;
	unsigned long TLDR;
	unsigned long ratio=(ulong)(GPTI_FCLK/frequency);
	TLDR_pwm10 = MAX_VALUE - ratio + 1;
	NumSettings_pwm10=MAX_VALUE - TLDR_pwm10;
	
	std::stringstream stream;
	stream<<"0x"<<std::hex<<TLDR_pwm10;
	std::string string_TLDR(stream.str());

	a=devmem2(PWM10_TCLR,"w","0"); //clean the buffer
	a=devmem2(CONTROL_PADCONF_UART2_CTS,"h","0x0002");//select the timer to be pwm
	a=devmem2(PWM10_TLDR,"w",string_TLDR);//set the frequency
	a=devmem2(PWM10_TMAR,"w",string_TLDR);//set the duty cycle -> 0
	a=devmem2(PWM10_TCRR,"w",string_TLDR);//prime the timer for the first cycle
	a=devmem2(PWM10_TCLR,"w","0x01843");//starts the pwm
}

void updatePWM10_DutyCycle(int dutyCycle)
{
	int a;
	unsigned long ratio= (ulong)((NumSettings_pwm10*dutyCycle)/(100));
	unsigned long TMAR= TLDR_pwm10 + ratio;

	std::stringstream stream;
	stream<<"0x"<<std::hex<<TMAR;
	std::string string_TMAR(stream.str());
	
	a=devmem2(PWM10_TMAR,"w",string_TMAR);
}

void setup_PWM11(double frequency)
{
	int a;
	unsigned long TLDR;
	unsigned long ratio=(ulong)(GPTI_FCLK/frequency);
	TLDR_pwm11= MAX_VALUE - ratio + 1;
	NumSettings_pwm11= MAX_VALUE - TLDR_pwm11;

	std::stringstream stream;
	stream<<0x"<<std::hex<<TLDR_pwm11;
	std::string string_TLDR(stream.str());

	a=devmem2(PWM11_TCLR,"w","0");
	a=devmem2(CONTROL_PADCONF_UART2_TX,"h","0x0002");
	a=devmem2(PWM11_TLDR,"w",string_TLDR);
	a=devmem2(PWM11_TMAR,"w",string_TLDR);
	a=devmem2(PWM11_TCRR,"w",string_TLDR);
	a=devmem2(PWM11_TCLR,"w","0x01843");
}

void updatePW11_DutyCycle(int dutyCycle)
{
	unsigned long ratio = (ulong)((NumSettings_pwm11*dutyCycle)/(100));
	unsigned long Base
}

std::string ulong2hexaString(unsigned long value)
{
}
