#include "../Server/Server.hpp"

void	Server::QUIT(std::string message, int fd)
{
	std::cout << "QUIT\nfd: " << fd << " ; message: " << message << std::endl;
}
