#define once

#define ERR_NEEDMOREPARAMS(str) (": 461 " + str + " :Not enough parameters\r\n")
#define	ERR_PASSWDMISMATCH(str) (": 464 " + str + " :Password incorrect\r\n")
#define	ERR_ALREADYREGISTERED(nickname) (": 462 " + nickname + " :You may not reregister\r\n")