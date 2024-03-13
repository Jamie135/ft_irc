#include "Server.hpp"

Server::Server(char **argv)
{
	socketFd = socket(AF_INET, SOCK_STREAM, 0);
	port = atoi(argv[1]);
	pass = argv[2];
}

Server::~Server()
{}

void	Server::initServer()
{
	struct sockaddr_in address;

	if (setsockopt(socketFd, SOL_SOCKET, SO_REUSEADDR, "1", 1) < 0)
		exit(EXIT_FAILURE);
	address.sin_family = AF_INET; // famille d'adresse IPv4
	address.sin_addr.s_addr = INADDR_ANY; //accepter les connexions entrantes sur toutes les interfaces réseau disponibles
	address.sin_port = htons(port); // le serveur écoute les connexions entrantes sur port
	if (bind(socketFd, (sockaddr *)&address, sizeof(address)) < 0) // lier le socket a l'adresse ip specifié
		exit(EXIT_FAILURE);
}

bool	Server::signal = false;


void	Server::signalHandler(int signum)
{
	(void)signum; // evite l'avertissement "unused parameter"
	std::cout << std::endl << "Signal Received!" << std::endl;
	Server::signal = true; // arreter le serveur
}
