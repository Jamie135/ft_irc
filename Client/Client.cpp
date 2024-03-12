#include "Client.hpp"

Client::Client()
{}

Client::~Client()
{}

int	Client::getFd()
{
	return fd;
}

void	Client::setFd(int n)
{
	fd = n;
}
