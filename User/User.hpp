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
	std::string	user;
	std::string ip;
	std::string buffer;
public:
	User();
	User(int fd, std::string nickname, std::string user);
	User(User const &obj);
	User &operator=(User const &obj);
	~User();

	int	getFduser();
	std::string	getNickname();
	std::string	getUser();
	std::string	getIp();
	std::string	getBuffer();

	void	setFduser(int fd);
	void	setNickname(std::string &nickname);
	void	setUser(std::string &user);
	void	setIp(std::string ip);
	void	setBuffer(std::string recv);

	void	removeBuffer();
};
