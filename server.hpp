#ifndef SERVER_H
#define SERVER_H

#ifdef __linux__
	#include <iostream>
	#include <stdlib.h>
	#include <unistd.h>
	#include <cstring>
	#include <sys/types.h>
	#include <sys/socket.h>
	#include <netinet/in.h>
#endif

class Server
{
	public:
		int sockfd;		// Socket built waiting for client
		int newsockfd;	// New socket for connection from client
		int port; 		// port number
		int status;

		Server(int port);
		~Server();

		void error(const char *msg);
		void listenToClient();
};
#endif