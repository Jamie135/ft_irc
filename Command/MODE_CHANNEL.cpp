#include "../Server/Server.hpp"

void	Server::MODE_CHANNEL(std::string &message, int fd)
{
	User	*user;
	Channel	*chan;
	char	addminus;
	size_t	nonspace;
	std::string	arg;
	std::string channelname;
	std::string param;
	std::string	modestring;
	std::stringstream	ssmode;
	std::vector<std::string>	paramsplit;

	addminus = '\0';
	arg = ":";
	arg.clear();
	modestring.clear();
	user = getClientFduser(fd);
	nonspace = message.find_first_not_of("MODEmode \t\v");
	if (nonspace != std::string::npos)
		message = message.substr(nonspace);
	else
	{
		sendMessage(ERR_NEEDMOREPARAMS(user->getNickname()), fd);
		return ;
	}
	parseModeChan(message, channelname, modestring, param);
	paramsplit = splitModeChan(param);
	chan = getChannel(channelname.substr(1));
	if (channelname[0] != '#' || !chan)
	{
		sendMessage(ERR_NOSUCHCHANNEL(user->getUser(), channelname), fd);
		return ;
	}
	else if (!chan->getUserFd(fd) && !chan->getOpFd(fd))
	{
		sendMessage2(442, getClientFduser(fd)->getNickname(), channelname, getClientFduser(fd)->getFduser(), " :You're not on that channel\r\n");
		return ;
	}
	else if (modestring.empty())
	{
		sendMessage(RPL_CHANNELMODEIS(user->getNickname(), chan->getChannelName(), chan->getMode()) + \
			RPL_CREATIONTIME(user->getNickname(), chan->getChannelName(), chan->getCreatedAt()), fd);
		return ;
	}
	else if (!chan->getOpFd(fd))
	{
		sendMessage(ERR_CHANOPRIVSNEEDED(chan->getChannelName()), fd);
		return ;
	}
	else if (chan)
	{
		for (size_t i = 0; i < modestring.size(); i++)
		{
			if (modestring[i] == '+' || modestring[i] == '-')
				addminus = modestring[i];
			else
			{
				if (modestring[i] == 'i')
					ssmode << modeInviteOnly(chan, addminus, ssmode.str());
				else
					sendMessage(ERR_UNKNOWNMODE(user->getNickname(), chan->getChannelName(), modestring[i]), fd);
			}
		}
	}
	std::string	chain = ssmode.str();
	std::cout << "CHAIN: " << chain << std::endl;
	if (chain.empty())
		return ;
	chan->sendAll(RPL_CHANGEMODE(user->getHostname(), chan->getChannelName(), ssmode.str(), arg));
}

// stocker le nom du canal, les modes spécifiés et les paramètres additionnels
void	Server::parseModeChan(std::string message, std::string &channelname, std::string &modestring, std::string &param)
{
	std::istringstream	ss(message);
	size_t	nonspace;

	ss >> channelname;
	ss >> modestring;
	nonspace = message.find_first_not_of(channelname + modestring + " \t\v");
	if (nonspace != std::string::npos)
		param = message.substr(nonspace);
}

// découpe les paramètres extraits avec ',' comme délimiteur
// et stocke ensuite chaque partie découpée dans paramsplit
std::vector<std::string>	Server::splitModeChan(std::string param)
{
	std::vector<std::string>	paramsplit;
	std::string	line;
	std::istringstream	ss(line);

	if (!param.empty() && param[0] == ':')
		param.erase(param.begin());
	while (std::getline(ss, line, ','))
	{
		paramsplit.push_back(line);
		line.clear();
	}
	return (paramsplit);
}

std::string	Server::modeChanAppend(std::string ssmode, char addminus, char mode)
{
	std::stringstream ss;

	ss.clear();
	char nul = '\0';
	for (size_t i = 0; i < ssmode.size(); i++)
	{
		if (ssmode[i] == '+' || ssmode[i] == '-')
			nul = ssmode[i];
	}
	if (nul != addminus)
		ss << addminus << mode;
	else
		ss << mode;
	return (ss.str());
}

std::string	Server::modeInviteOnly(Channel *channel, char addminus, std::string ssmode)
{
	std::string	param;

	param.clear();
	if (addminus == '+' && !channel->getModeOption(0))
	{
		channel->setMode(0, true);
		channel->setOnlyInvited(1);
		param = modeChanAppend(ssmode, addminus, 'i');
	}
	else if (addminus == '-' && channel->getModeOption(1))
	{
		channel->setMode(1, false);
		channel->setOnlyInvited(0);
		param = modeChanAppend(ssmode, addminus, 'i');
	}
	return (param);
}
