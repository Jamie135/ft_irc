#include "../Server/Server.hpp"

void	Server::OPER(std::string &message, int fd)
{
	User	*user;
	std::vector<std::string>	param;

	user = getClientFduser(fd);
	param = splitParam(message);
	if (param.size() < 2)
		sendMessage(ERR_NEEDMOREPARAMS(std::string("*"), user->getNickname()), fd);
	if (param[2] != password)
		sendMessage(ERR_PASSWDMISMATCH(std::string("*")), fd);
	user->setOp(true);
	sendMessage(RPL_YOUREOPER(user->getNickname()), fd);
}
