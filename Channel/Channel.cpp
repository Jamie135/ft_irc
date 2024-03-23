#include "Channel.hpp"

/* ************************************************************************** */
/* 							CONSTRUCTORS / DESTRUCTORS						  */
/* ************************************************************************** */

Channel::Channel()
{
	this->_channelName = "";
	this->_chanOps = "";
	this->_topic = "";
}

Channel::Channel(Channel const &src)
{
	*this = src;
}

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
		this->_channelName = rhs._channelName;
		this->_chanOps = rhs._chanOps;
		this->_topic = rhs._topic;
	}
	return (*this);
}

/* ************************************************************************** */
/* 								MEMBER FUNCTIONS							  */
/* ************************************************************************** */

std::string	Channel::getChannelName()
{
	return (_channelName);
}

std::string	Channel::getChanOps()
{
	return (_chanOps);
}

std::string	Channel::getTopic()
{
	return (_topic);
}

void	Channel::setChannelName(std::string name)
{
	this->_channelName = name;
}

void	Channel::setChanOps(std::string ops)
{
	this->_chanOps = ops;
}

void	Channel::setTopic(std::string topic)
{
	this->_topic = topic;
}
