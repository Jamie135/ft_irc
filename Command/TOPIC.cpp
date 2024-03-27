#include "../Server/Server.hpp"

void Server::TOPIC( std::string message, int fd )
{
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
		3.	The correct key (password) must be given if it is set.
	*/
	
	/*
		check the topic
		Check if a topic is set
		return the topic "<channel> :<topic>"
	*/
	for (size_t i = 0; i < channel.size(); i++)
	{
		std::cout << "Channel[" << i << "] == " << channel[i].getChannelName() << std::endl;
		if (channel[i].getChannelName() == split_params[0])
		{
			if (channel[i].modeIsActive('t') == 1 && channel[i].isOperator(fd) == 0)
			{
				std::cerr << "Error: TOPIC(): only operator option is on." << std::endl;
				return ;
			}
			else if ()
		}
	}
    return ;
}