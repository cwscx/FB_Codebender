#include "server.hpp"

using namespace std;

#define RETURN_MSG "Message Received"

/*
 * So bascily, a socket is created with socket(), bound to local address with bind(),
 * and is listening for connection after a listen().
 */
Server::Server(int port)
{
	this -> status = 1;
	struct sockaddr_in  serv_addr; 	// Server address

	// Set the default value for port
	if(port == 0) {
		port = 3000;
	}
	this -> port = port;

	// Initialize an IPv4 Internet protocols socket
	this -> sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(this -> sockfd < 0) {
		error("Error opening socket");
	}

	// Clear the server address as 0.
	// Set the server address to given port, and other default value.
	bzero((char *)&serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(port);
	serv_addr.sin_addr.s_addr = INADDR_ANY;

	// Bind the socket with the address, cuz the when a socket is created,
	// it exists in a name space (address family), but no address asigned to it.
	if(bind(this -> sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
		error("Error on binding the socket with address in memory.");
	}

	// Listen to the socketfd 
	listen(this -> sockfd, 5);

	cout << "Server created successfully on localhost:" << this -> port << endl;
	cout << "The server is now listening from client......" << endl;
	cout << "You can type \'quitServer\'' or \'qs\' in the client to close the server." << endl;
}

void Server::listenToClient()
{
	socklen_t clilen;				// Client length
	struct sockaddr_in cli_addr;	// Client address

	// Size of the client address
	clilen = sizeof(cli_addr);

	// Accept a connection on socket
	this -> newsockfd = accept(this -> sockfd, (struct sockaddr *) &cli_addr, &clilen);
	if(this -> newsockfd < 0) {
		error("Error on accepting");
	}

	cout << "\nConnceted from client..." << endl;

	char buffer[256];	// Bytes to be stored from client
	int n;				// Number of bytes read from / write to client

	// Clear buffer and read from client socket
	bzero(buffer, 256);
	n = read(this -> newsockfd, buffer, 255);
	if(n < 0) {
		error("Error reading from socket");
	}

	// If client part entered quit or q
	// Then update the status of the server to quit
	if(strcmp(buffer, "quitServer") == 0 || strcmp(buffer, "qs") == 0)
	{
		this -> status = 0;
	}

	// Print out the message
	cout << "Here is the message: " << buffer << endl;

	// Write to the Client socket
	n = write(this -> newsockfd, RETURN_MSG, strlen(RETURN_MSG));
	if(n < 0) {
		error("Error writing to the Client socket.");
	}

	close(this -> newsockfd);
	cout << "Connection from client closed" << endl;
}

Server::~Server()
{	
	close(this -> sockfd);
	cout << "Server closes at localhost:" << this -> port << endl;
}

void Server::error(const char *msg)
{
	cerr << msg << endl;
	exit(1);
}

int main(int argc, char* argv[])
{
	if(argc != 2) {
		cerr << "Error no port provided." << endl;
		exit(1);
	}

	Server *server = new Server(atoi(argv[1]));

	while(server -> status == 1)
	{
		server -> listenToClient();
	}

	delete server;
	return 0;
}