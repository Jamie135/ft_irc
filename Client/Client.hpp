#pragma once

#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cerrno>
#include <vector> // for vector
#include <map> // for map
#include <sys/socket.h> // for socket()
#include <sys/types.h> // for socket()
#include <netinet/in.h> // for sockaddr_in
#include <fcntl.h> // for fcntl() in mac
#include <unistd.h> // for close()
#include <arpa/inet.h> // for inet_ntoa()
#include <poll.h> // for poll()
#include "../Server/Server.hpp"

class Client
{
private:
	int	fd_user;
	std::string	nickname;
public:
	Client();
	~Client();
};
