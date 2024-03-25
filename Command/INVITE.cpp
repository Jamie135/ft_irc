#include "../Server/Server.hpp"

void	Server::INVITE(std::string message, int fd)
{
	std::cout << "INVITE\nfd: " << fd << " ; message: " << message << std::endl;

	User	*user;
	std::vector<std::string>	param;

	user = getClientFduser(fd);
	param = splitParam(message);

	if (param.size() < 2)
		sendMessage(ERR_NEEDMOREPARAMS(user->getNickname(), message), fd);
	else if (!checkChannelExist(param[2]))
		sendMessage(ERR_NOSUCHCHANNEL(user->getNickname(), param[2]), fd);
	//ERR_NOTONCHANNEL
	//ERR_CHANOPRIVSNEEDED
	//ERR_USERONCHANNEL
	else
		sendMessage(RPL_INVITING(std::string("*"), user->getNickname(), param[2]), fd);

}
