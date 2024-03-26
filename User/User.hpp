#pragma once

#include "../Server/Server.hpp"
#include "../Channel/Channel.hpp"

class Channel;

class User
{
private:
	int	fdUser;
	std::string	nickname;
	std::string	user;
	std::string ip;
	std::string buffer;
	bool	registered;
	bool	connected;
	bool	isOp;
	std::vector<std::string>	invitation;
public:
	User();
	User(int fd, std::string nickname, std::string user);
	User(User const &obj);
	User &operator=(User const &obj);
	bool operator==(User const &rhs);
	~User();

	int	getFduser();
	std::string	getNickname();
	std::string	getUser();
	std::string	getIp();
	std::string	getBuffer();
	std::string getHostname();
	bool	getRegistered();
	bool	getConnected();
	bool	getInvited(std::string &channel);
	bool	getOp();

	void	setFduser(int fd);
	void	setNickname(std::string &nickname);
	void	setUser(std::string &user);
	void	setIp(std::string ip);
	void	setBuffer(std::string recv);
	void	setRegistered(bool val);
	void	setConnected(bool val);
	void	setOp(bool op);

	void	removeBuffer();
	void	removeInvite(std::string &channel);
};
