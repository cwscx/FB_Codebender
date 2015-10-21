#ifndef CLIENT_H
#define CLIENT_H

#ifdef __linux__
	#include <iostream>
	#include <stdlib.h>
	#include <unistd.h>
	#include <cstring>
	#include <sys/types.h>
	#include <sys/socket.h>
	#include <netinet/in.h>
	#include <netdb.h> 
#elif __APPLE__
	#include <iostream>
	#include <stdlib.h>
	#include <unistd.h>
	#include <cstring>
	#include <sys/types.h>
	#include <sys/socket.h>
	#include <netinet/in.h>
	#include <netdb.h>
#endif

class Client
{
	public:
		int sockfd;	// Client socket
		int port;

		Client(char *host, int port);
		~Client();

		void error(const char *msg);
		void writeToServer();
};

#endif
