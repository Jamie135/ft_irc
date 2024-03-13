#pragma once

#include <iostream>
#include <vector> // for vector
#include <map> // fot map
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
	int	socketFd;
	int	port; //server port
	std::string	pass; // mot de pass
	std::map<int, Client*>   clients; // vector des clients
	static bool signal; // static boolean pour le signal
public:
	Server(char **argv);
	~Server();

	void	initServer(); // intitalise le server
	void	initSocket(); // initialise le socket
	void	acceptClient(); // accepter un nouveau client
	void	eventClient(); // receive event from registered client
	static void signalHandler(int signum); // signal handler
};
