#include "class_socket.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
	class_socket *Client= new class_socket("client",8095);
	int length_VarArray=0;

	int value = Client->connect2Server();

	int value2 =Client->send_infoClient("REQ");//Sending Request

	std::string CadenaRecibida=Client->receive_InfoClient();
	printf("Data_received: %s\n",CadenaRecibida.data());

	length_VarArray=atoi(CadenaRecibida.data());

	printf("The variable array has to be : %d characters long.\n",length_VarArray);
	Client->VariableSize=length_VarArray;
	Client->Data_Received_Variable= (char*) malloc (Client->VariableSize);

	value2 =Client->send_infoClient("ACK");//Sending ACK

	//Receiving block of info.	
	std::string CadenaRecibida2=Client->receive_InfoClient_Variable();
	printf("Data_received: %s\n",CadenaRecibida2.data());

	free (Client->Data_Received_Variable);

	return 0;
}
