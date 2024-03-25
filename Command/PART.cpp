#include "../Server/Server.hpp"

void	Server::PART(std::string message, int fd)
{
	std::vector<std::string>	param;
	std::string	reason;
	bool	flag;

	if (!splitPart(message, param, reason, fd))
	{
		sendMessage3(461, getClientFduser(fd)->getNickname(), getClientFduser(fd)->getFduser(), " :Not enough parameters\r\n");
		return ;
	}
	for (size_t i = 0; i < param.size(); i++)
	{
		flag = false;
		for (size_t j = 0; j < this->channel.size(); j++)
		{
			if (this->channel[j].getChannelName() == param[i])
			{
				flag = true;
				if (!channel[j].getUserFd(fd) && !channel[j].getOpFd(fd))
				{
					sendMessage2(442, getClientFduser(fd)->getNickname(), "#" + param[i], getClientFduser(fd)->getFduser(), " :You're not on that channel\r\n");
					continue;
				}
				std::stringstream	ss;
				ss << ":" << getClientFduser(fd)->getNickname() << "!~" << getClientFduser(fd)->getUser() << "@localhost PART #" << param[i];
				if (!reason.empty())
					ss << " :" << reason << "\r\n";
				else
					ss << "\r\n";
				channel[j].sendAll(ss.str());
				if (channel[j].getOpFd(channel[j].getFindUser(getClientFduser(fd)->getNickname())->getFduser()))
					channel[j].removeOp(channel[j].getFindUser(getClientFduser(fd)->getNickname())->getFduser());
				else
					channel[j].removeUser(channel[j].getFindUser(getClientFduser(fd)->getNickname())->getFduser());
				if (channel[j].numClient() == 0)
					channel.erase(channel.begin() + j);
			}
		}
		if (!flag)
			sendMessage2(403, getClientFduser(fd)->getNickname(), "#" + param[i], getClientFduser(fd)->getFduser(), " :No such channel\r\n");
	}
}

int	Server::splitPart(std::string message, std::vector<std::string> &param, std::string &reason, int fd)
{
	std::string	str;
	std::string	tmp;

	tmp = splitPartReason(message, param);
	if (param.size() < 2)
	{
		param.clear();
		return (0);
	}
	param.erase(param.begin());
	str = param[0];
	param.clear();
	for (size_t i = 0; i < str.size(); i++)
	{
		if (str[i] == ',')
		{
			param.push_back(tmp);
			tmp.clear();
		}
		else
			tmp += str[i];
	}
	param.push_back(tmp);
	for (size_t i = 0; i < param.size(); i++)
	{
		if (param[i].empty())
			param.erase(param.begin() + i--);
	}
	if (reason[0] == ':')
		reason.erase(reason.begin());
	else
	{
		for (size_t i = 0; i < reason.size(); i++)
		{
			if (reason[i] == ' ')
			{
				reason = reason.substr(0, i);
				break;
			}
		}
	}
	for (size_t i = 0; i < param.size(); i++)
	{
		if (*(param[i].begin()) == '#')
			param[i].erase(param[i].begin());
		else
		{
			sendMessage2(403, getClientFduser(fd)->getNickname(), param[i], getClientFduser(fd)->getFduser(), " :No such channel\r\n");
			param.erase(param.begin() + i--);
		}
	}
	return (1);
}

// divise la commande en deux mots distincts et stocke les deux premiers mots dans param
std::string	Server::splitPartReason(std::string &message, std::vector<std::string> &param)
{
	int	count;
	std::stringstream	ss(message);
	std::string	str; 
	std::string	reason;

	count = 2;
	while (ss >> str && count--)
		param.push_back(str);
	if (param.size() != 2)
		return (std::string(""));
	findReason(message, param[1], reason);
	return (reason);
}

// trouver la première occurrence de tofind dans message 
// et stocke tout ce qui se trouve après cette occurrence dans reason
void	Server::findReason(std::string message, std::string tofind, std::string &reason)
{
	size_t	i;
	std::string	str;

	i = 0;
	for (; i < message.size(); i++)
	{
		if (message[i] != ' ')
		{
			for (; i < message.size() && message[i] != ' '; i++)
				str += message[i];
			if (str == tofind)
				break;
			else
				str.clear();
		}
	}
	if (i < message.size())
		reason = message.substr(i);
	i = 0;
	for (; i < reason.size() && reason[i] == ' '; i++)
	reason = reason.substr(i);
}
