#pragma once

#include <iostream>
#include <vector> // for vector
#include <map> // fot map
#include <string>

#include <sys/socket.h> // for socket()
#include <sys/types.h> // for socket()
#include <netinet/in.h> // for sockaddr_in
#include <fcntl.h> // for fcntl() in mac
#include <unistd.h> // for close()
#include <arpa/inet.h> // for inet_ntoa()
#include <poll.h> // for poll()
#include <csignal> // for signal()
#include <stdlib.h>
#include <stdint.h>
#include "../Client/Client.hpp"

class Server
{
private:
	int	sockfd;
	int	port; //server port
	std::string	pass; // mot de pass
	std::map<int, Client*>   clients; // vector des clients
	static bool signal; // static boolean pour le signal
	struct sockaddr_in	addr;
	socklen_t	socklen;
	int	(Server::*parse[8])(std::string split_mess[3]);
public:
	Server(char **argv);
	~Server();

	void	initServer(); // intitalise le server
	int	initSocket(); // initialise le socket
	int	acceptClient( void ); // accepter un nouveau client
	void	eventClient(); // receive event from registered client
	static void signalHandler(int signum); // signal handler

	int	splitMessage( std::string message, std::string split_mess[3] );
	int	splitParams( std::string params, std::string split_params[3] );

	int	parseNick( std::string split_mess[3] );
	int	parseUser( std::string split_mess[3] );
	int	parseJoin( std::string split_mess[3] );
	int	parsePrivmsg( std::string split_mess[3] );
	int	parseTopic( std::string split_mess[3] );
	int	parseMode( std::string split_mess[3] );
	int	parseKick( std::string split_mess[3] );
	int	parseInvite( std::string split_mess[3] );

	int8_t	parseCommand( std::string command );
	int	parseMessage( std::string message );
};