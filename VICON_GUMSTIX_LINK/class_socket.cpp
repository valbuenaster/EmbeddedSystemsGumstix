#include "class_socket.h"

class_socket::class_socket(const std::string & Mode,int Port)
{
	this->Port=Port;
	if(Mode.compare("server")==0)
	{
		std::cout<<"It is going to create a server"<<std::endl;

		if((this->sock=socket(AF_INET,SOCK_STREAM,0))==-1)
		{
			perror("El socket...");
		}

		if(setsockopt(this->sock,SOL_SOCKET,SO_REUSEADDR,&Status,sizeof(int))==-1)
		{
			perror("Error...");
		}
		this->server_addr.sin_family=AF_INET;
		this->server_addr.sin_port=htons(this->Port);
		this->server_addr.sin_addr.s_addr=INADDR_ANY;

		if(bind(this->sock,(struct sockaddr *)&server_addr,sizeof(struct sockaddr))==-1)
		{
			perror("cannot link port with the IP address...");
		}
	}
		
	if(Mode.compare("client")==0)
	{
		std::cout<<"It is going to create a client"<<std::endl;

		this->host=gethostbyname("127.0.0.1");//192.168.0.146

		if((this->sock=socket(AF_INET,SOCK_STREAM,0))==-1)//
		{
			perror("Socket creation failed...");
		}

inet_pton(AF_INET,SERVER_ADDRESS,&(this->server_addr.sin_addr));
		this->server_addr.sin_family=AF_INET;
		this->server_addr.sin_port=htons(this->Port);
	
		printf("local IP address is: %s.\n",inet_ntop(AF_INET,&(this->server_addr.sin_addr),this->BufferINET,INET_ADDRSTRLEN));
		bzero(&(this->server_addr.sin_zero),8);
	}
}
void class_socket::startListening()
{
		if(listen(this->sock,5)==-1)//The server is listening...
		{
			perror("it is not listening...");
		}

		std::cout<<"TCP Server waiting for client at port "<<this->Port<<std::endl;
		fflush(stdout);

		this->T_Estructure=sizeof(client_addr);
		this->cc_connected=accept(this->sock,(struct sockaddr *)&client_addr,&T_Estructure);
		
		if (this->cc_connected!=-1)
		{
			printf("it received a connection from: %s. through the port: %d.\n",inet_ntoa(client_addr.sin_addr),ntohs(client_addr.sin_port));
		}else{
			perror("it didn't connect...");
		}
}

int class_socket::connect2Server()
{
	if(connect(this->sock,(struct sockaddr *)&server_addr,sizeof(struct sockaddr))==-1)
	{
		perror("Connection error...");
		return -1;
	}
	return 0;
}

class_socket::~class_socket()
{	
	
	close(cc_connected);
	close(sock);
}

std::string class_socket::receive_InfoClient()
{
	int bytesReceived=read(this->sock,this->Data_Received,SIZE_BUFFER);
	Data_Received[bytesReceived]='\0';
	std::string returnValue=Data_Received;
	return returnValue;
}

std::string class_socket::receive_InfoClient_Variable()
{
	int bytesReceived=read(this->sock,this->Data_Received_Variable,this->VariableSize);
	Data_Received[bytesReceived]='\0';
	std::string returnValue=Data_Received_Variable;
//	printf("Data_Received in function: %s, bytes= %d. \n",this->Data_Received_Variable,bytesReceived);	
	return returnValue;
}

int class_socket::send_infoClient(const std::string & Type)
{
	int bytesTosend=write(this->sock,Type.data(),Type.size());
	return bytesTosend;
}

std::string class_socket::receive_InfoServer()
{
	int bytesReceived=read(this->cc_connected,this->Data_Received,SIZE_BUFFER);
	Data_Received[bytesReceived]='\0';
	std::string returnValue=Data_Received;
	return returnValue;
}

std::string class_socket::receive_InfoServer_Variable()
{
	int bytesReceived=read(this->cc_connected,this->Data_Received_Variable,VariableSize);
	Data_Received[bytesReceived]='\0';
	std::string returnValue=Data_Received_Variable;
	return returnValue;
}

int class_socket::send_infoServer(const std::string & Type)
{
	int bytesTosend=write(this->cc_connected,Type.data(),Type.size());
//	printf("Data_to_Send: %s, bytesTosend= %d, Type.size() = %d. \n",Type.data(),bytesTosend,Type.size());	
	return bytesTosend;
}

void class_socket::serverExists()
{
	int valA=0;
	int n_Agents=7;
	std::string Received_Array;

	std::stringstream stream;
	std::string baseChain;

	std::string DataAA("Any data string you want to put here.");

	while(1)
	{
		this->startListening();

		//receiving request
		Received_Array=this->receive_InfoServer();
		printf("Data_received: %s\n",Received_Array.data());

		//sending Info to variable array		
		baseChain.erase (baseChain.begin(), baseChain.end());
		stream<<std::dec<<(n_Agents*DEFAULT_LENGTH);
		baseChain=stream.str();

		valA=this->send_infoServer(baseChain);

		//receiving Acknowledgement
		Received_Array=this->receive_InfoServer();
		printf("Data_received: %s\n",Received_Array.data());

		//Sending the complete info ...
		valA=this->send_infoServer(DataAA);
		printf("PASA AQUI\n");
		close(cc_connected);
	}
}
