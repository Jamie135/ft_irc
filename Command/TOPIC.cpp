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
		ERR_NEEDMOREPARAMS: user not in a channel and does not specify a #ch 
		RPL_NOTOPIC: No topic is set in the channel
		ERR_CHANOPRIVSNEEDED: 
		ERR_NOTONCHANNEL OK
		RPL_TOPIC OK
	*/
	
	/*
		check the topic
		Check if a topic is set
		return the topic "<channel> :<topic>"
	*/
	Channel	ch = Channel();
	// Check if the channel name exists
	for (size_t i = 0; i < channel.size(); i++)
	{
		std::cout << "Channel[" << i << "] == " << channel[i].getChannelName() << std::endl;
		if (channel[i].getChannelName() == &split_params[0][1])
			ch = channel[i];
	}

	if (!split_params[0].empty() && split_params[1].empty())
	{
		// Print the channel's topic
		if (ch.getTopicName().empty() == 1)
			sendMessage(RPL_NOTOPIC(ch.getChannelName()), fd);
		else
			sendMessage(RPL_TOPIC(getClientFduser(fd)->getNickname(), ch.getChannelName(), ch.getTopicName()), fd);
		return ;
	}
	else if (split_params[0].empty())
	{
		sendMessage(ERR_NEEDMOREPARAMS(getClientFduser(fd)->getUser(), split_message[1]), fd);
		return ;
	}
	else if ( ch.isUserPresent(getClientFduser(fd)->getNickname())
		&& (!ch.modeIsActive('t') || (ch.modeIsActive('t') && ch.isOperator(fd))) )
	{
		// Change topic
		ch.setTopicName(split_params[1]);
		return ;
	}
	else
	{
		// Find the right error
		if (ch.modeIsActive('t') == 1 && ch.isOperator(fd) == 0)
		{
			// Check channel's mode and rights of user
			sendMessage(ERR_CHANOPRIVSNEEDED(ch.getChannelName()), fd);
			return ;
		}
		else if(ch.getChannelName().empty() == 1 || ch.isUserPresent(getClientFduser(fd)->getNickname()) == 0)
		{
			// Check is user is on the channel
			sendMessage(ERR_NOTONCHANNEL(split_params[0]), fd);
		}
	}
}