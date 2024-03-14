#include "Server.hpp"

void    Server::initSocket()
{
    struct sockaddr_in addr;

    if (sockfd == -1)
    {
        std::cerr << "Error: init_socket(): socket() failed." << std::endl;
        exit(EXIT_FAILURE);
    }

	(addr).sin_family = AF_INET;
    (addr).sin_addr.s_addr = INADDR_ANY;
	(addr).sin_port = htons(port);

    int opt_val = 1;
    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &opt_val, sizeof(opt_val)) < 0)
    {
        std::cerr << "init_socket(): sotsockopt() failed." << std::endl;
        exit(EXIT_FAILURE);
    }
    if (fcntl(sockfd, F_SETFD, O_NONBLOCK) < 0)
    {
        std::cerr << "init_socket(): fcntl() failed." << std::endl;
        exit(EXIT_FAILURE);
    }
    if (bind(sockfd, (const struct sockaddr*)&addr, sizeof(const struct sockaddr)) < 0)
    {
        std::cerr << "init_socket(): bind() failed." << std::endl;
        exit(EXIT_FAILURE);
    }
	if (listen(sockfd, 3) < 0)
	{
		std::cerr << "init_socket(): listen() failed." << std::endl;
        exit(EXIT_FAILURE);
	}
    addr_len = sizeof(addr);
    poll_fd[0].fd = sockfd;
    poll_fd[0].events = POLLIN;
    poll_fd[0].revents = 0;
}
