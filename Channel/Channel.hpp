#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include <iostream>
# include <string>
# include "../User/User.hpp"

class User;

class Channel
{
	public:
		Channel(std::string channelName, std::string owner);
		Channel(Channel const &src);
		~Channel();

		Channel	&operator=(Channel const &rhs);

		std::string	getChannelName();
		std::string	getChanOps();
		std::string	getTopic();

	private:
		std::string	_channelName;
		std::string	_chanOps;
		std::string	_topic;
};

#endif