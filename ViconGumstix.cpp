/*
 * ViconGumstix.cpp
 *
 *  Created on: Jul 21, 2014
 *      Author: Luis Ariel Valbuena Reyes
 *
 */
#include "ViconGumstix.h"
#include "class_socket.h"
#include <iostream>
#include <string>

ViconGumstix::ViconGumstix() 
{
	
}

ViconGumstix::~ViconGumstix()
{
}
        
void ViconGumstix::update()
{
	this->Client= new class_socket("client",8095);
	this->length_VarArray=0;

	this->status = Client->connect2Server();

	this->status = Client->send_infoClient("REQ");//Sending Request

	std::string CadenaRecibida;
	CadenaRecibida.erase(0,CadenaRecibida.size());
	CadenaRecibida=Client->receive_InfoClient();

//	std::cout<<"Data_received: "<<CadenaRecibida.data()<<std::endl;

	length_VarArray=atoi(CadenaRecibida.data());

//	std::cout<<"The variable array has to be : "<<length_VarArray<<" characters long."<<std::endl;
	Client->VariableSize=length_VarArray;
	Client->Data_Received_Variable= (char*) malloc (length_VarArray);

	this->status =Client->send_infoClient("ACK");//Sending ACK

	//Receiving block of info.	
	this->BufferData=Client->receive_InfoClient_Variable();
//	std::cout<<"Data_received: "<<this->BufferData.data()<<std::endl;

	free (Client->Data_Received_Variable);
	delete this->Client;
}
        
void ViconGumstix::returnSubjectPos(std::string subjectName, double & x,double & y, double & z, double & p, double & r, double & q)
{
	std::size_t found = this->BufferData.find(subjectName);
	std::size_t found_1=0;
        std::size_t found_2=0;
        std::size_t found_3=0;
        std::size_t found_4=0;
        std::size_t found_5=0;
        std::size_t found_6=0;
	std::size_t found_7=0;

	std::string str1;
        std::string str2;
        std::string str3;
        std::string str4;
        std::string str5;
        std::string str6;


	if(found ==-1)
	{
		std::cout<<"The subject "<<subjectName<<" is not present..."<<std::endl;
	}else{
		found_1 = this->BufferData.find("x",found+1);
                found_2 = this->BufferData.find("y",found_1+1);
                found_3 = this->BufferData.find("z",found_2+1);
                found_4 = this->BufferData.find("p",found_3+1);
                found_5 = this->BufferData.find("r",found_4+1);
                found_6 = this->BufferData.find("q",found_5+1);
                found_7 = this->BufferData.find("@",found_6+1);

		str1=this->BufferData.substr(found_1+1,found_2-found_1-1);
                str2=this->BufferData.substr(found_2+1,found_3-found_2-1);
                str3=this->BufferData.substr(found_3+1,found_4-found_3-1);
                str4=this->BufferData.substr(found_4+1,found_5-found_4-1);
                str5=this->BufferData.substr(found_5+1,found_6-found_5-1);
                str6=this->BufferData.substr(found_6+1,found_7-found_6-1);

//		std::cout<<"x = "<<str1<<", y = "<<str2<<", z = "<<str3<<", p = "<<str4<<", q = "<<str5<<", r = "<<str6<<std::endl;

		std::string::size_type sz;
		x= atof(str1.c_str());
		y= atof(str2.c_str());
		z= atof(str3.c_str());
		p= atof(str4.c_str());
		r= atof(str5.c_str());
		q= atof(str6.c_str());
	}	
}
