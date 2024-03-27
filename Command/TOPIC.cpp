#include "../Server/Server.hpp"

void Server::TOPIC( std::string message, int fd )
{
	std::cout << "> Info: TOPIC(): message == " << message << std::endl;
    std::string split_message[3] = {std::string(), std::string(), std::string()};
    if (splitMessage(message, split_message))
		return ;
	
	std::string split_params[3] = {std::string(), std::string(), std::string()};
	if (splitParams(split_message[2], split_params) == 1)
	{
		return ;
	}
	if (parseTopic(split_message, split_params))
		return ;
	
	/*
	Parsing:
		1.	The user must be invited if the channel is invite-only;
		2.	The user's nick/username/hostname must not match any active bans;
	*/
	
	/*
		check the topic
		Check if a topic is set
		return the topic "<channel> :<topic>"
	*/
	for (size_t i = 0; i < channel.size(); i++)
	{
		std::cout << "Channel[" << i << "] == " << channel[i].getChannelName() << std::endl;
		std::cout << "Channel[" << i << "] == " << channel[i].getChannelName() << std::endl;
		if (channel[i].getChannelName() == &split_params[0][1])
		{
			if (split_params[1].empty() == 1)
			{
				sendMessage(RPL_TOPIC(getClientFduser(fd)->getNickname(), channel[i].getChannelName(), channel[i].getTopicName()), fd);
				break ;
			}
			else if (channel[i].modeIsActive('t') == 1 && channel[i].isOperator(fd) == 0)
			{
				sendMessage(ERR_CHANOPRIVSNEEDED(channel[i].getChannelName()), fd);
				return ;
			}
			const std::vector<User> cli = sockclient;
			for (size_t i = 0; i < cli.size(); i++)
			{
				// check is the client is banned;
				/*
					if (cli[i] == _banlist[j])
					{
						ERR_NOTONCHANNEL
					}
				*/
			}
		}
	}
    return ;
}