#include "client.hpp"

using namespace std;

Client::Client(char *host, int port)
{
	struct sockaddr_in serv_addr; 	// Server address
	struct hostent *server;			// server

	// Set the default value for port
	if(port == 0) {
		port = 3000;
	}
	this -> port = port;

	this -> sockfd = socket(AF_INET, SOCK_STREAM, 0);
	
	if(sockfd < 0) 
		error("Error opening socket");

	server = gethostbyname(host);
	if(server == NULL)
	{
		cerr << "Error! No such host" << endl;
		exit(1);
	}

	bzero((char *) &serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;

	bcopy((char *)server->h_addr, 
         (char *)&serv_addr.sin_addr.s_addr,
         server->h_length);

    serv_addr.sin_port = htons(port);
    if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) 
        error("ERROR connecting");

    cout << "Client started successfully..." << endl;
    cout << "Client connects with localhost:" << this -> port << endl;
	cout << "You can type \'quitServer\'' or \'qs\' to close the server." << endl;
}

Client::~Client()
{
    close(this -> sockfd);
	cout << "Client closes connection to localhost:" << this -> port << endl;
}

void Client::error(const char *msg)
{
	cerr << msg << endl;
	exit(1);
}

void Client::writeToServer()
{
	char buffer[256];
	int n;			// Number of bytes write to / read from the socket

    cout << "Please enter the message: ";
    
    bzero(buffer,256);
    cin >> buffer;

    n = write(sockfd,buffer,strlen(buffer));
    if (n < 0) 
         error("ERROR writing to socket");
    
    bzero(buffer,256);
    n = read(sockfd,buffer,255);
    if (n < 0) 
         error("ERROR reading from socket");
    cout << buffer << endl;
}

int main(int argc, char *argv[])
{
	if(argc != 3) {
		cerr << "Incorrect Input arguments" << endl;
		cerr << "You should follow the format that ./client host port" << endl;
		exit(1);
	}

	Client *client = new Client(argv[1], atoi(argv[2]));
	client -> writeToServer();
	delete client;
	
	return 0;
}