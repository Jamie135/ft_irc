#include "../Server/Server.hpp"

void	Server::USER(std::string &message, int fd)
{
	std::cout << "USER\nfd: " << fd << " ; message: " << message << std::endl;
}
