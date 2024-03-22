#include "Server.hpp"

void	Server::PASS(std::string message, int fd)
{
	// std::cout << "PASS\nfd: " << fd << " ; message: " << message << std::endl;
	User	*user;
	size_t	nonspace;
	std::string	pass;

	user = getClientFduser(fd);
	message = message.substr(4);
	nonspace = message.find_first_not_of("\t\v ");
	if (nonspace < message.size()) // supprimer les espaces ou les ":"
	{
		message = message.substr(nonspace);
		if (message[0] == ':')
			message.erase(message.begin());
	}
	if (message.empty() || nonspace == std::string::npos)
		sendMessage(ERR_NEEDMOREPARAMS(std::string("*")), fd);
	else if (!user->getRegistered())
	{
		pass = message;
		if (pass == password)
			user->setRegistered(true);
		else
			sendMessage(ERR_PASSWDMISMATCH(std::string("*")), fd);
	}
	else
		sendMessage(ERR_ALREADYREGISTERED(getClientFduser(fd)->getNickname()), fd);
}

void	Server::NICK(std::string message, int fd)
{
	std::cout << "NICK\nfd: " << fd << " ; message: " << message << std::endl;
}
