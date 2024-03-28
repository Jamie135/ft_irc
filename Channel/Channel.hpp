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
		std::string	getTopicName();
		std::string getChannelPass();
		std::string getChannelList();
		std::string	getCreatedAt();
		std::string	getMode();
		User	*getUserFd(int fd);
		User	*getOpFd(int fd);
		User	*getFindUser(std::string name);
		int getTopic();
		int getKey();
		int getLimit();
		int	getOnlyInvited();
		bool	getModeOption(size_t i);

		void	setChannelName(std::string name);
		void	setTopicName(std::string topic);
		void 	setChannelPass(std::string password);
		void	setTopic(int topic);
		void	setKey(int key);
		void	setLimit(int limit);
		void	setOnlyInvited(int onlyInvited);
		void	setMode(size_t i, bool mode);
		void	setCreatedAt();

		void	removeUser(int fd);
		void	removeOp(int fd);

		void	sendAll(std::string reply);
		void	sendAll2(std::string reply, int fd);

		size_t	numClient();
		bool	isUserPresent(std::string &name);
		void	checkChannelName(std::string channelName);
		void	addChanOps(User user);
		void	addMember(User user);
		bool	userToOp(std::string& name);
		bool	opToUser(std::string& name);
		void	sendMessage(std::string msg, User &author);

	private:

		std::string	_channelName;
		std::string	_topicname;
		std::string password;
		std::string created_at;
		int	topic;
		int	key;
		int	limit;
		int	onlyInvited;

		std::vector<User>	sockclient;
		std::vector<User>	ops;
		std::vector<std::pair<char, bool> > _modes;
};

#endif