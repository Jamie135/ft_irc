#pragma once

#include <iostream>
#include <vector> // for vector
#include <sys/socket.h> // for socket()
#include <sys/types.h> // for socket()
#include <netinet/in.h> // for sockaddr_in
#include <fcntl.h> // for fcntl() in mac
#include <unistd.h> // for close()
#include <arpa/inet.h> // for inet_ntoa()
#include <poll.h> // for poll()
#include <csignal> // for signal()
#include "../Client/Client.hpp"

class Server
{
private:
	int	port; //server port
	int	fdSocket; //socket file descriptor
	std::vector<Client> clients; // vector des clients
	static bool signal; // static boolean pour le signal
public:
	Server();
	~Server();

	void	initServer(); // intitalise le server
	void	initSocket(); // initialise le socket
	void	acceptClient(); // accepter un nouveau client
	void	eventClient(); // receive event from registered client
	static void signalHandler(int signum); // signal handler
	void	closeFd(); // close file descriptors
};
