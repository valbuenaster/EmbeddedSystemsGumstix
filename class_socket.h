/*
 * class_socket.h
 *
 *  Created on: Jul 21, 2014
 *      Author: Luis Ariel Valbuena Reyes
 *
 */
#ifndef CLASS_SOCKET_H_
#define CLASS_SOCKET_H_

#include <iostream>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <math.h>
#include <sstream>

#define SIZE_BUFFER 10
#define DEFAULT_LENGTH 80

#define SERVER_ADDRESS "192.168.0.106"

class class_socket
{
	char BufferINET[INET_ADDRSTRLEN];
	char Data_Received[SIZE_BUFFER];
	std::string Mode;
	socklen_t T_Estructure;
	struct sockaddr_in server_addr,client_addr;
	struct hostent *host;

  public:
	class_socket(const std::string & Mode,int Port);
	~class_socket();

	int sock,Status,cc_connected, Port;
	int VariableSize;
	int connect2Server();
	char *Data_Received_Variable;
	void startListening();
	void serverExists();
	int send_infoClient(const std::string & Type);
	std::string receive_InfoClient();
	std::string receive_InfoClient_Variable();
	int send_infoServer(const std::string & Type);
	std::string receive_InfoServer();
	std::string receive_InfoServer_Variable();
};
#endif
