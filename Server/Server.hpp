#pragma once

#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <cerrno>
#include <ctime>
#include <stdio.h>
#include <sstream>
#include <algorithm>
#include <map>
#include <vector>
#include <sys/socket.h> // for socket()
#include <sys/types.h> // for socket()
#include <netinet/in.h> // for sockaddr_in
#include <fcntl.h> // for fcntl() in mac
#include <unistd.h> // for close()
#include <arpa/inet.h> // for inet_ntoa()
#include <poll.h> // for poll()
#include <csignal> // for signal()
#include "../User/User.hpp"
#include "../Channel/Channel.hpp"
#include "../Command/Message.hpp"

class User;
class Channel;

class Server
{
private:

	int	sockfd;
	int	port;
	std::string	password;
	int	poll_size;
	int	status;
	int	max_client;
	int opt_val;
	int	addr_len;
	static bool signal;
	struct pollfd	new_client;
	std::vector<struct pollfd>	poll_fd;
	std::vector<User>	sockclient;
	std::vector<Channel>	channel;
	std::map<int, std::string>	buffer;
	int	(Server::*parse[8])(std::string split_mess[3]);

public:

	Server(char **argv);
	Server(Server const &obj);
	Server &operator=(Server const &obj);
	~Server();

	// Getters
	int	getSockfd();
	int	getPort();
	std::string	getPassword();
	User	*getClientFduser(int fd);
	User	*getClientNickname(std::string nickname);

	// Setters
	void	setSockfd(int sockfd);
	void	setPort(int port);
	void	setPassword(std::string password);
	void	setClientUser(User newuser);
	void	setPollfd(pollfd fd);

	// Removers
	void	removeClientUser(int fd);
	void	removeFd(int fd);
	void	clearChannel(int fd);

	// Send Methods
	void	sendMessage(std::string message, int fd);
	void	sendMessage2(int errnum, std::string user, std::string channel, int fd, std::string message);
	void	sendMessage3(int errnum, std::string user, int fd, std::string message);

	// Utils Methods
	bool	isRegistered(int fd);

	// ServerInit Methods
	void	initServer();
	void	checkPoll();
	void	acceptClient();
	void	acceptUser(int fd, std::string buff);
	void	receiveEvent(int fd);
	void	closeFd();
	static void	signalHandler(int signum);

	// ServerParsing Methods
	int	splitMessage( std::string message, std::string split_mess[3] );
	int	splitParams( std::string params, std::string split_params[3] );
	int	parseNick( std::string split_mess[3] );
	int	parseUser( std::string split_mess[3] );
	int	parseJoin( std::string split_mess[3] );
	int	parsePrivmsg( std::string split_mess[3] );
	int	parseTopic( std::string split_mess[3] );
	int	parseMode( std::string split_mess[3] );
	int	parseKick( std::string split_mess[3] );
	int	parseInvite( std::string split_mess[3] );
	int8_t	parseCommand( std::string command );
	std::vector<std::string>	splitParam(std::string &message);
	std::vector<std::string>	parseMessage( std::string &message );
	std::vector<std::string>	splitBuffer(std::string buffer);
	void	parseCommandList(std::string &command, int fd);

	// Command Methods
	void	PASS(std::string message, int fd);

	void	NICK(std::string message, int fd);
	bool	usedNickname(std::string &nickname);
	bool	validNickname(std::string &nickname);

	void	USER(std::string &message, int fd);

	void	QUIT(std::string message, int fd);
	std::string	quitReason(std::string message);
	void	quitFormatReason(std::string message, std::string str, std::string &reason);
	
	void	PING(std::string &message, int fd);

	void	JOIN(std::string message, int fd);
	int	splitJoin(std::vector<std::pair<std::string, std::string> > &param, std::string message, int fd);
	void	addToExistChannel(std::vector<std::pair<std::string, std::string> > &param, int i , int j, int fd);
	void	addToNewChannel(std::vector<std::pair<std::string, std::string> >&param, int i, int fd);
	int	countJoinedChannel(std::string user);
	bool	isInvited(User *user, std::string channel, int flag);

	void	PART(std::string message, int fd);
	int	splitPart(std::string message, std::vector<std::string> &param, std::string &reason, int fd);
	std::string	splitPartReason(std::string &message, std::vector<std::string> &param);
	void	findReason(std::string message, std::string tofind, std::string &reason);
};
