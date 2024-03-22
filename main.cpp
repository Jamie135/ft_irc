#include <iostream>
#include <cstring>
#include <cerrno>
#include <map>
#include <vector>
#include <sys/socket.h> // for socket()
#include <sys/types.h> // for socket()
#include <netinet/in.h> // for sockaddr_in
#include <fcntl.h> // for fcntl() in mac
#include <unistd.h> // for close()
#include <arpa/inet.h> // for inet_ntoa()
#include <poll.h> // for poll()
#include <csignal> // for signal()
#include "./Server/Server.hpp"

int	main(int argc, char **argv)
{
	Server	serv(argv);

	if (argc != 3)
	{
		std::cerr << "Error: Syntax must be ./ircserv <port> <password>";
		return (0);
	}
	try
	{
		signal(SIGINT, Server::signalHandler);
		signal(SIGQUIT, Server::signalHandler);
		serv.initServer();
		serv.checkPoll();
	}
	catch(const std::exception& e)
	{
		serv.closeFd();
		std::cerr << e.what() << std::endl;
	}
	return (0);
}

// int	main( int argc, char **argv )
// {
// 	if (argc != 3)
// 	{
// 		std::cerr << "Error: Syntax must be ./ircserv <port> <password>";
// 		return (0);
// 	}


// 	Server	serv(argv);
// 	std::string message;

// 	message = std::string("NICK Wiz");
// 	serv.parseMessage(message);
// 	std::cout << std::endl << std::endl;
// 	message = std::string(":WiZ NICK Kilroy");
// 	serv.parseMessage(message);
// 	std::cout << std::endl << std::endl;

// 	message = std::string("JOIN #foobar");
// 	serv.parseMessage(message);
// 	std::cout << std::endl << std::endl;
// 	message = std::string("JOIN &foo fubar");
// 	serv.parseMessage(message);
// 	std::cout << std::endl << std::endl;
// 	message = std::string("JOIN #foo,&bar fubar");
// 	serv.parseMessage(message);
// 	std::cout << std::endl << std::endl;
// 	message = std::string("JOIN #foo,#bar fubar,foobar");
// 	serv.parseMessage(message);
// 	std::cout << std::endl << std::endl;
// 	message = std::string("JOIN #foo,#bar");
// 	serv.parseMessage(message);
// 	std::cout << std::endl << std::endl;
// 	message = std::string(":WiZ JOIN #Twilight_zone");
// 	serv.parseMessage(message);
// 	std::cout << std::endl << std::endl;

// 	message = std::string(":Angel PRIVMSG Wiz :Hello are you receiving this message ?");
// 	serv.parseMessage(message);
// 	std::cout << std::endl << std::endl;
// 	message = std::string("PRIVMSG Angel :yes I'm receiving it !receiving it !'u>(768u+1n) .br");
// 	serv.parseMessage(message);
// 	std::cout << std::endl << std::endl;
// 	message = std::string("PRIVMSG jto@tolsun.oulu.fi :Hello !");
// 	serv.parseMessage(message);
// 	std::cout << std::endl << std::endl;
// 	message = std::string("PRIVMSG $*.fi :Server tolsun.oulu.fi rebooting.");
// 	serv.parseMessage(message);
// 	std::cout << std::endl << std::endl;
// 	message = std::string("PRIVMSG #*.edu :NSFNet is undergoing work, expect interruptions");
// 	serv.parseMessage(message);
// 	std::cout << std::endl << std::endl;

// 	message = std::string("KICK &Melbourne Matthew");
// 	serv.parseMessage(message);
// 	std::cout << std::endl << std::endl;
// 	message = std::string("KICK #Finnish John :Speaking English");
// 	serv.parseMessage(message);
// 	std::cout << std::endl << std::endl;
// 	message = std::string(":WiZ KICK #Finnish John");
// 	serv.parseMessage(message);
// 	std::cout << std::endl << std::endl;

// 	message = std::string(":Angel INVITE Wiz #Dust");
// 	serv.parseMessage(message);
// 	std::cout << std::endl << std::endl;
// 	message = std::string("INVITE Wiz #Twilight_Zone");
// 	serv.parseMessage(message);
// 	std::cout << std::endl << std::endl;

// 	message = std::string(":Wiz TOPIC #test :New topic");
// 	serv.parseMessage(message);
// 	std::cout << std::endl << std::endl;
// 	message = std::string("TOPIC #test :another topic");
// 	serv.parseMessage(message);
// 	std::cout << std::endl << std::endl;
// 	message = std::string("TOPIC #test");
// 	serv.parseMessage(message);
// 	std::cout << std::endl << std::endl;

// 	message = std::string("MODE #Finnish +im");
// 	serv.parseMessage(message);
// 	std::cout << std::endl << std::endl;
// 	message = std::string("MODE #Finnish +o Kilroy");
// 	serv.parseMessage(message);
// 	std::cout << std::endl << std::endl;
// 	message = std::string("MODE #Finnish +v Wiz");
// 	serv.parseMessage(message);
// 	std::cout << std::endl << std::endl;
// 	message = std::string("MODE #Fins -s");
// 	serv.parseMessage(message);
// 	std::cout << std::endl << std::endl;
// 	message = std::string("MODE #42 +k oulu");
// 	serv.parseMessage(message);
// 	std::cout << std::endl << std::endl;
// 	message = std::string("MODE #eu-opers +l 10");
// 	serv.parseMessage(message);
// 	std::cout << std::endl << std::endl;
// 	message = std::string("MODE &oulu +b");
// 	serv.parseMessage(message);
// 	std::cout << std::endl << std::endl;
// 	message = std::string("MODE &oulu +b *!*@*");
// 	serv.parseMessage(message);
// 	std::cout << std::endl << std::endl;
// 	message = std::string("MODE &oulu +b *!*@*.edu");
// 	serv.parseMessage(message);
// 	std::cout << std::endl << std::endl;

// 	return (0);
// }
