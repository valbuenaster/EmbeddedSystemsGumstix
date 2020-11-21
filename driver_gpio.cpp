/*
 * driver_gpio.cpp
 *
 *  Created on: Jul 21, 2014
 *      Author: Luis Ariel Valbuena Reyes
 *
 */

#include "driver_gpio.h"

using namespace std;

void setGPIO_PORT144()
{
	cout<<"setGPIO_PORT144: This port is set up only as output by default"<< endl;
}

void setGPIO_PORT_INPUT144()
{
	cout<<"setGPIO_PORT_INPUT144: This port is set up only as output by default"<< endl;
}

void setGPIO_PORT_OUTPUT144()
{
	cout<<"setGPIO_PORT_OUTPUT144: This port is set up only as output by default"<< endl;
}

void setGPIO_PORT_VALUE144(int value)
{
	char Array[100];
	memset(Array,0,100);
	char buffer[10];
	memset(buffer,0,10);
	char Val[3];

	FILE *pF;
	strcat(Array,ROUTEPORT);
	snprintf(buffer,10,"%d",144);
	snprintf(Val,3,"%d",value);
	strcat(Array,"/gpio");
	strcat(Array,buffer);
	strcat(Array,"/value");

	pF=fopen(Array,"w");
	fwrite(Val,sizeof(char),sizeof(Val), pF);
	
	fclose(pF);
}

void setGPIO_PORT147()
{
	char Array[100];
	memset(Array,0,100);
	FILE *pF;

	strcat(Array,ROUTEPORT);
	strcat(Array,"/export");
	cout<<"Destiny to open ..."<< Array << endl;
	pF=fopen(Array,"w");
	fprintf(pF,"%d",147);

	fclose(pF);
}

void setGPIO_PORT_INPUT147()
{
	char Array[100];
	memset(Array,0,100);
	char buffer[10];
	memset(buffer,0,10);

	FILE *pF;
	strcat(Array,ROUTEPORT);
	snprintf(buffer,10,"%d",147);
	strcat(Array,"/gpio");
	strcat(Array,buffer);
	strcat(Array,"/direction");
	
	pF=fopen(Array,"w");
	fprintf(pF,"in");

	fclose(pF);
}

void setGPIO_PORT_OUTPUT147()
{
	char Array[100];
	memset(Array,0,100);
	char buffer[10];
	memset(buffer,0,10);
	char outString[]="out";

	FILE *pF1;
	strcat(Array,ROUTEPORT);
	snprintf(buffer,10,"%d",147);
	strcat(Array,"/gpio");
	strcat(Array,buffer);
	strcat(Array,"/direction");
	
	pF1=fopen(Array,"w");
	fwrite(outString,sizeof(char),sizeof(outString),pF1);
	
	fclose(pF1);
}

void setGPIO_PORT_VALUE147(int value)
{
	char Array[100];
	memset(Array,0,100);
	char buffer[10];
	memset(buffer,0,10);
	char Val[3];

	FILE *pF;
	strcat(Array,ROUTEPORT);
	snprintf(buffer,10,"%d",147);
	snprintf(Val,3,"%d",value);
	strcat(Array,"/gpio");
	strcat(Array,buffer);
	strcat(Array,"/value");

	pF=fopen(Array,"w");
	fwrite(Val,sizeof(char),sizeof(Val), pF);
	
	fclose(pF);
}
