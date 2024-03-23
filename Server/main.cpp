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

int	main( void )
{

	Server	serv(NULL);
	std::string message;

	std::cout << "\t---- NICK ----" << std::endl;
	message = std::string("NICK Wiz");
	std::cout << "NICK Wiz : ";
	if (serv.parseMessage(message) == 0)
		std::cout << GRN << "> OK <" << WHT << std::endl;
	else
		std::cout << RED << "> KO <" << WHT << std::endl;
	
	message = std::string(":WiZ NICK Kilroy");
	std::cout << ":WiZ NICK Kilroy : ";
	if (serv.parseMessage(message) == 0)
		std::cout << GRN << "> OK <" << WHT << std::endl;
	else
		std::cout << RED << "> KO <" << WHT << std::endl;

	message = std::string("NICK");
	std::cout << "NICK : ";
	if (serv.parseMessage(message) == 1)
		std::cout << GRN << "> OK <" << WHT << std::endl;
	else
		std::cout << RED << "> KO <" << WHT << std::endl;

	message = std::string("NICK ddjak adjnkcda djakfhdjk");
	std::cout << "NICK : ";
	if (serv.parseMessage(message) == 1)
		std::cout << GRN << "> OK <" << WHT << std::endl;
	else
		std::cout << RED << "> KO <" << WHT << std::endl;

	// =========================================================================
	std::cout << "\t---- JOIN ----" << std::endl;
	message = std::string("JOIN #foobar");
	std::cout << "JOIN #foobar : ";
	if (serv.parseMessage(message) == 0)
		std::cout << GRN << "> OK <" << WHT << std::endl;
	else
		std::cout << RED << "> KO <" << WHT << std::endl;

	message = std::string("JOIN &foo fubar");
	std::cout << "JOIN &foo fubar : ";
	if (serv.parseMessage(message) == 0)
		std::cout << GRN << "> OK <" << WHT << std::endl;
	else
		std::cout << RED << "> KO <" << WHT << std::endl;

	message = std::string("JOIN #foo,&bar fubar");
	std::cout << "JOIN #foo,&bar fubar : ";
	if (serv.parseMessage(message) == 0)
		std::cout << GRN << "> OK <" << WHT << std::endl;
	else
		std::cout << RED << "> KO <" << WHT << std::endl;

	message = std::string("JOIN #foo,#bar fubar,foobar");
	std::cout << "JOIN #foo,#bar fubar,foobar : ";
	if (serv.parseMessage(message) == 0)
		std::cout << GRN << "> OK <" << WHT << std::endl;
	else
		std::cout << RED << "> KO <" << WHT << std::endl;

	message = std::string("JOIN #foo,#bar");
	std::cout << "JOIN #foo,#bar : ";
	if (serv.parseMessage(message) == 0)
		std::cout << GRN << "> OK <" << WHT << std::endl;
	else
		std::cout << RED << "> KO <" << WHT << std::endl;

	message = std::string(":WiZ JOIN #Twilight_zone");
	std::cout << ":WiZ JOIN #Twilight_zone : ";
	if (serv.parseMessage(message) == 0)
		std::cout << GRN << "> OK <" << WHT << std::endl;
	else
		std::cout << RED << "> KO <" << WHT << std::endl;
	std::cout << std::endl;

	message = std::string(":WiZ JOIN");
	std::cout << ":WiZ JOIN : ";
	if (serv.parseMessage(message) == 1)
		std::cout << GRN << "> OK <" << WHT << std::endl;
	else
		std::cout << RED << "> KO <" << WHT << std::endl;
	std::cout << std::endl;

	message = std::string("JOIN");
	std::cout << "JOIN : ";
	if (serv.parseMessage(message) == 1)
		std::cout << GRN << "> OK <" << WHT << std::endl;
	else
		std::cout << RED << "> KO <" << WHT << std::endl;
	std::cout << std::endl;

	message = std::string(":WiZ JOIN #Twilight_zone bonjour aurevoir");
	std::cout << ":WiZ JOIN #Twilight_zone bonjour aurevoir : ";
	if (serv.parseMessage(message) == 1)
		std::cout << GRN << "> OK <" << WHT << std::endl;
	else
		std::cout << RED << "> KO <" << WHT << std::endl;
	std::cout << std::endl;


	// =========================================================================
	std::cout << "\t---- PRIVMSG ----" << std::endl;
	message = std::string(":Angel PRIVMSG Wiz :Hello are you receiving this message ?");
	std::cout << ":Angel PRIVMSG Wiz :Hello are you receiving this message ? : ";
	if (serv.parseMessage(message) == 0)
		std::cout << GRN << "> OK <" << WHT << std::endl;
	else
		std::cout << RED << "> KO <" << WHT << std::endl;

	message = std::string("PRIVMSG Angel :yes I'm receiving it !receiving it !'u>(768u+1n) .br");
	std::cout << "PRIVMSG Angel :yes I'm receiving it !receiving it !'u>(768u+1n) .br : ";
	if (serv.parseMessage(message) == 0)
		std::cout << GRN << "> OK <" << WHT << std::endl;
	else
		std::cout << RED << "> KO <" << WHT << std::endl;

	message = std::string("PRIVMSG jto@tolsun.oulu.fi :Hello !");
	std::cout << "PRIVMSG jto@tolsun.oulu.fi :Hello ! : ";
	if (serv.parseMessage(message) == 0)
		std::cout << GRN << "> OK <" << WHT << std::endl;
	else
		std::cout << RED << "> KO <" << WHT << std::endl;

	message = std::string("PRIVMSG $*.fi :Server tolsun.oulu.fi rebooting.");
	std::cout << "PRIVMSG $*.fi :Server tolsun.oulu.fi rebooting. : ";
	if (serv.parseMessage(message) == 0)
		std::cout << GRN << "> OK <" << WHT << std::endl;
	else
		std::cout << RED << "> KO <" << WHT << std::endl;

	message = std::string("PRIVMSG #*.edu :NSFNet is undergoing work, expect interruptions");
	std::cout << "PRIVMSG #*.edu :NSFNet is undergoing work, expect interruptions : ";
	if (serv.parseMessage(message) == 0)
		std::cout << GRN << "> OK <" << WHT << std::endl;
	else
		std::cout << RED << "> KO <" << WHT << std::endl;
	std::cout << std::endl;

	message = std::string("PRIVMSG :NSFNet is undergoing work, expect interruptions");
	std::cout << "PRIVMSG :NSFNet is undergoing work, expect interruptions : ";
	if (serv.parseMessage(message) == 1)
		std::cout << GRN << "> OK <" << WHT << std::endl;
	else
		std::cout << RED << "> KO <" << WHT << std::endl;
	std::cout << std::endl;

	message = std::string("PRIVMSG #*.edu :");
	std::cout << "PRIVMSG #*.edu : : ";
	if (serv.parseMessage(message) == 0)
		std::cout << GRN << "> OK <" << WHT << std::endl;
	else
		std::cout << RED << "> KO <" << WHT << std::endl;
	std::cout << std::endl;

	message = std::string("PRIVMSG #*.edu");
	std::cout << "PRIVMSG #*.edu : ";
	if (serv.parseMessage(message) == 1)
		std::cout << GRN << "> OK <" << WHT << std::endl;
	else
		std::cout << RED << "> KO <" << WHT << std::endl;
	std::cout << std::endl;

	message = std::string("PRIVMSG");
	std::cout << "PRIVMSG : ";
	if (serv.parseMessage(message) == 1)
		std::cout << GRN << "> OK <" << WHT << std::endl;
	else
		std::cout << RED << "> KO <" << WHT << std::endl;
	std::cout << std::endl;

	message = std::string("PRIVMSG #* :NSFNet is undergoing work, expect interruptions :");
	std::cout << "PRIVMSG #* :NSFNet is undergoing work, expect interruptions : ";
	if (serv.parseMessage(message) == 1)
		std::cout << GRN << "> OK <" << WHT << std::endl;
	else
		std::cout << RED << "> KO <" << WHT << std::endl;
	std::cout << std::endl;

	// =========================================================================
	std::cout << "\t---- KICK ----" << std::endl;
	message = std::string("KICK &Melbourne Matthew");
	std::cout << "KICK &Melbourne Matthew : ";
	if (serv.parseMessage(message) == 0)
		std::cout << GRN << "> OK <" << WHT << std::endl;
	else
		std::cout << RED << "> KO <" << WHT << std::endl;

	message = std::string("KICK #Finnish John :Speaking English");
	std::cout << "KICK #Finnish John :Speaking English : ";
	if (serv.parseMessage(message) == 0)
		std::cout << GRN << "> OK <" << WHT << std::endl;
	else
		std::cout << RED << "> KO <" << WHT << std::endl;

	message = std::string(":WiZ KICK #Finnish John");
	std::cout << ":WiZ KICK #Finnish John : ";
	if (serv.parseMessage(message) == 0)
		std::cout << GRN << "> OK <" << WHT << std::endl;
	else
		std::cout << RED << "> KO <" << WHT << std::endl;
	std::cout << std::endl;

	message = std::string(":WiZ KICK");
	std::cout << ":WiZ KICK : ";
	if (serv.parseMessage(message) == 1)
		std::cout << GRN << "> OK <" << WHT << std::endl;
	else
		std::cout << RED << "> KO <" << WHT << std::endl;
	std::cout << std::endl;

	message = std::string(":WiZ KICK John");
	std::cout << ":WiZ KICK John : ";
	if (serv.parseMessage(message) == 1)
		std::cout << GRN << "> OK <" << WHT << std::endl;
	else
		std::cout << RED << "> KO <" << WHT << std::endl;
	std::cout << std::endl;

	message = std::string(":WiZ KICK #channel");
	std::cout << ":WiZ KICK #channel : ";
	if (serv.parseMessage(message) == 1)
		std::cout << GRN << "> OK <" << WHT << std::endl;
	else
		std::cout << RED << "> KO <" << WHT << std::endl;
	std::cout << std::endl;

	// =========================================================================
	std::cout << "\t---- INVITE ----" << std::endl;
	message = std::string(":Angel INVITE Wiz #Dust");
	std::cout << ":Angel INVITE Wiz #Dust : ";
	if (serv.parseMessage(message) == 0)
		std::cout << GRN << "> OK <" << WHT << std::endl;
	else
		std::cout << RED << "> KO <" << WHT << std::endl;

	message = std::string("INVITE Wiz #Twilight_Zone");
	std::cout << "INVITE Wiz #Twilight_Zone : ";
	if (serv.parseMessage(message) == 0)
		std::cout << GRN << "> OK <" << WHT << std::endl;
	else
		std::cout << RED << "> KO <" << WHT << std::endl;
	std::cout << std::endl;

	message = std::string("INVITE Wiz ");
	std::cout << "INVITE Wiz : ";
	if (serv.parseMessage(message) == 1)
		std::cout << GRN << "> OK <" << WHT << std::endl;
	else
		std::cout << RED << "> KO <" << WHT << std::endl;
	std::cout << std::endl;

	message = std::string("INVITE #Twilight_Zone");
	std::cout << "INVITE #Twilight_Zone : ";
	if (serv.parseMessage(message) == 1)
		std::cout << GRN << "> OK <" << WHT << std::endl;
	else
		std::cout << RED << "> KO <" << WHT << std::endl;
	std::cout << std::endl;

	message = std::string("INVITE");
	std::cout << "INVITE : ";
	if (serv.parseMessage(message) == 1)
		std::cout << GRN << "> OK <" << WHT << std::endl;
	else
		std::cout << RED << "> KO <" << WHT << std::endl;
	std::cout << std::endl;

	message = std::string("INVITE #Wiz Twilight_Zone");
	std::cout << "INVITE #Wiz Twilight_Zone : ";
	if (serv.parseMessage(message) == 1)
		std::cout << GRN << "> OK <" << WHT << std::endl;
	else
		std::cout << RED << "> KO <" << WHT << std::endl;
	std::cout << std::endl;

	message = std::string("INVITE Wiz Twilight_Zone");
	std::cout << "INVITE Wiz Twilight_Zone : ";
	if (serv.parseMessage(message) == 1)
		std::cout << GRN << "> OK <" << WHT << std::endl;
	else
		std::cout << RED << "> KO <" << WHT << std::endl;
	std::cout << std::endl;

	message = std::string("INVITE #Wiz #Twilight_Zone");
	std::cout << "INVITE #Wiz #Twilight_Zone : ";
	if (serv.parseMessage(message) == 1)
		std::cout << GRN << "> OK <" << WHT << std::endl;
	else
		std::cout << RED << "> KO <" << WHT << std::endl;
	std::cout << std::endl;

	message = std::string("INVITE Wiz #");
	std::cout << "INVITE Wiz # : ";
	if (serv.parseMessage(message) == 1)
		std::cout << GRN << "> OK <" << WHT << std::endl;
	else
		std::cout << RED << "> KO <" << WHT << std::endl;
	std::cout << std::endl;

	// =========================================================================
	std::cout << "\t---- TOPIC ----" << std::endl;
	message = std::string(":Wiz TOPIC #test :New topic");
	std::cout << ":Wiz TOPIC #test :New topic : ";
	if (serv.parseMessage(message) == 0)
		std::cout << GRN << "> OK <" << WHT << std::endl;
	else
		std::cout << RED << "> KO <" << WHT << std::endl;

	message = std::string("TOPIC #test :another topic");
	std::cout << "TOPIC #test :another topic : ";
	if (serv.parseMessage(message) == 0)
		std::cout << GRN << "> OK <" << WHT << std::endl;
	else
		std::cout << RED << "> KO <" << WHT << std::endl;

	message = std::string("TOPIC #test");
	std::cout << "TOPIC #test : ";
	if (serv.parseMessage(message) == 0)
		std::cout << GRN << "> OK <" << WHT << std::endl;
	else
		std::cout << RED << "> KO <" << WHT << std::endl;
	std::cout << std::endl;

	message = std::string("TOPIC test");
	std::cout << "TOPIC test : ";
	if (serv.parseMessage(message) == 1)
		std::cout << GRN << "> OK <" << WHT << std::endl;
	else
		std::cout << RED << "> KO <" << WHT << std::endl;
	std::cout << std::endl;

	message = std::string("TOPIC #test :topic dnjakc");
	// std::cout << "TOPIC #test :topic dnjakc : ";
	// if (serv.parseMessage(message) == 1)
	// 	std::cout << GRN << "> OK <" << WHT << std::endl;
	// else
	// 	std::cout << RED << "> KO <" << WHT << std::endl;
	// std::cout << std::endl;
	// =========================================================================
	std::cout << "\t---- MODE ----" << std::endl;
	message = std::string("MODE #Finnish +im");
	std::cout << "ODE #Finnish +im : ";
	if (serv.parseMessage(message) == 0)
		std::cout << GRN << "> OK <" << WHT << std::endl;
	else
		std::cout << RED << "> KO <" << WHT << std::endl;

	message = std::string("MODE #Finnish +o Kilroy");
	std::cout << "MODE #Finnish +o Kilroy : ";
	if (serv.parseMessage(message) == 0)
		std::cout << GRN << "> OK <" << WHT << std::endl;
	else
		std::cout << RED << "> KO <" << WHT << std::endl;

	message = std::string("MODE #Finnish +v Wiz");
	std::cout << "MODE #Finnish +v Wiz : ";
	if (serv.parseMessage(message) == 0)
		std::cout << GRN << "> OK <" << WHT << std::endl;
	else
		std::cout << RED << "> KO <" << WHT << std::endl;

	message = std::string("MODE #Fins -s");
	std::cout << "MODE #Fins -s : ";
	if (serv.parseMessage(message) == 0)
		std::cout << GRN << "> OK <" << WHT << std::endl;
	else
		std::cout << RED << "> KO <" << WHT << std::endl;

	message = std::string("MODE #42 +k oulu");
	std::cout << "MODE #42 +k oulu : ";
	if (serv.parseMessage(message) == 0)
		std::cout << GRN << "> OK <" << WHT << std::endl;
	else
		std::cout << RED << "> KO <" << WHT << std::endl;

	message = std::string("MODE #eu-opers +l 10");
	std::cout << "MODE #eu-opers +l 10 : ";
	if (serv.parseMessage(message) == 0)
		std::cout << GRN << "> OK <" << WHT << std::endl;
	else
		std::cout << RED << "> KO <" << WHT << std::endl;

	message = std::string("MODE &oulu +b");
	std::cout << "MODE &oulu +b : ";
	if (serv.parseMessage(message) == 0)
		std::cout << GRN << "> OK <" << WHT << std::endl;
	else
		std::cout << RED << "> KO <" << WHT << std::endl;

	message = std::string("MODE &oulu +b *!*@*");
	std::cout << "MODE &oulu +b *!*@* : ";
	if (serv.parseMessage(message) == 0)
		std::cout << GRN << "> OK <" << WHT << std::endl;
	else
		std::cout << RED << "> KO <" << WHT << std::endl;

	message = std::string("MODE &oulu +b *!*@*.edu");
	std::cout << "MODE &oulu +b *!*@*.edu : ";
	if (serv.parseMessage(message) == 0)
		std::cout << GRN << "> OK <" << WHT << std::endl;
	else
		std::cout << RED << "> KO <" << WHT << std::endl;
	std::cout << std::endl;

	message = std::string("MODE WiZ -w");
	std::cout << message << " : ";
	if (serv.parseMessage(message) == 0)
		std::cout << GRN << "> OK <" << WHT << std::endl;
	else
		std::cout << RED << "> KO <" << WHT << std::endl;
	std::cout << std::endl;

	message = std::string(":Angel MODE Angel +i");
	std::cout << message << " : ";
	if (serv.parseMessage(message) == 0)
		std::cout << GRN << "> OK <" << WHT << std::endl;
	else
		std::cout << RED << "> KO <" << WHT << std::endl;
	std::cout << std::endl;

	message = std::string("MODE WiZ -o");
	std::cout << message << " : ";
	if (serv.parseMessage(message) == 0)
		std::cout << GRN << "> OK <" << WHT << std::endl;
	else
		std::cout << RED << "> KO <" << WHT << std::endl;
	std::cout << std::endl;

	message = std::string("MODE");
	std::cout << "MODE : ";
	if (serv.parseMessage(message) == 1)
		std::cout << GRN << "> OK <" << WHT << std::endl;
	else
		std::cout << RED << "> KO <" << WHT << std::endl;
	std::cout << std::endl;

	message = std::string("MODE &oulou");
	std::cout << "MODE &oulou : ";
	if (serv.parseMessage(message) == 1)
		std::cout << GRN << "> OK <" << WHT << std::endl;
	else
		std::cout << RED << "> KO <" << WHT << std::endl;
	std::cout << std::endl;

	message = std::string("MODE +s");
	std::cout << "MODE +s : ";
	if (serv.parseMessage(message) == 1)
		std::cout << GRN << "> OK <" << WHT << std::endl;
	else
		std::cout << RED << "> KO <" << WHT << std::endl;
	std::cout << std::endl;

	message = std::string("MODE +soi");
	std::cout << "MODE +soi : ";
	if (serv.parseMessage(message) == 1)
		std::cout << GRN << "> OK <" << WHT << std::endl;
	else
		std::cout << RED << "> KO <" << WHT << std::endl;
	std::cout << std::endl;

	message = std::string("MODE +b *!*@*.edu");
	std::cout << "MODE +b *!*@*.edu : ";
	if (serv.parseMessage(message) == 1)
		std::cout << GRN << "> OK <" << WHT << std::endl;
	else
		std::cout << RED << "> KO <" << WHT << std::endl;
	std::cout << std::endl;

	message = std::string("MODE #42 +k");
	std::cout << "MODE #42 +k : ";
	if (serv.parseMessage(message) == 1)
		std::cout << GRN << "> OK <" << WHT << std::endl;
	else
		std::cout << RED << "> KO <" << WHT << std::endl;
	std::cout << std::endl;

	return (0);
}