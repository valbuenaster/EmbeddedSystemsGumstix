/*
 * driver_gpio.h
 *
 *  Created on: Jul 21, 2014
 *      Author: Luis Ariel Valbuena Reyes
 *
 */
#ifndef DRIVER_GPIO_H_
#define DRIVER_GPIO_H_

#define ROUTEPORT "/sys/class/gpio"

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <unistd.h>

void setGPIO_PORT144();
void setGPIO_PORT_INPUT144();
void setGPIO_PORT_OUTPUT144();
void setGPIO_PORT_VALUE144(int value);

void setGPIO_PORT147();
void setGPIO_PORT_INPUT147();
void setGPIO_PORT_OUTPUT147();
void setGPIO_PORT_VALUE147(int value);
#endif
