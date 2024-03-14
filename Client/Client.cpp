#include "./Client.hpp"

Client::Client( void )
{}

Client::Client( char *arg ): port(atoi(arg))
{
    if (initSocket() != 0)
    {
        return ;
    }
}

Client::~Client()
{}

int Client::initSocket( void )
{
    if (sockfd != 0)
    {
        std::cout << "Error: init_socket(): parameter not initialized." << std::endl;
        return (1);
    }

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1)
    {
        std::cout << "Error: init_socket(): socket() failed." << std::endl;
        return (1);
    }
    std::cout << "Socket == " << sockfd << std::endl;
	
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	addr.sin_addr.s_addr = INADDR_ANY;

    std::cout << "> Client socket succesfully initialized." << std::endl;
    return (0);
}

int	Client::sendConnectionRequest( void )
{
    if (connect(sockfd, (sockaddr *) &addr, sizeof(addr)) == -1)
    {
        std::cerr << "Error: sendConnectionRequest(): connect() failed." << std::endl;
		std::cerr << "Error " << errno << ": " << strerror(errno) << std::endl;
		return (1);
    }
	std::cout << "> Client: Connect been accepted." << std::endl;
	// if (accept(sockfd, (sockaddr *) &addr, &socklen) == -1)
    // {
    //     std::cout << "Error: Client::sendConnectionRequest(): accept() failed." << std::endl;
	// 	return (1);
    // }
	std::string s("Bonjour du client! Je t'envoie un long message pour tester les limites des fonctions.");
	send(sockfd, s.c_str(), s.length(), 0);
	return (0);
}
