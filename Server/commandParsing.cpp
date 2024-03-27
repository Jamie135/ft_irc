#include "./Server.hpp"
#include <string>

void	goToNextSpace( std::string s, size_t *i )
{
	while (s[*i] != 0 && s[*i] != ' ')
	{
		++(*i);
	}
}

bool	Server::splitParams( std::string params, std::string splitParams[3] )
{
	size_t	i = 0;
	size_t	k = 0;
	for (int8_t j = 0; i < params.length() && j < 3; j++)
	{
		k = i;
		i = params.find_first_of(" ", k);
		if (i == std::string::npos
			|| (j >= 1 && params[k] == ':'))
		{
			splitParams[j] = params.substr(k);
			break ;
		}
		else if (i < params.length())
			splitParams[j] = params.substr(k, i - k);
		i += (1 & (params[i] == ' '));
	}
	return (0);
}

bool	Server::checkOption( std::string opt )
{
	return (opt.empty() == 1
	|| (opt[0] != '+' && opt[0] != '-')
	|| (opt.length() == 1));
}

bool	Server::checkChannel( std::string ch )
{
	return (ch.empty() == 1
	|| (ch[0] != '#' && ch[0] != '&')
	|| ch.length() == 1);
}

bool	Server::checkPrefix( std::string pref )
{
	return (pref.empty() == 1
	|| pref[0] != ':'
	|| pref.length() == 1);
}

int	Server::parseNick( std::string split_mess[3] )
{
	/*
	Example:
		NICK Wiz	; Introducing new nick "Wiz".
		:WiZ NICK Kilroy	; WiZ changed his nickname to Kilroy.
	*/
	if (split_mess[2].empty() == 1)
	{
		std::cerr << "Error: parseNick(): no nickname given." << std::endl;
		return (1);
	}
	std::string split_params[3] = {std::string(), std::string(), std::string()};
	if (splitParams(split_mess[2], split_params) == 1)
	{
		return (1);
	}
	if (split_params[1].empty() == 0)
	{
		std::cerr << "Error: parseJoin(): too much parameters." << std::endl;
		return (1);
	}
	if (split_mess[0].empty() == 0) // An already existing user changes nickname
	{
		/*
			Check if requesting user exists.
			Check if the new nickname is not already in use
		*/
	}
	else // A new nickname is requested
	{
		/*
			Check if nickname requested is available
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

	std::string split_params[3] = {std::string(), std::string(), std::string()};
	if (splitParams(split_mess[2], split_params) == 1)
	{
		return (1);
	}
	if (split_params[2].empty() == 0)
	{
		std::cerr << "Error: parseJoin(): too much parameters." << std::endl;
		return (1);
	}

	if (split_params[0].empty() == 1)	
	{
		std::cerr << "Error: parseJoin(): need more params.(no parameters given)" << std::endl;
		return (1);
	}
	/*
		if ( channel requires a key )
			check if split_params[1].empty() == 0
		check if channel is invite only
		check if channel is full
		check if channel exists
		check if user is banned form channel
		check if user is concerned by the ban mask
		check if key is correct
		check if the user joined a limit number of channels
	*/
	
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
		std::cerr << "Error: parsePrivmsg(): need more parameters.(no parameters)" << std::endl;
		return (1);
	}
	std::string split_params[3] = {std::string(), std::string(), std::string()};
	if (splitParams(split_mess[2], split_params) == 1)
	{
		return (1);
	}
	// std::cout << "Split_params[0] == [" << split_params[0] << "]" << std::endl;
	// std::cout << "Split_params[1] == [" << split_params[1] << "]" << std::endl;
	// std::cout << "Split_params[2] == [" << split_params[2] << "]" << std::endl;
	if (checkPrefix(split_params[0]))
	{
		std::cerr << "Error: parsePrivmsg(): invalid prefix." << std::endl;
		return (1);
	}
	else if (split_params[0].find_first_of(".", 0) == std::string::npos)
	{
		std::cerr << "Error: parsePrivmsg(): receiver parameter syntax error.(must have a '.')" << std::endl;
		return (1);
	}

	if (split_params[1].empty() == 1)
	{
		std::cerr << "Error: parsePrivmsg(): need more parameters.(trail param empty)" << std::endl;
		return (1);
	}
	else
	{
		if (split_params[1][0] != ':')	
		{
			std::cerr << "Error: parsePrivmsg(): trail parameter syntax error." << std::endl;
			return (1);
		}
		else if (split_params[1].length() == 1)
		{
			std::cout << "Information: parsePrivmsg(): empty message will be ignored." << std::endl;
		}
	}

	if (split_params[2].empty() == 0)
	{
		std::cerr << "Error: parsePrivmsg(): toot much parameters." << std::endl;
		return (1);
	}
	
	return (0);
}

int	Server::parseKick( std::string split_mess[3] )
{
	// std::cout << "> In Server::parseKick()" << std::endl;
	/*
	Examples:
	KICK &Melbourne Matthew
			; Kick Matthew from &Melbourne
	KICK #Finnish John :Speaking English
			; Kick John from #Finnish using "Speaking English" as the reason (comment).
	:WiZ KICK #Finnish John
			; KICK message from WiZ to remove John from channel #Finnish
	*/

	if (split_mess[2].empty() == 1)
	{
		std::cerr << "Error: parseKick(): no parameters" << std::endl;
		return (1);
	}
	std::string split_params[3] = {std::string(), std::string(), std::string()};
	if (splitParams(split_mess[2], split_params) == 1)
	{
		return (1);
	}
	
	if (split_params[0].empty() == 1)
	{
		std::cerr << "Error: parseKick(): not enough arguments(no channel name)" << std::endl;
		return (1);
	}
	else if (split_params[1].empty() == 1)
	{
		std::cerr << "Error: parseKick(): not enough arguments(no user name)" << std::endl;
		return (1);
	}
	
	if (split_params[0][0] != '#' && split_params[0][0] != '&')
	{
		std::cerr << "Error: parseKick(): invalid parameters.(miss '#' || '&' for channel)" << std::endl;
		return (1);
	}
	else if (split_params[0][1] == 0)
	{
		std::cerr << "Error: parseKick(): invalid parameters.(channel name == \"#\" or \"&\")" << std::endl;
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
	/*
	Examples:
		:Angel INVITE Wiz #Dust
				; User Angel inviting WiZ to channel #Dust
		INVITE Wiz #Twilight_Zone
				; Command to invite WiZ to #Twilight_zone
	*/
	(void) split_mess;
	if (split_mess[2].empty() == 1)
	{
		std::cerr << "Error: parseInvite(): not enough arguments." << std::endl;
		return (1);
	}

	std::string split_params[3] = {std::string(), std::string(), std::string()};
	if (splitParams(split_mess[2], split_params) == 1)
	{
		return (1);
	}
	
	if (split_params[0].empty() == 1)
	{
		std::cerr << "Error: parseInvite(): not enough arguments(no user name)" << std::endl;
		return (1);
	}
	else if (split_params[1].empty() == 1)
	{
		std::cerr << "Error: parseInvite(): not enough arguments(no channel name)" << std::endl;
		return (1);
	}
	else if (split_params[2].empty() == 0)
	{
		std::cerr << "Error: parseInvite(): invalid arguments.(too much arguments)" << std::endl;
		return (1);
	}
	
	if (isalpha(split_params[0][0]) == 0)
	{
		std::cerr << "parseInvite(): invalide parameters.(Invalid nickname)" << std::endl;
		return (1);
	}
	else if (split_params[1][0] != '#' && split_params[1][0] != '&')
	{
		std::cerr << "parseInvite(): invalid parameters.(second param not a channel name)" << std::endl;
		return (1);
	}
	else if (split_params[1].length() < 2)
	{
		std::cerr << "parseInvite(): invalid parameters.(channel name == \"#\" or \"&\")" << std::endl;
		return (1);
	}
	
	/*
		Check if user exists
		Check if channel exists
		Check if user is not banned from the channel
		Check if user is not ALREADY on the channel
	*/

	if (split_mess[0].empty() == 0)
	{
		/*
			Check if :sender exists
			Check if :sender has needed rights (is operator | is on channel)
		*/
	}

	// return RPL_INVITING "<channel> <nick>"
	return (0);
}

int	Server::parseTopic( std::string split_mess[3] )
{
	/*
	Examples:
		:Wiz TOPIC #test :New topic
				;User Wiz setting the topic.
		TOPIC #test :another topic
				;set the topic on #test to "another topic".
		TOPIC #test
				; check the topic for #test.
	*/
	if (split_mess[2].empty() == 1)
	{
		std::cerr << "Error: parseTopic(): no parameters" << std::endl;
		return (1);
	}

	std::string split_params[3] = {std::string(), std::string(), std::string()};
	if (splitParams(split_mess[2], split_params) == 1)
	{
		return (1);
	}

	if (split_params[0].empty() == 1)
	{
		std::cerr << "Error: parseInvite(): not enough arguments(no user name)" << std::endl;
		return (1);
	}
	else if (split_params[2].empty() == 0)
	{
		std::cerr << "Error: parseInvite(): invalid arguments.(too much arguments)" << std::endl;
		return (1);
	}

	// std::cout << "Split_params[0] == [" << split_params[0] << "]" << std::endl;
	// std::cout << "Split_params[1] == [" << split_params[1] << "]" << std::endl;
	// std::cout << "Split_params[2] == [" << split_params[2] << "]" << std::endl;
	if (checkChannel(split_params[0]))
	{
		std::cerr << "Error: parseTopic(): invalid arguments.(First arg is not a channel)" << std::endl;
		return (1);
	}

	if (split_params[1].empty() == 1)
	{
		// Print the channel topic
	}
	else if (split_params[1][0] != ':')
	{
		std::cerr << "parseTopic(): invalid parameters.(no trail parameter)" << std::endl;
		return (1);
	}
	else if (split_params[1].length() < 2)
	{
		std::cerr << "parseTopic(): invalid parameters.(trail parameter is empty" << std::endl;
		return (1);
	}
	
	/*
		check the topic
		Check if a topic is set
		return the topic "<channel> :<topic>"
	*/

	if (split_mess[0].empty() == 0)
	{
		/*
			Check if :sender is on the channel
			Check if :sender has the needed rights
		*/
	}
	return (0);
}

int	Server::parseMode( std::string split_mess[3] )
{
	/*
	Examples:
		Channel Mode:
		MODE #Finnish +im
				; Makes #Finnish channel moderated and 'invite-only'.
		MODE #Finnish +o Kilroy
				; Gives 'chanop' privileges to Kilroy on channel #Finnish.
		MODE #Finnish +v Wiz
				; Allow WiZ to speak on #Finnish.
		MODE #Fins -s
				; Removes 'secret' flag from channel #Fins.
		MODE #42 +k oulu
				; Set the channel key to "oulu".
		MODE #eu-opers +l 10
				; Set the limit for the number of users on channel to 10.
		MODE &oulu +b
				; list ban masks set for channel.
		MODE &oulu +b *!*@*
				; prevent all users from joining.
		MODE &oulu +b *!*@*.edu
				; prevent any user from a hostname matching *.edu from joining.

		User Mode:
		:MODE WiZ -w
				; turns reception of WALLOPS messages off for WiZ.
		:Angel MODE Angel +i
				; Message from Angel to make themselves invisible.
		MODE WiZ -o
				; WiZ 'deopping' (removing operator	status).  The plain reverse of this
				command ("MODE WiZ +o") must not be allowed from users since would bypass
				the OPER command.
	*/
	if (split_mess[2].empty() == 1)
	{
		std::cerr << "Error: parseMode(): no parameters" << std::endl;
		return (1);
	}
	std::string split_params[3] = {std::string(), std::string(), std::string()};

	if (splitParams(split_mess[2], split_params) == 1 || split_params[0].empty() == 1)
	{
		return (1);
	}
	// std::cout << "Split_params[0] == [" << split_params[0] << "]" << std::endl;
	// std::cout << "Split_params[1] == [" << split_params[1] << "]" << std::endl;
	// std::cout << "Split_params[2] == [" << split_params[2] << "]" << std::endl;
	if (split_params[1].find_first_not_of("+-opsitnmlbvkws") != std::string::npos)
	{
		std::cerr << "Error: parseMode(): invalid parameters.(option)" << std::endl;
		return (1);
	}
	else if (checkOption(split_params[1]))
	{
		std::cerr << "Error: parseMode(): invalid parameters.(+|-)" << std::endl;
		return (1);
	}
	else if (split_mess[0].empty() == 0 && split_mess[0][0] != ':')
	{
		std::cerr << "Error: parseMode(): invalid prefix." << std::endl;
		return (1);
	}

	if (split_params[0][0] == '#' || split_params[0][0] == '&')
	{
				//	Channel mode
		/*
			Check if channel name valid
			Check if channel name exists
			Check if channel name is associated with the right symbol (#|&)
		*/
		if (split_params[1].find_first_not_of("+-opsitnmlbvk") != std::string::npos)
		{
			std::cerr << "Error: parseMode(): invalid arguments.(channel mode wrong option)" << std::endl;
			return (1);
		}

		if (split_params[1].find_first_of("olvk") != std::string::npos)
		{
			//	Checks for MODE #channel [+|-]opt
			if (split_params[2].empty() == 1)
			{
				std::cerr << "Error: parseMode(): invalid arguments.(ovkl No arguments)" << std::endl;
				return (1);
			}

		}
		else if (split_params[1].find_first_of("psitnm") != std::string::npos)
		{
			if (split_params[2].empty() == 0)
			{
				std::cerr << "Error: parseMode(): invalid arguments.(non-arg options has argument)" << std::endl;
				return (1);
			}
		}
	}
	else
	{
		if (split_params[2].find_first_not_of("+-iwso") != std::string::npos)
		{
			if (split_mess[2].empty() == 1 || split_params[0].empty() == 1 || split_params[1].empty() == 1)
			{
				std::cerr << "Error: parseMode(): need more argument.(user mode need argument)" << std::endl;
				return (1);
			}
			else
			{
				if (split_mess[0].compare(":" + split_params[0]) != 0)
				{
					std::cerr << "Error: parseMode(): invalid arguments.(:sender != <nickname>)" << std::endl;
					return (1);
				}
			}
		}
		else
		{
			/*
				Check if is user exists
				Check if user is on the channel
			*/
		}
	}
	
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

	// std::string cmds[] = {"NICK", "USER", "JOIN", "PRIVMSG", "TOPIC", "MODE", "KICK", "INVITE"};
	char cmds[] = {'N', 'U', 'J', 'P', 'T', 'M', 'K', 'I'};

	for (int8_t i = 0; i < 8; i++)
	{
		if (command[0] == cmds[i])
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
		// std::cout << "prefix == [" << s_tmp << "]" << std::endl;
		split_mess[0] = s_tmp;
		// Go to next element
		goToNextSpace(message, &i);
		i += (1 & (message[i] == ' '));
		if (message[i] == 0)
		{
			// std::cout << "Quitting" << std::endl;
			return (1);
		}
	}
	else
	{
		split_mess[0] = std::string();
	}

	s_tmp = message.substr(i, message.find_first_of(" ", i) - i);
	// std::cout << "command == [" << s_tmp << "]" << std::endl;
	split_mess[1] = s_tmp;
	goToNextSpace(message, &i);
	i += (1 & (message[i] == ' '));
	if (message[i] == 0)
	{
		// std::cout << "Quitting" << std::endl;
		return (1);
	}
	else
	{
		s_tmp = message.substr(i);
		split_mess[2].append(s_tmp);
	}
	return (0);
}

int	Server::parseMessage( std::string message )
{
	// std::cout << "Dans parseMessage()" << std::endl;
	// std::cout << "\tmessage: [" << message << "]" << std::endl;
	if (message.empty() == 1)
	{
		return (1);
	}
	
    std::string split_mess[3] = {std::string(), std::string(), std::string()};
								// [0]: prefix, [1]:command, [2]: params

	splitMessage(message, split_mess);

	// std::cout << "splitmessage[0] == [" << split_mess[0] << "]" << std::endl;
	// std::cout << "splitmessage[1] == [" << split_mess[1] << "]" << std::endl;
	// std::cout << "splitmessage[2] == [" << split_mess[2] << "]" << std::endl;

	int8_t	cmd = parseCommand(split_mess[1]);
	if (cmd == -1)
		return (1);
	
	return ( (this->*parse[cmd])(split_mess) == 1 );
}