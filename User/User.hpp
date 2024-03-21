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
#include "../Channel/Channel.hpp"

class Channel;

class User
{
private:
	int	fdUser;
	std::string	nickname;
	std::string	name;
public:
	User(int fdNew, std::string const &nicknameNew);
	~User();
	int	getFdUser();
	std::string const	&getNickName() const;
	std::string const	&getName() const;
	void	setName(std::string const &nameNew);
};
