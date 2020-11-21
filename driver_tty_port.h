/*
 * driver_tty_port.h
 *
 *  Created on: Jul 21, 2014
 *      Author: Luis Ariel Valbuena Reyes
 *
 */
#ifndef DRIVER_TTY_PORT_H_
#define DRIVER_TTY_PORT_H_

#include <iostream>
#include <string.h>
#include <sstream>

class driver_tty_port
{
	std::string Port;
	std::string PathRoute;
    public:
	driver_tty_port(const std::string & Port, int speed);
	~driver_tty_port();

	void transmit_Info(const std::string & Info);
	void transmit_Info(int Character);	
	void transmit_Info(char Character);
	void transmit_Info(char * ArrayI, int n);

	std::string get_Info();
};

#endif
