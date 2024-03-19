#include "./Server.hpp"
#include <string>

void	goToNextSpace( std::string s, size_t *i )
{
	while (s[*i] != 0 && s[*i] != ' ')
	{
		++(*i);
	}
}

// int	Server::parsePass( std::string split_mess[3] )
// {
// 	/*
// 	Example:
// 		PASS secretpasswordhere
// 	*/

// 	if (split_mess[0].empty() == 0)
// 	{
// 		std::cerr << "Error: parsePass(): prefix should be empty." << std::endl;
// 		return (1);
// 	}
// 	if (split_mess[2].empty() == 1)
// 	{
// 		std::cerr << "Error: parsePass(): parameters should not be empty." << std::endl;
// 		return (1);
// 	}
// 	return (0);
// }

int	Server::parseNick( std::string split_mess[3] )
{
	/*
	Example:
		NICK Wiz	; Introducing new nick "Wiz".
		:WiZ NICK Kilroy	; WiZ changed his nickname to Kilroy.
	*/
	if (split_mess[2].empty() == 1)
	{
		std::cerr << "Error: parseNick(): parameters can't be empty()." << std::endl;
		return (1);
	}
	if (split_mess[0].empty() == 0) // An already existing user changes nickname
	{
		/*
			Check if requesting user exists.
			Check if the new nickname is not already in use
		*/
	}	
	return (0);
}

int	Server::parseUser( std::string split_mess[3] )
{
	(void) split_mess;
	return (0);
}

int	Server::parseJoin( std::string split_mess[3] )
{
	/*
	Examples:
		JOIN #foobar
				; join channel #foobar.
		JOIN &foo fubar
				; join channel &foo using key "fubar".
		JOIN #foo,&bar fubar
				; join channel #foo using key "fubar" and &bar using no key.
		JOIN #foo,#bar fubar,foobar
				; join channel #foo using key "fubar". channel #bar using key "foobar".
		JOIN #foo,#bar
				; join channels #foo and #bar.
		:WiZ JOIN #Twilight_zone
				; JOIN message from WiZ
	*/
	
	if (split_mess[2].empty() == 1)
	{
		std::cerr << "Error: parseJoin(): parameters can't be empty." << std::endl;
		return (1);
	}
	// Check for doc to see all other errors
	return (0);
}

int Server::parsePrivmsg( std::string split_mess[3] )
{
	/*
	Examples:
		:Angel PRIVMSG Wiz :Hello are you receiving this message ?
				; Message from Angel to Wiz.
		PRIVMSG Angel :yes I'm receiving it !receiving it !'u>(768u+1n) .br
				;Message to Angel.
		PRIVMSG jto@tolsun.oulu.fi :Hello !
				; Message to a client on server tolsun.oulu.fi with username of "jto".
		PRIVMSG $*.fi :Server tolsun.oulu.fi rebooting.
				; Message to everyone on a server which has a name matching *.fi.
		PRIVMSG #*.edu :NSFNet is undergoing work, expect interruptions
				; Message to all users who come from a host which has a name matching *.edu.
	*/

	if (split_mess[2].empty() == 1)
	{
		std::cout << "Information: parsePrivmsg(): no parameters" << std::endl;
		std::cout << "> Message ignored." << std::endl;
		return (1);
	}
	return (0);
}

int	Server::splitParams( std::string params, std::string splitParams[3] )
{
	size_t	i = 0;
	size_t	k = 0;
	for (int8_t j = 0; i <= params.length() && j < 3; j++)
	{
		std::cout << ">> j == " << j << std::endl;
		k = i;
		i = params.find_first_of(" ", k);
		if (i == std::string::npos)
		{
			splitParams[j] = params.substr(k);
		}
		else if (i < params.length())
		{
			splitParams[j] = params.substr(k, i);
		}
		std::cout << "splitParams[" << (int)j << "] == [" << splitParams[j] << "]" << std::endl;
		std::cout << "i += " << (1 & (params[i] == ' ')) << std::endl;
		i += (1 & (params[i] == ' '));
	}

	return (0);
}

int	Server::parseKick( std::string split_mess[3] )
{
	std::cout << "> In Server::parseKick()" << std::endl;
	/*
	Examples:
	KICK &Melbourne Matthew
			; Kick Matthew from &Melbourne
	KICK #Finnish John :Speaking English
			; Kick John from #Finnish using "Speaking English" as the reason (comment).
	:WiZ KICK #Finnish John
			; KICK message from WiZ to remove John from channel #Finnish
	*/

	// std::cout << "splitmessage[0] == [" << split_mess[0] << "]" << std::endl;
	// std::cout << "splitmessage[1] == [" << split_mess[1] << "]" << std::endl;
	// std::cout << "splitmessage[2] == [" << split_mess[2] << "]" << std::endl;

	if (split_mess[2].empty() == 1)
	{
		std::cerr << "Error: parseKick(): no parameters" << std::endl;
		return (1);
	}
	std::string splitParams[3] = {std::string(), std::string(), std::string()};

	if (splitParams(split_mess[2], splitParams) == 1)
	{
		return (1);
	}
	
	if (splitParams[0].empty() == 0 && splitParams[1].empty() == 1)
	{
		std::cerr << "Error: parseKick(): not enough arguments" << std::endl;
		return (1);
	}

	/*
		Check if channel exists
		Check if user exists and is in the channel
		Check if user has right to run the command
		Check if user can be kicked from the channel
	*/
	
	return (0);
}

int	Server::parseInvite( std::string split_mess[3] )
{
	(void) split_mess;
	return (0);
}

int	Server::parseTopic( std::string split_mess[3] )
{
	(void) split_mess;
	return (0);
}

int	Server::parseMode( std::string split_mess[3] )
{
	(void) split_mess;
	return (0);
}

int8_t	Server::parseCommand( std::string command )
{
	/*
	NICK: Used to set or change the user's nickname.
    USER: Used to specify the username, hostname, servername, and realname of a new user.
    JOIN: Used to join a channel or a list of channels.
    PRIVMSG: Used to send a message to a specific user or channel.
    TOPIC: Used to set or query the topic of a channel.
    MODE: Used to set or query channel modes or user modes.
    KICK: Used to remove a user from a channel.
    INVITE: Used to invite a user to a channel.
	*/
	(void) command;

	std::string cmds[] = {"NICK", "USER", "JOIN", "PRIVMSG", "TOPIC", "MODE", "KICK", "INVITE"};

	for (int8_t i = 0; i < 8; i++)
	{
		if (command[0] == cmds[i][0])
		{
			return (i);
		}
	}
	return (-1);
}

int	Server::splitMessage( std::string message, std::string split_mess[3] )
{
	std::string	s_tmp;
	size_t	i = 0;

	if (message[i] == ':')
	{
		s_tmp = message.substr(0, message.find_first_of(" "));
		std::cout << "prefix == [" << s_tmp << "]" << std::endl;
		split_mess[0] = s_tmp;
		// Go to next element
		goToNextSpace(message, &i);
		i += (1 & (message[i] == ' '));
		if (message[i] == 0)
		{
			std::cout << "Quitting" << std::endl;
			return (1);
		}
	}
	else
	{
		split_mess[0] = std::string("");
	}

	s_tmp = message.substr(i, message.find_first_of(" ", i) - i);
	std::cout << "command == [" << s_tmp << "]" << std::endl;
	split_mess[1] = s_tmp;
	goToNextSpace(message, &i);
	i += (1 & (message[i] == ' '));
	if (message[i] == 0)
	{
		std::cout << "Quitting" << std::endl;
		return (1);
	}
	else
	{
		s_tmp = message.substr(i);
		std::cout << "params == [" << s_tmp << "]" << std::endl;
		split_mess[2].append(s_tmp);
	}
	return (0);
}

int	Server::parseMessage( std::string message )
{
	std::cout << "Dans parseMessage()" << std::endl;
	std::cout << "\tmessage: [" << message << "]" << std::endl;
    std::string split_mess[3] = {std::string(), std::string(), std::string()}; // [0]: prefix, [1]:command, [2]: params

	splitMessage(message, split_mess);

	std::cout << "splitmessage[0] == [" << split_mess[0] << "]" << std::endl;
	std::cout << "splitmessage[1] == [" << split_mess[1] << "]" << std::endl;
	std::cout << "splitmessage[2] == [" << split_mess[2] << "]" << std::endl;

	int8_t	cmd = parseCommand(split_mess[1]);
	if (cmd == -1)
		return (1);
	
	return ( (this->*parse[cmd])(split_mess) == 1 );
}