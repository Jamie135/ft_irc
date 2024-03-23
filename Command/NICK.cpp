#include "../Server/Server.hpp"

void	Server::NICK(std::string message, int fd)
{
	// std::cout << "NICK\nfd: " << fd << " ; message: " << message << std::endl;

	User	*user;
	size_t	nonspace;
	std::string asterisk;
	std::string	old;
	
	user = getClientFduser(fd);
	message = message.substr(4);
	nonspace = message.find_first_not_of("\t\v ");
	asterisk = "*";
	if (nonspace < message.size())
	{
		message = message.substr(nonspace);
		if (message[0] == ':')
			message.erase(message.begin());
	}
	if (message.empty() || nonspace == std::string::npos)
		sendMessage(ERR_NEEDMOREPARAMS(std::string("*"), message), fd);
	if (usedNickname(message) && user->getNickname() != message)
	{
		if (user->getNickname().empty())
			user->setNickname(asterisk);
		sendMessage(ERR_NICKNAMEINUSE(std::string("*"), message), fd);
	}
	if (!validNickname(message))
		sendMessage(ERR_ERRONEUSNICKNAME(std::string("*") ,message), fd);
	else
	{
		if (user && user->getRegistered())
		{
			old = user->getNickname();
			user->setNickname(message);
			if (!old.empty() && old != message)
			{
				if (old == "*" && !user->getUser().empty())
				{
					user->setConnected(true);
					sendMessage(RPL_CONNECTED(user->getNickname()), fd);
					sendMessage(RPL_CHANGENICK(user->getNickname(), message), fd);
				}
				else
					sendMessage(RPL_CHANGENICK(old, message), fd);
			}
		}
		else if (user && !user->getRegistered())
			sendMessage(ERR_NOTREGISTERED(message), fd);
	}
	if (user && user->getRegistered() && !user->getUser().empty() && !user->getNickname().empty() && user->getNickname() != "*" && !user->getConnected())
	{
		user->setConnected(true);
		sendMessage(RPL_CONNECTED(user->getNickname()), fd);
	}
}

bool	Server::usedNickname(std::string &nickname)
{
	for (size_t i = 0; i < this->sockclient.size(); i++)
	{
		if (this->sockclient[i].getNickname() == nickname)
			return (true);
	}
	return (false);
}

bool	Server::validNickname(std::string &nickname)
{
	if (nickname[0] == '&' || nickname[0] == '#' || nickname[0] == ':')
		return (false);
	for (size_t i = 1; i < nickname.size(); i++)
	{
		if (!std::isalnum(nickname[i]) && nickname[i] != '_')
			return (false);
	}
	return (true);
}
