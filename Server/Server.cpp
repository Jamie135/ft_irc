#include "Server.hpp"

Server::Server(char **argv)
{
	std::cout << "---------- FT_IRC SERVER ----------" << std::endl;
	this->sockfd = -1;
	port = atoi(argv[1]);
	password = argv[2];
	opt_val = 1;
	poll_size = 10;
	max_client = 10;
}

Server::Server(Server const &obj)
{
	*this = obj;
}

Server &Server::operator=(Server const &obj){
	if (this != &obj)
	{
		this->sockfd = obj.sockfd;
		this->port = obj.port;
		this->password = obj.password;
		this->sockclient = obj.sockclient;
		this->poll_fd = obj.poll_fd;
	}
	return *this;
}

Server::~Server()
{}

int	Server::getSockfd()
{
	return (this->sockfd);
}

int	Server::getPort()
{
	return (this->port);
}

std::string	Server::getPassword()
{
	return (this->password);
}

User	*Server::getClientFduser(int fd)
{
	for (size_t i = 0; i < sockclient.size(); i++)
	{
		if (this->sockclient[i].getFduser() == fd)
			return (&this->sockclient[i]);
	}
	return (NULL);
}

User	*Server::getClientNickname(std::string nickname)
{
	for (size_t i = 0; i < sockclient.size(); i++)
	{
		if (this->sockclient[i].getNickname() == nickname)
			return (&this->sockclient[i]);
	}
	return (NULL);
}

void	Server::setSockfd(int fd)
{
	this->sockfd = fd;
}

void	Server::setPort(int port)
{
	this->port = port;
}

void	Server::setPassword(std::string password)
{
	this->password = password;
}

void	Server::setClientUser(User newuser)
{
	this->sockclient.push_back(newuser);
}

void	Server::setPollfd(pollfd fd)
{
	this->poll_fd.push_back(fd);
}

void	Server::removeClientUser(int fd){
	for (size_t i = 0; i < this->sockclient.size(); i++)
	{
		if (this->sockclient[i].getFduser() == fd)
		{
			this->sockclient.erase(this->sockclient.begin() + i);
			return ;
		}
	}
}

void	Server::removeFd(int fd){
	for (size_t i = 0; i < this->poll_fd.size(); i++)
	{
		if (this->poll_fd[i].fd == fd)
		{
			this->poll_fd.erase(this->poll_fd.begin() + i);
			return;
		}
	}
}

void	Server::sendMessage(std::string message, int fd)
{
	std::cout << ">> " << message;
	if (send(fd, message.c_str(), message.size(), 0) == -1)
		std::cerr << "send() failed" << std::endl;
}
