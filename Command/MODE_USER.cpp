#include "../Server/Server.hpp"

void	Server::MODE_USER(std::string &message, int fd)
{
	User	*user;
	char	addminus;
	size_t	nonspace;
	std::string	arg;
	std::string	nickname;
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
	parseModeUser(message, nickname, modestring, param);
	paramsplit = splitModeUser(param);
	for (size_t i = 0; i < modestring.size(); i++)
	{
		if (modestring[i] == '+' || modestring[i] == '-')
			addminus = modestring[i];
		else
		{
			if (modestring[i] == 'i')
				ssmode << modeInvisible(addminus, ssmode.str());
		}
	}
	std::string	chain = ssmode.str();
	if (chain.empty())
		return ;
}

void	Server::parseModeUser(std::string message, std::string &nickname, std::string &modestring, std::string &param)
{
	std::istringstream	ss(message);
	size_t	nonspace;

	ss >> nickname;
	ss >> modestring;
	nonspace = message.find_first_not_of(nickname + modestring + " \t\v");
	if (nonspace != std::string::npos)
		param = message.substr(nonspace);
}

std::vector<std::string>	Server::splitModeUser(std::string param)
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

std::string	Server::modeUserAppend(std::string ssmode, char addminus, char mode)
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

std::string	Server::modeInvisible(char addminus, std::string ssmode)
{
	std::string	param;

	param.clear();
	if (addminus == '+')
	{
		param = modeUserAppend(ssmode, addminus, 'i');
	}
	else if (addminus == '-')
	{
		param = modeUserAppend(ssmode, addminus, 'i');
	}
	return (param);
}
