#include "Server.hpp"

Server::Server(char **argv): port(atoi(argv[1])), pass(argv[2])
{
	socklen = sizeof(addr);
}

Server::~Server()
{}

bool	Server::signal = false;


void	Server::signalHandler(int signum)
{
	(void)signum; // evite l'avertissement "unused parameter"
	std::cout << std::endl << "Signal Received!" << std::endl;
	Server::signal = true; // arreter le serveur
	exit (signum);
}

int Server::initSocket()
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

    int opt_val = 1;
    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &opt_val, sizeof(opt_val)) == -1)
    {
        std::cout << "Error: init_socket(): sotsockopt() failed." << std::endl;
        return (1);
    }
    if (fcntl(sockfd, F_SETFD, O_NONBLOCK) == -1)
    {
        std::cout << "Error: init_socket(): fcntl() failed." << std::endl;
        return (1);
    }

	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(sockfd, (const struct sockaddr*)&addr, sizeof(const struct sockaddr)) == -1)
    {
        std::cout << "Error: init_socket(): bind() failed." << std::endl;
        return (1);
    }
	if (listen(sockfd, 3) == -1)
	{
		std::cout << "Error: init_socket(): bind() failed." << std::endl;
        return (1);
	}
    std::cout << "> Server socket succesfully initilized." << std::endl;
    return (0);
}

int	Server::acceptClient( void )
{
	std::cout << "listening ..." << std::endl;
	int	cli_sock = accept(sockfd, (sockaddr *) &addr, &socklen);
    if (cli_sock == -1)
    {
        std::cout << "Error: Server::acceptClient(): accept() failed." << std::endl;
		return (1);
    }
    std::cout << "> Client: A new connection is just being accepted." << std::endl;
	char	buf[5] = {0};
	int		res = 1;
	while (res > 0)
	{
		res = recv(cli_sock, buf, 5, 0);
		if (res == -1)
		{
			std::cerr << "Error: Server::acceptClient(): recv() failed." << std::endl;
			std::cerr << "Error " << errno << ": " << strerror(errno) << std::endl;
			std::cerr << strerror(errno) << std::endl;
			return (1);
		}
		std::cout << "Message: " << std::string(buf, res) << std::endl;
		std::cout << "Bytes received: " << res << std::endl;
	}
	std::cout << "> Message from client received." << std::endl;
	return (0);
}
