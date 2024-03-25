#define once

#define ERR_NEEDMOREPARAMS(client, command) ("461 <" + client + "> <" + command + "> : Not enough parameters\r\n")
#define	ERR_PASSWDMISMATCH(client) ("464 <" + client + "> : Password incorrect\r\n")
#define	ERR_ALREADYREGISTERED(nickname) ("462 <" + nickname + "> : You may not reregister\r\n")
#define ERR_NICKNAMEINUSE(client, nickname) ("433 <" + client + "> <" + nickname + "> : Nickname is already in use\r\n")
#define ERR_ERRONEUSNICKNAME(client, nickname) ("432 <" + client + "> <" + nickname + "> : Erroneus nickname\r\n")
#define ERR_NOTREGISTERED(nickname) ("451 <" + nickname + "> : You have not registered!\r\n")
#define ERR_NOSUCHCHANNEL(client, channel) ("403 <" + client + "> <" + channel + "> :No such channel")
#define ERR_NOTONCHANNEL(client, channel) ("442 <" + client + "> <" + channel + "> :You're not on that channel")
#define ERR_CHANOPRIVSNEEDED(client, channel) ("482 <" + client + "> <" + channel + "> :You're not channel operator")
#define ERR_USERONCHANNEL(client, nickname, channel) ("443 <" + client + "> <" + nickname + "> <" + channel + "> :is already on channel")

#define	RPL_PONG "PONG ft_irc localhost\r\n"
#define	RPL_CONNECTED(nickname) ("001 <" + nickname + "> : Welcome to the ft_irc server!\r\n")
#define RPL_CHANGENICK(old, nickname) (":" + old + " changed to " + nickname + "\r\n")
#define RPL_INVITING(client, nickname, channel) ("341" + client + nickname + channel)
