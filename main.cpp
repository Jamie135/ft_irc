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
#include "./Server/Server.hpp"

int	main(int argc, char **argv)
{
	if (argc != 3)
	{
		std::cerr << "Error: Syntax must be ./ircserv <port> <password>";
		return (0);
	}

	Server	serv;
	try
	{
		signal(SIGINT, Server::signalHandler);
		signal(SIGQUIT, Server::signalHandler);
	}
	catch(const std::exception& e)
	{
		serv.closeFd();
		std::cerr << e.what() << std::endl;
	}
	return (0);
}