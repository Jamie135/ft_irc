#include "../Server/Server.hpp"

void	Server::MODE(std::string &message, int fd)
{
	User	*user;
	Channel	*chan;
	// char	mode;
	size_t	nonspace;
	std::string	arg;
	std::string channelname;
	std::string param;
	std::string	modestring;
	std::stringstream	ssmode;
	std::vector<std::string>	paramsplit;

	// mode = '\0';
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
	parseModeParam(message, channelname, modestring, param);
	paramsplit = splitModeParam(param);
	if (channelname[0] != '#' || !(chan = getChannel(channelname.substr(1))))
	{
		sendMessage(ERR_NOSUCHCHANNEL(user->getUser(), channelname), fd);
		return ;
	}
	else if (!chan->getUserFd(fd) && !chan->getOpFd(fd))
	{
		sendMessage2(442, getClientFduser(fd)->getNickname(), channelname, getClientFduser(fd)->getFduser(), " :You're not on that channel\r\n");
		return ;
	}
}

// stocker le nom du canal, les modes spécifiés et les paramètres additionnels
void	Server::parseModeParam(std::string message, std::string &channelname, std::string &modestring, std::string &param)
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
std::vector<std::string>	Server::splitModeParam(std::string param)
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
