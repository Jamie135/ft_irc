#pragma once

#include <iostream>
#include <vector> //-> for vector
#include <sys/socket.h> //-> for socket()
#include <sys/types.h> //-> for socket()
#include <netinet/in.h> //-> for sockaddr_in
#include <fcntl.h> //-> for fcntl() in mac
#include <unistd.h> //-> for close()
#include <arpa/inet.h> //-> for inet_ntoa()
#include <poll.h> //-> for poll()
#include <csignal> //-> for signal()
#include <stdlib.h>
#include <cerrno>
#include <cstring>
// #include "../Server/Server.hpp"

class Client
{
private:
	int	sockfd;
	int port;
	// socklen_t	socklen;
	struct sockaddr_in addr;

public:
	Client();
	Client( char *arg );
	~Client();

	int initSocket( void );
	int	sendConnectionRequest( void );
};
