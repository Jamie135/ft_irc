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

		void	setChannelName(std::string name);
		void	setChanOps(std::string ops);
		void	setTopic(std::string topic);

	private:

		std::string	_channelName;
		std::string	_chanOps;
		std::string	_topic;

		std::vector<User>	sockclient;
};

#endif