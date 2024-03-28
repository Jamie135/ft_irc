#define once

#define ERR_NEEDMOREPARAMS(client) (": 461 " + client + " :Not enough parameters\r\n")
#define	ERR_PASSWDMISMATCH(client) (": 464 " + client + " :Password incorrect\r\n")
#define	ERR_ALREADYREGISTERED(client) (": 462 " + client + " :You may not reregister\r\n")
#define ERR_NICKNAMEINUSE(client) (": 433 " + client + " :Nickname is already in use\r\n")
#define ERR_ERRONEUSNICKNAME(client) (": 432 " + client + " :Erroneus nickname\r\n")
#define ERR_NOTREGISTERED(client) (": 451 " + client + " :You have not registered!\r\n")
#define	ERR_NOSUCHCHANNEL(client, channel) (": 403 " + client + " " + channel + " :No such channel\r\n")
#define	ERR_CHANOPRIVSNEEDED(channel) (": 482 #" + channel + " :You're not a channel operator\r\n")
#define	ERR_UNKNOWNMODE(nickname, channel, mode) ": 472 " + nickname + " #" + channel + " " + mode + " :is not a recognised channel mode\r\n"

#define	RPL_PONG "PONG ft_irc localhost\r\n"
#define	RPL_CONNECTED(client) (": 001 " + client + " : Welcome to the ft_irc server!\r\n")
#define RPL_CHANGENICK(old, client) (":" + old + " NICK " + client + "\r\n")
#define RPL_JOIN(hostname, ipaddress, channel) (":" + hostname + "@" + ipaddress + " JOIN #" + channel + "\r\n")
#define RPL_NAMREPLY(client, channel, clientslist) (": 353 " + client + " @ #" + channel + " :" + clientslist + "\r\n")
#define RPL_ENDOFNAMES(client, channel) (": 366 " + client + " #" + channel + " :END of /NAMES list\r\n")
#define RPL_TOPIC(client, channel, topic) (": 332 " + client + " #" + channel + " :" + topic + "\r\n")
#define	RPL_YOUREOPER(client) (client + ": You are now an IRC operator\r\n")
#define	RPL_CHANNELMODEIS(client, channel, mode) ": 324 " + client + " #" + channel + " " + mode + "\r\n"
#define RPL_CREATIONTIME(client, channel, createdat) ": 329 " + client + " #" + channel + " " + createdat + "\r\n"
#define	RPL_CHANGEMODE(hostname, channel, mode, arguments) (":" + hostname + " MODE #" + channel + " " + mode + " " + arguments + "\r\n")
