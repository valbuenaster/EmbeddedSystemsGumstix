#include "vicon_pos.h"
#include <iostream>
#include <string>
#include <stdio.h>
#include "class_socket.h"

#define LINE_LENGTH 80

int main (int argc, char* argv [])
{
	char DataFormated[LINE_LENGTH];
	int n;
	int valA=0;
	float posx_temp,posy_temp,posz_temp;
	float angulo_temp1=0,angulo_temp2=0,angulo_temp3=0;

	std::string StringDataFormatted;
	std::string baseChain;
	std::string Received_Array;
	std::stringstream stream;
	vicon_pos* v = new vicon_pos();
	class_socket *Server= new class_socket("server",8095);

	v->update();

	int N_Robots=v->num_subs;

	while(1)
	{

		Server->startListening();

		//receiving request
		Received_Array=Server->receive_InfoServer();
		printf("Data_received: %s\n",Received_Array.data());

		//sending Info to variable array		
		baseChain.erase (baseChain.begin(), baseChain.end());
		stream<<std::dec<<(N_Robots*DEFAULT_LENGTH);
		baseChain=stream.str();
		valA=Server->send_infoServer(baseChain);

		v->update();
		StringDataFormatted.clear();

		for(int bb=0;bb<N_Robots;bb++)
		{//130 characters to describe the position of a robot
			v->get_subject_coord(bb,posx_temp,posy_temp,posz_temp);
			v->get_subject_euler_xyz(bb,angulo_temp1,angulo_temp2,angulo_temp3);

			n=sprintf(DataFormated,"%sx%4.2fy%4.2fz%4.2fp%4.2fr%4.2fq%4.2f",v->subjects[bb].data(),posx_temp,posy_temp,posz_temp,angulo_temp1,angulo_temp2,angulo_temp3);		

			//std::cout<<DataFormated<<std::endl;
			StringDataFormatted.append(DataFormated);
		}			
		std::cout<<StringDataFormatted.data()<<std::endl;

		//receiving Acknowledgement
		Received_Array=Server->receive_InfoServer();
		printf("Data_received: %s\n",Received_Array.data());

		//Sending the complete info ...
		valA=Server->send_infoServer(StringDataFormatted);
		printf("PASA AQUI\n");
		close(Server->cc_connected);
	}

	sleep(1);
	return 0;
};

