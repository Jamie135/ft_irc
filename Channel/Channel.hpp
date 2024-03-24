#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include <iostream>
# include <string>
# include "../Server/Server.hpp"
# include "../User/User.hpp"

class User;

class Channel
{
	public:
		Channel(std::string channelName, User &founder);
		// Channel(Channel const &src);
		~Channel();

		Channel	&operator=(Channel const &rhs);

		void	checkChannelName(std::string channelName);
		void	addChanOps(User &user);
		void	removeChanOps(User &user);
		void	addMember(User &user);
		void	removeMember(User &user);
		void	setTopic(std::string topic);
		void	sendMessage(std::string msg, User &author);


		std::string	getChannelName();
		std::string	getTopic();

	private:
		std::string					_channelName;
		User						&_founder;
		std::vector<User>			_chanOps;
		std::vector<User>			_members;
		std::string					_topic;
		std::vector<std::string>	_modes;
};

#endif
