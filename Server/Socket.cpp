#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <poll.h>
#include "Server.hpp"

int Server::initSocket()
{
    struct sockaddr_in addr;

    if (sockfd == -1)
    {
        std::cout << "Error: init_socket(): socket() failed." << std::endl;
        exit(EXIT_FAILURE);
    }
    std::cout << "Socket == " << sockfd << std::endl;

	(addr).sin_family = AF_INET;
	(addr).sin_port = htons(port);

    int opt_val = 1;
    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &opt_val, sizeof(opt_val)) < 0)
    {
        std::cout << "Error: init_socket(): sotsockopt() failed." << std::endl;
        exit(EXIT_FAILURE);
    }
    if (fcntl(sockfd, F_SETFD, O_NONBLOCK) < 0)
    {
        std::cout << "Error: init_socket(): fcntl() failed." << std::endl;
        exit(EXIT_FAILURE);
    }
    if (bind(sockfd, (const struct sockaddr*)&addr, sizeof(const struct sockaddr)) < 0)
    {
        std::cout << "Error: init_socket(): bind() failed." << std::endl;
        exit(EXIT_FAILURE);
    }
	if (listen(sockfd, 3) < 0)
	{
		std::cout << "Error: init_socket(): bind() failed." << std::endl;
        exit(EXIT_FAILURE);
	}
    return (0);
}
