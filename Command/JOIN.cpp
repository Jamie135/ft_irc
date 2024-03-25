#include "../Server/Server.hpp"

void	Server::JOIN(std::string message, int fd)
{
	std::cout << "JOIN\nfd: " << fd << " ; message: " << message << std::endl;

	// param est un vecteur dont chaque indice correspond à une paire de string
	// le premier string représente le nom du canal
	// le deuxième string représente la clé associée si elle est spécifié
	std::vector<std::pair<std::string, std::string> >	param;
	if (!splitJoin(param, message, fd))
	{
		return ;
	}
}

int	Server::splitJoin(std::vector<std::pair<std::string, std::string> > &param, std::string message, int fd)
{
	std::vector<std::string>	vec;
	std::istringstream	ss(message);
	std::string	line;
	std::string	channel;
	std::string	key;
	std::string	str;

	// on divise la commandes et ses parametres dans vec
	while (std::getline(ss, line, ' '))
		vec.push_back(line);
	if (vec.size() < 2)
	{
		param.clear();
		return (0);
	}
	vec.erase(vec.begin());
	channel = vec[0];
	vec.erase(vec.begin());
	if (!vec.empty()) // vérifie si les keys sont spécifiées
	{
		key = vec[0];
		vec.clear();
	}
	for (size_t i = 0; i < channel.size(); i++) // extraire les noms de canal
	{
		if (channel[i] == ',')
		{
			param.push_back(std::make_pair(str, "")); // ajoute le nom de canal au vecteur param
			str.clear();
		}
		else
			str += channel[i];
	}
	param.push_back(std::make_pair(str, "")); // ajoute le dernier nom de canal extrait au vecteur param
	
	// si les keys sont spécifiées, il est stocké dans la deuxième partie de chaque paire dans param
	if (!key.empty())
	{
		size_t	j = 0;
		str.clear();
		for (size_t i = 0; i < key.size(); i++)
		{
			if (key[i] == ',') // pour plusieurs keys
			{
				param[j].second = str;
				j++;
				str.clear();
			}
			else
				str += key[i];
		}
		param[j].second = str;
	}
	// supprimer les noms de canal vides
	for (size_t i = 0; i < param.size(); i++)
	{
		if (param[i].first.empty())
			param.erase(param.begin() + i--);
	}
	// vérifie si les noms commencent par un '#' puis l'enlever
	for (size_t i = 0; i < param.size(); i++)
	{
		if (*(param[i].first.begin()) != '#')
		{
			sendMessage2(403, getClientFduser(fd)->getNickname(), param[i].first, getClientFduser(fd)->getFduser(), " :No such channel\r\n");
			param.erase(param.begin() + i--);
		}
		else
			param[i].first.erase(param[i].first.begin());
	}
	return (1);
}
