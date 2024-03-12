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
	static bool	signal; // for signal
	std::vector<Client> clients; // vector of clients
public:
	Server();
	~Server();

	void	initServer(); // server initialization
	void	initSocket(); // socket initialization
	void	acceptClient(); // accept new client
	void	eventClient(); // receive event from registered client
};
