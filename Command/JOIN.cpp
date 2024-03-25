#include "../Server/Server.hpp"

void	Server::JOIN(std::string message, int fd)
{
	std::cout << "JOIN\nfd: " << fd << " ; message: " << message << std::endl;

	// param est un vecteur dont chaque indice correspond à une paire de string
	// le premier string représente le nom du canal
	// le deuxième string représente la clé associée si elle est spécifié
	std::vector<std::pair<std::string, std::string> >	param;
}
