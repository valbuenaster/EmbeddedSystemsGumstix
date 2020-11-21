/*
 * ViconGumstix.h
 *
 *  Created on: Jul 21, 2014
 *      Author: Luis Ariel Valbuena Reyes
 *
 */
#ifndef VICONGUMSTIX_H_
#define VICONGUMSTIX_H_

#include "class_socket.h"

class ViconGumstix{
  public:
	int status;
	int length_VarArray;
	class_socket *Client;
	std::string BufferData;

	ViconGumstix();
	~ViconGumstix();
	void update();
	void returnSubjectPos(std::string subjectName, double & x,double & y, double & z, double & p, double & r, double & q);
};

#endif /* VICONGUMSTIX_H_*/
