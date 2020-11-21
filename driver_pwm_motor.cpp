/*
 * driver_pwm_motor.cpp
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
/*
int devmem2(const std::string& target,const std::string& access_type,const std::string& writeval)
{
	std::string Array;
	
	Array.append("devmem2 ");
	Array.append(target);
	Array.append(" ");
	Array.append(access_type);
	Array.append(" ");
	Array.append(writeval);

//	std::cout<<"string to write "<<Array<<std::endl; 

	return system(Array.data());
}
*/

int devmem2(const std::string& target1,int access_type1,const std::string& writeval1)
{
/*
 * devmem2.c: Simple program to read/write from/to any location in memory.
 *
 *  Copyright (C) 2000, Jan-Derk Bakker (J.D.Bakker@its.tudelft.nl)
 *
 * This software has been developed for the LART computing board
 * (http://www.lart.tudelft.nl/). The development has been sponsored by
 * the Mobile MultiMedia Communications (http://www.mmc.tudelft.nl/)
 * and Ubiquitous Communications (http://www.ubicom.tudelft.nl/)
 * projects.
 * The author can be reached at:
 *  Jan-Derk Bakker
 *  Information and Communication Theory Group
 *  Faculty of Information Technology and Systems
 *  Delft University of Technology
 *  P.O. Box 5031
 *  2600 GA Delft
 *  The Netherlands
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 */
    int fd;
    void *map_base;
    char  *virt_addr; 
    unsigned long read_result;

    off_t target = strtoul(target1.c_str(),0,0);
    int access_type = 'w';
    access_type =  access_type1;
    unsigned long writeval = strtoul(writeval1.c_str(),0,0);

    if((fd = open("/dev/mem", O_RDWR | O_SYNC)) == -1) FATAL;
//    printf("/dev/mem opened.\n"); 
//    fflush(stdout);
    
    /* Map one page */
    map_base = mmap(0, MAP_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, target & ~MAP_MASK);
    if(map_base == (void *) -1) FATAL;
//    printf("Memory mapped at address %p.\n", map_base); 
//    fflush(stdout);
    
    virt_addr =(char *) map_base + (target & MAP_MASK);

    switch(access_type) {
		case 'b':
			read_result = *((unsigned char *) virt_addr);
			break;
		case 'h':
			read_result = *((unsigned short *) virt_addr);
			break;
		case 'w':
			read_result = *((unsigned long *) virt_addr);
			break;
		default:
			fprintf(stderr, "Illegal data type '%c'.\n", access_type);
			exit(2);
	}
//    printf("Value at address 0x%X (%p): 0x%X\n", target, virt_addr, read_result); 
//    fflush(stdout);

    switch(access_type) 
    {
	case 'b':
		*((unsigned char *) virt_addr) = writeval;
		read_result = *((unsigned char *) virt_addr);
		break;
	case 'h':
		*((unsigned short *) virt_addr) = writeval;
		read_result = *((unsigned short *) virt_addr);
		break;
	case 'w':
		*((unsigned long *) virt_addr) = writeval;
		read_result = *((unsigned long *) virt_addr);
		break;
    }
//    printf("Written 0x%X; readback 0x%X\n", writeval, read_result); 
//    fflush(stdout);

	
    if(munmap(map_base, MAP_SIZE) == -1) FATAL;
    close(fd);
    return 0;
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

	a=devmem2(PWM10_TCLR,'w',"0"); //clean the buffer
	a=devmem2(CONTROL_PADCONF_UART2_CTS,'h',"0x0002");//select the timer to be pwm
	a=devmem2(PWM10_TLDR,'w',string_TLDR);//set the frequency
	a=devmem2(PWM10_TMAR,'w',string_TLDR);//set the duty cycle -> 0
	a=devmem2(PWM10_TCRR,'w',string_TLDR);//prime the timer for the first cycle
	a=devmem2(PWM10_TCLR,'w',"0x01843");//starts the pwm
}

void clean_PWM10()
{
	int a;

	a=devmem2(PWM10_TCLR,'w',"0");
	a=devmem2(CONTROL_PADCONF_UART2_CTS,'h',"0x0002");
}

void updatePWM10_DutyCycle(int dutyCycle)
{
	int a;
	unsigned long ratio= (ulong)((NumSettings_pwm10*dutyCycle)/(100));
	unsigned long TMAR= TLDR_pwm10 + ratio;

	std::stringstream stream;
	stream<<"0x"<<std::hex<<TMAR;
	std::string string_TMAR(stream.str());
	
	a=devmem2(PWM10_TMAR,'w',string_TMAR);
}

void setup_PWM11(double frequency)
{
	int a;
	unsigned long TLDR;
	unsigned long ratio=(ulong)(GPTI_FCLK/frequency);
	TLDR_pwm11= MAX_VALUE - ratio + 1;
	NumSettings_pwm11= MAX_VALUE - TLDR_pwm11;

	std::stringstream stream;
	stream<<"0x"<<std::hex<<TLDR_pwm11;
	std::string string_TLDR(stream.str());

	a=devmem2(PWM11_TCLR,'w',"0");
	a=devmem2(CONTROL_PADCONF_UART2_TX,'h',"0x0002");
	a=devmem2(PWM11_TLDR,'w',string_TLDR);
	a=devmem2(PWM11_TMAR,'w',string_TLDR);
	a=devmem2(PWM11_TCRR,'w',string_TLDR);
	a=devmem2(PWM11_TCLR,'w',"0x01843");
}

void clean_PWM11()
{
	int a;

	a=devmem2(PWM11_TCLR,'w',"0");
	a=devmem2(CONTROL_PADCONF_UART2_TX,'h',"0x0002");
}

void updatePWM11_DutyCycle(int dutyCycle)
{
	int a;
	unsigned long ratio = (ulong)((NumSettings_pwm11*dutyCycle)/(100));
	unsigned long TMAR = TLDR_pwm11 + ratio;

	std::stringstream stream;
	stream<<"0x"<<std::hex<<TMAR;
	std::string string_TMAR(stream.str());

	a=devmem2(PWM11_TMAR,'w',string_TMAR);
}

std::string ulong2hexaString(unsigned long value)
{
}
