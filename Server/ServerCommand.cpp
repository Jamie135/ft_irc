#include "Server.hpp"

void	Server::PASS(std::string message, int fd)
{
	std::cout << "PASS\nfd: " << fd << " ; message: " << message << std::endl;
}

void	Server::NICK(std::string message, int fd)
{
	std::cout << "NICK\nfd: " << fd << " ; message: " << message << std::endl;
}