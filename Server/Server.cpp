#include "Server.hpp"

Server::Server(char **argv)
{
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	port = atoi(argv[1]);
	pass = argv[2];
}

Server::~Server()
{}

bool	Server::signal = false;


void	Server::signalHandler(int signum)
{
	(void)signum; // evite l'avertissement "unused parameter"
	std::cout << std::endl << "Signal Received!" << std::endl;
	Server::signal = true; // arreter le serveur
}
