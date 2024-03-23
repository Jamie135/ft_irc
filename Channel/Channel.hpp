#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include "../Server/Server.hpp"
# include "../User/User.hpp"

class User;

class Channel
{
	public:

		Channel();
		Channel(Channel const &src);
		Channel	&operator=(Channel const &rhs);
		~Channel();

		std::string	getChannelName();
		std::string	getChanOps();
		std::string	getTopic();
		User	*getUserFd(int fd);
		User	*getOpFd(int fd);

		void	setChannelName(std::string name);
		void	setChanOps(std::string ops);
		void	setTopic(std::string topic);

		void	removeUser(int fd);
		void	removeOp(int fd);

		void	sendAll(std::string reply);

		size_t	numClient();

	private:

		std::string	_channelName;
		std::string	_chanOps;
		std::string	_topic;

		std::vector<User>	sockclient;
		std::vector<User>	ops;
};

#endif