#include "Server.hpp"

Server::Server(char **argv)
{
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	std::cout << "Server constructed: Passive Socket == " << sockfd << std::endl;
	port = atoi(argv[1]);
	pass = argv[2];
	poll_size = 10;
}

Server::~Server()
{
	std::cout << "Server destructed" << std::endl;
	for (std::map<int, Client*>::iterator it = clients.begin(); it != clients.end(); ++it)
	{
		delete it->second;
	}
}

bool	Server::signal = false;


void	Server::signalHandler(int signum)
{
	(void)signum; // evite l'avertissement "unused parameter"
	std::cout << std::endl << "Signal Received!" << std::endl;
	Server::signal = true; // arreter le serveur
}
