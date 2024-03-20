#include <iostream>
#include <vector> //-> for vector
#include <sys/socket.h> //-> for socket()
#include <sys/types.h> //-> for socket()
#include <netinet/in.h> //-> for sockaddr_in
#include <fcntl.h> //-> for fcntl() in mac
#include <unistd.h> //-> for close()
#include <arpa/inet.h> //-> for inet_ntoa()
#include <poll.h> //-> for poll()
#include <csignal> //-> for signal()
#include "./Server.hpp"

// int	main(int argc, char **argv)
// {
// 	if (argc != 3)
// 	{
// 		std::cerr << "Error: Syntax must be ./ircserv <port> <password>";
// 		return (0);
// 	}

// 	Server	serv(argv);
// 	serv.initSocket();
// 	try
// 	{
// 		signal(SIGINT, Server::signalHandler);
// 		signal(SIGQUIT, Server::signalHandler);
// 	}
// 	catch(const std::exception& e)
// 	{
// 		std::cerr << e.what() << std::endl;
// 	}
// 	if (serv.acceptClient() != 0)
// 	{
// 		return (1);
// 	}
// 	return (0);
// }

int	main( int argc, char **argv )
{
	if (argc != 3)
	{
		std::cerr << "Error: Syntax must be ./ircserv <port> <password>";
		return (0);
	}


	Server	serv(argv);
	std::string message;
	
	// message = std::string(":sender PRIVMSG #channel :Hello, everyone!");
	// serv.parseMessage(message);
	// std::cout << std::endl << std::endl;
	// message = std::string("PASS secretpasswordhere");
	// serv.parseMessage(message);
	// std::cout << std::endl << std::endl;
	// message = std::string(":WiZ NICK Kilroy");
	// serv.parseMessage(message);
	// std::cout << std::endl << std::endl;
	// message = std::string("JOIN #foo,#bar fubar,foobar");
	// serv.parseMessage(message);
	// std::cout << std::endl << std::endl;
	// message = std::string(":Wiz TOPIC #test :New topic ");
	// serv.parseMessage(message);
	// std::cout << std::endl << std::endl;
	// message = std::string(":Angel INVITE Wiz #Dust");
	// serv.parseMessage(message);
	// std::cout << std::endl << std::endl;
	// message = std::string("");
	// serv.parseMessage(message);

	std::cout << std::endl << std::endl;
	// message = std::string(":WiZ KICK #Finnish John");
	message = std::string(":WiZ KICK #Finnish");
	serv.parseMessage(message);

	return (0);
}