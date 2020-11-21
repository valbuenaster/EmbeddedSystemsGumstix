#include "vicon_pos.h"
#include <iostream>
#include <string>
#include <stdio.h>

#define LINE_LENGTH 80

int main (int argc, char* argv [])
{
	char DataFormated[LINE_LENGTH];
	int n;
	std::string StringDataFormatted;
	vicon_pos* v = new vicon_pos();

	float posx_temp,posy_temp,posz_temp;
	float angulo_temp1=0,angulo_temp2=0,angulo_temp3=0;
	
	v->update();

	int N_Robots=v->num_subs;

	double distance=1;

	while(distance>0.1)
	{
		v->update();
		StringDataFormatted.clear();
		for(int bb=0;bb<N_Robots;bb++)
		{//130 characters to describe the position of a robot
			v->get_subject_coord(bb,posx_temp,posy_temp,posz_temp);
			v->get_subject_euler_xyz(bb,angulo_temp1,angulo_temp2,angulo_temp3);

			n=sprintf (DataFormated, "%sx%4.2fy%4.2fz%4.2fp%4.2fr%4.2fq%4.2f",v->subjects[bb].data(),posx_temp,posy_temp,posz_temp,angulo_temp1,angulo_temp2,angulo_temp3);		

			//std::cout<<DataFormated<<std::endl;
			StringDataFormatted.append(DataFormated);
		}			
		std::cout<<StringDataFormatted.data()<<std::endl;

		distance-=0.1;
	}

	sleep(5);
	return 0;
};

