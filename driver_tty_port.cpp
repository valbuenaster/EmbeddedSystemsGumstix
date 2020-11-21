/*
 * driver_tty_port.cpp
 *
 *  Created on: Jul 21, 2014
 *      Author: Luis Ariel Valbuena Reyes
 *
 */
#include <stdio.h>
#include <stdlib.h>

#include "driver_tty_port.h"

driver_tty_port::driver_tty_port(const std::string & Port,int speed)
{
	int temp=0;
	this->Port=Port;
	this->PathRoute="/dev/ttyS";
	this->PathRoute.append(this->Port);

	std::stringstream stream;
	stream<<std::dec<<speed;
	std::string string_Speed(stream.str());

	std::string String2Write;
	String2Write="stty -F ";
	String2Write.append(this->PathRoute);
	String2Write.append(" speed ");
	String2Write.append(string_Speed);
	String2Write.append(" raw -clocal cs8 -parenb -cstopb");

//	std::cout<<"String to write in system .... "<< String2Write <<std::endl;
	temp=system(String2Write.data());	
}

driver_tty_port::~driver_tty_port()
{}

void driver_tty_port::transmit_Info(const std::string & Info)
{
	FILE *fp;

	fp=fopen(this->PathRoute.data(),"w");
	if(!fp) exit(-1);

	fprintf(fp,Info.data());
	std::cout<<"This is the path"<<this->PathRoute.data()<<". It should have sent this: "<<Info.data()<<std::endl;
	fclose(fp);
}
/*
void driver_tty_port::transmit_Info(int Character)
{
	FILE *fp;
	std::stringstream Charac;
	Charac<<"0x"<<std::hex<<Character;
	std::string DataToTransmitt(Charac.str());

	fp = fopen(this->PathRoute.data(),"w");
	if(!fp) exit(-1);

	fprintf(fp,DataToTransmitt.data());
	std::cout<<"Transmitted Info "<<DataToTransmitt.data() <<" It should have printed the character "<<Character<<std::endl;
	fclose(fp);
}
*/
void driver_tty_port::transmit_Info(char Character)
{
	FILE *fp;
	fp=fopen(this->PathRoute.data(),"w");
	if(!fp) exit(-1);

	char Buffer=Character;

	fwrite(&Buffer,sizeof(char),sizeof(char),fp);
	
	fclose(fp);
}

void driver_tty_port::transmit_Info(char * ArrayI, int n)
{
//	std::cout<<"N CARACTERS"<<n<<std::endl;
	FILE *fp;
	fp=fopen(this->PathRoute.data(),"w");
	if(!fp) exit(-1);

	char *Buffer= new char[n];
	for(int i=0;i<n;i++)Buffer[i]=ArrayI[i];
	
	fwrite(Buffer,sizeof(char),n,fp);
	fclose(fp);
	delete Buffer;
}

std::string driver_tty_port::get_Info()
{
}
