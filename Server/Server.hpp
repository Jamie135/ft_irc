#pragma once

#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cerrno>
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
	std::string	pass; // mot de pass
	static bool signal; // static boolean pour le signal
	struct pollfd	poll_fd[11]; // tableau de 11 structures pollfd utilisées pour surveiller 11 files descriptors dont 1 correspond a sockfd
	int	poll_size;
	int	poll_num;
	int	status;
	std::map<int, User*>	sockclient;
	std::map<int, std::string>	buffer;
public:
	Server(char **argv);
	~Server();

	void	initServer();
	void	checkPoll();
	void	acceptClient();
	void	acceptUser(int fd, std::string buff);
	void	receiveEvent(int i);
	static void signalHandler(int signum);
};
