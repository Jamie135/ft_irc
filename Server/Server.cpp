#include "Server.hpp"

Server::Server()
{
	fdSocket = -1;
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

void	Server::closeFd()
{
	for (int i = 0; i < clients.size(); i++)
	{
		close(clients[i].getFd());
	}
	if (fdSocket != -1)
		close(fdSocket);
}
