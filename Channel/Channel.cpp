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

User	*Channel::getUserFd(int fd)
{
	for (std::vector<User>::iterator it = sockclient.begin(); it != sockclient.end(); ++it)
	{
		if (it->getFduser() == fd)
			return &(*it);
	}
	return (NULL);
}

User	*Channel::getOpFd(int fd)
{
	for (std::vector<User>::iterator it = ops.begin(); it != ops.end(); ++it)
	{
		if (it->getFduser() == fd)
			return &(*it);
	}
	return (NULL);
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

void	Channel::removeUser(int fd)
{
	for (std::vector<User>::iterator it = sockclient.begin(); it != sockclient.end(); ++it)
	{
		if (it->getFduser() == fd)
		{
			sockclient.erase(it);
			break;
		}
	}
}

void	Channel::removeOp(int fd)
{
	for (std::vector<User>::iterator it = ops.begin(); it != ops.end(); ++it)
	{
		if (it->getFduser() == fd)
		{
			ops.erase(it);
			break;
		}
	}
}

void	Channel::addMember(User &user)
{
	for (std::vector<User>::iterator it = sockclient.begin(); it != sockclient.end(); ++it)
	{
		if (*it == user)
			throw std::runtime_error("User is already member of this channel");
	}
	sockclient.push_back(user);
}

void	Channel::addChanOps(User &user)
{
	for (std::vector<User>::iterator it = ops.begin(); it != ops.end(); ++it)
	{
		if (*it == user)
			throw std::runtime_error("User is already operator of this channel");
	}
	ops.push_back(user);
}

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

size_t	Channel::numClient()
{
	size_t	num;
	
	num = this->sockclient.size() + this->ops.size();
	return (num);
}

// envoyer un message à tous les users et opérateurs présents dans le canal
void	Channel::sendAll(std::string reply)
{
	for (size_t i = 0; i < ops.size(); i++)
	{
		if (send(ops[i].getFduser(), reply.c_str(), reply.size(), 0) == -1)
			std::cerr << "send() failed" << std::endl;
	}
	for (size_t i = 0; i < sockclient.size(); i++)
	{
		if (send(sockclient[i].getFduser(), reply.c_str(), reply.size(), 0) == -1)
			std::cerr << "send() failed" << std::endl;
	}
}

void	Channel::sendMessage(std::string msg, User &author)
{
	(void)msg;
	(void)author;
}
