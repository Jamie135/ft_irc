#include "Channel.hpp"

/* ************************************************************************** */
/* 							CONSTRUCTORS / DESTRUCTORS						  */
/* ************************************************************************** */

Channel::Channel(std::string channelName, User &founder) : _channelName(channelName),
	_founder(founder)
{
	checkChannelName(_channelName);
	_chanOps.push_back(_founder);
	_members.push_back(_founder);
}

// Channel::Channel(Channel const &src)
// {
// 	*this = src;
// }

Channel::~Channel()
{
}

/* ************************************************************************** */
/* 									OPERATORS								  */
/* ************************************************************************** */

Channel	&Channel::operator=(Channel const &rhs)
{
	if (this != &rhs)
	{
	}
	return (*this);
}

/* ************************************************************************** */
/* 								MEMBER FUNCTIONS							  */
/* ************************************************************************** */

void	Channel::checkChannelName(std::string channnelName)
{
	if (channnelName.empty() || channnelName.size() < 2)
		throw std::runtime_error("Incorrect channel name");

	if (channnelName[0] != '&')
		throw std::runtime_error("Incorrect channel name, it must begin with &");
	for (size_t i = 0; i < channnelName.size(); ++i)
	{
		if (channnelName[i] == ' ' || channnelName[i] == 0x07 || channnelName[i] == ',')
			throw std::runtime_error("Incorrect channel name");
	}
}

void	Channel::addChanOps(User &user)
{
	for (std::vector<User>::iterator it = _chanOps.begin(); it != _chanOps.end(); ++it)
	{
		if (*it == user)
			throw std::runtime_error("User is already operator of this channel");
	}
	_chanOps.push_back(user);
}

void	Channel::removeChanOps(User &user)
{
	for (std::vector<User>::iterator it = _chanOps.begin(); it != _chanOps.end(); ++it)
	{
		if (*it == user)
		{
			_chanOps.erase(it);
		}
	}
}

void	Channel::addMember(User &user)
{
	for (std::vector<User>::iterator it = _members.begin(); it != _members.end(); ++it)
	{
		if (*it == user)
			throw std::runtime_error("User is already member of this channel");
	}
	_members.push_back(user);
}

void	Channel::removeMember(User &user)
{
	for (std::vector<User>::iterator it = _members.begin(); it != _members.end(); ++it)
	{
		if (*it == user)
		{
			_members.erase(it);
		}
	}
}

void	Channel::setTopic(std::string topic)
{
	_topic = topic;
}

void	Channel::sendMessage(std::string msg, User &author)
{
	(void)msg;
	(void)author;
}

std::string	Channel::getChannelName()
{
	return (_channelName);
}

std::string	Channel::getTopic()
{
	return (_topic);
}

