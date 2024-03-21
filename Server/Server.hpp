#pragma once

#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cerrno>
#include <stdio.h>
#include <algorithm>
#include <map>
#include <vector>
#include <sys/socket.h> // for socket()
#include <sys/types.h> // for socket()
#include <netinet/in.h> // for sockaddr_in
#include <fcntl.h> // for fcntl() in mac
#include <unistd.h> // for close()
#include <arpa/inet.h> // for inet_ntoa()
#include <poll.h> // for poll()
#include <csignal> // for signal()
#include "../User/User.hpp"

class Server
{
private:
	int	sockfd;
	int	port; //server port
	std::string	password; // mot de pass
	static bool signal; // static boolean pour le signal
	std::vector<struct pollfd>	poll_fd; // tableau de 11 structures pollfd utilisées pour surveiller 11 files descriptors dont 1 correspond a sockfd
	struct pollfd	new_client;
	int	poll_size;
	int	status;
	int	max_client;
	int opt_val;
	int	addr_len;
	std::map<int, User*>	sockclient;
	std::map<int, std::string>	buffer;
public:
	Server(char **argv);
	~Server();

	void	initServer();
	void	checkPoll();
	void	acceptClient();
	void	acceptUser(int fd, std::string buff);
	void	receiveEvent(int fd);
	static void signalHandler(int signum);
};
