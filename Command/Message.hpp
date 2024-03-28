#define once

#define ERR_NEEDMOREPARAMS(client) (": 461 " + client + " :Not enough parameters\r\n")
#define	ERR_PASSWDMISMATCH(client) (": 464 " + client + " :Password incorrect\r\n")
#define	ERR_ALREADYREGISTERED(nickname) (": 462 " + nickname + " :You may not reregister\r\n")
#define ERR_NICKNAMEINUSE(nickname) (": 433 " + nickname + " :Nickname is already in use\r\n")
#define ERR_ERRONEUSNICKNAME(nickname) (": 432 " + nickname + " :Erroneus nickname\r\n")
#define ERR_NOTREGISTERED(nickname) (": 451 " + nickname + " :You have not registered!\r\n")
#define	ERR_NOSUCHCHANNEL(nickname, channelname) (": 403 " + nickname + " " + channelname + " :No such channel\r\n")

#define	RPL_PONG "PONG ft_irc localhost\r\n"
#define	RPL_CONNECTED(nickname) (": 001 " + nickname + " : Welcome to the ft_irc server!\r\n")
#define RPL_CHANGENICK(old, nickname) (":" + old + " NICK " + nickname + "\r\n")
#define RPL_JOIN(hostname, ipaddress, channelname) (":" + hostname + "@" + ipaddress + " JOIN #" + channelname + "\r\n")
#define RPL_NAMREPLY(nickname, channelname, clientslist) (": 353 " + nickname + " @ #" + channelname + " :" + clientslist + "\r\n")
#define RPL_ENDOFNAMES(nickname, channelname) (": 366 " + nickname + " #" + channelname + " :END of /NAMES list\r\n")
#define RPL_TOPIC(nickname, channelname, topic) (": 332 " + nickname + " #" + channelname + " :" + topic + "\r\n")
#define	RPL_YOUREOPER(nickname) (nickname + ": You are now an IRC operator\r\n")
