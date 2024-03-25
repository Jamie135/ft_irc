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
		std::string	getTopicName();
		std::string getChannelPass();
		std::string getChannelList();
		User	*getUserFd(int fd);
		User	*getOpFd(int fd);
		User	*getFindUser(std::string name);
		int getTopic();
		int getKey();
		int getLimit();
		int	getOnlyInvited();


		void	setChannelName(std::string name);
		void	setChanOps(std::string ops);
		void	setTopicName(std::string topic);
		void 	setChannelPass(std::string password);
		void	setTopic(int topic);
		void	setKey(int key);
		void	setLimit(int limit);
		void	setOnlyInvited(int onlyInvited);

		void	removeUser(int fd);
		void	removeOp(int fd);

		void	sendAll(std::string reply);

		size_t	numClient();
		void	checkChannelName(std::string channelName);
		void	addChanOps(User &user);
		void	addMember(User &user);
		void	sendMessage(std::string msg, User &author);

	private:

		std::string	_channelName;
		std::string	_chanOps;
		std::string	_topicname;
		std::string password;
		int	topic;
		int	key;
		int	limit;
		int	onlyInvited;

		std::vector<User>	sockclient;
		std::vector<User>	ops;
		std::vector<std::string> _modes;
};

#endif