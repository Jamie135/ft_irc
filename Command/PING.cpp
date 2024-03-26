#include "../Server/Server.hpp"

void	Server::PING(std::string &message, int fd)
{
	User	*user;
	std::vector<std::string>	param;

	user = getClientFduser(fd);
	param = splitParam(message);
	if (user && param.size() < 2)
		sendMessage(ERR_NEEDMOREPARAMS(std::string("*"), user->getNickname()), fd);
	sendMessage(RPL_PONG, fd);
}
