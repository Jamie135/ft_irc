#include "Server.hpp"

bool	Server::signal = false;

void    Server::initServer()
{
    struct sockaddr_in addr;

	addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
	addr.sin_port = htons(port);
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
    {
        std::cerr << "Error: initServer(): socket() failed." << std::endl;
        exit(EXIT_FAILURE);
    }
    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, (char *)&opt_val, sizeof(opt_val)) < 0)
    {
        std::cerr << "initServer(): sotsockopt() failed." << std::endl;
        exit(EXIT_FAILURE);
    }
    if (fcntl(sockfd, F_SETFD, O_NONBLOCK) < 0)
    {
        std::cerr << "initServer(): fcntl() failed." << std::endl;
        exit(EXIT_FAILURE);
    }
    if (bind(sockfd, (const struct sockaddr*)&addr, sizeof(const struct sockaddr)) < 0)
    {
        std::cerr << "initServer(): bind() failed." << std::endl;
        exit(EXIT_FAILURE);
    }
	if (listen(sockfd, 3) < 0)
	{
		std::cerr << "initServer(): listen() failed." << std::endl;
        exit(EXIT_FAILURE);
	}
	std::cout << "Passive socket: FD[" << sockfd << "]" << std::endl;
	addr_len = sizeof(addr);
    new_client.fd = sockfd;
    new_client.events = POLLIN;
    new_client.revents = 0;
	poll_fd.push_back(new_client);
}

// boucle qui surveille les activités des files descriptors avec poll()
void	Server::checkPoll()
{
	std::cout << "Waiting for a connection...\n";
	while (Server::signal == false)
	{
		status = poll(&poll_fd[0], poll_fd.size(), -1);
		if (status < 0 && Server::signal == false)
			throw(std::runtime_error("poll() failed"));
		for (size_t i = 0; i < poll_fd.size(); i++)
		{
			if (poll_fd[i].revents & POLLIN) //verfier si on peut read le socket
			{
				if (poll_fd[i].fd == sockfd)
					Server::acceptClient();
				else
					Server::receiveEvent(poll_fd[i].fd);
			}
		}
	}
	closeFd();
}

// accepte une nouvelle connexion entrante sur un sockfd et récupère le fd du nouveau socket créé
void 	Server::acceptClient()
{
	User	client;
	int	cli_sock;
	struct sockaddr_in	client_addr;
 	socklen_t	socklen = sizeof(client_addr);

	cli_sock = accept(sockfd, (sockaddr *)&client_addr, &socklen);
    if (cli_sock == -1)
    {
        std::cerr << "Error: Server::acceptClient(): accept() failed." << std::endl;
		exit(EXIT_FAILURE);
    }
	if (fcntl(cli_sock, F_SETFL, O_NONBLOCK) == -1)
	{
		std::cerr << "Error: Server::acceptClient(): fcntl() failed." << std::endl;
		exit(EXIT_FAILURE);
	}
	new_client.fd = cli_sock;
    new_client.events = POLLIN | POLLOUT;
	new_client.revents = 0;
	client.setFduser(cli_sock);
	client.setIp(inet_ntoa(client_addr.sin_addr));
	sockclient.push_back(client);
	poll_fd.push_back(new_client);
	std::cout << "FD[" << cli_sock << "] connected" << std::endl;
}

// lire les données provenant d'un socket et traite les données lues en fonction du socket expéditeur
void	Server::receiveEvent(int fd)
{
	User	*client;
	char	buf[1024]; // array pour stocker les datas recus
	int	bytes;
	std::vector<std::string> command;

	client = getClientFduser(fd);
	memset(buf, 0, sizeof(buf));
	bytes = recv(fd, buf, sizeof(buf) - 1, 0); // recevoir les datas du socket connecté et les stocker dans buf
	if (bytes <= 0) // recv retourne -1 si le socket est deconnecté, dans ce cas, on enleve le socket dans le tableau poll_fd
	{
		std::cout << "FD[" << fd << "] disconnected" << std::endl;
		clearChannel(fd);
		removeClientUser(fd);
		removeFd(fd);
		close(fd);
	}
	else
	{
		client->setBuffer(buf);
		// std::cout << "buf:\n" << buf << std::endl;
		if (client->getBuffer().find_first_of("\r\n") == std::string::npos)
			return ;
		command = splitBuffer(client->getBuffer());
		for (size_t i = 0; i < command.size(); i++)
		{
			// std::cout << "command[" << i << "]: " << command[i] << std::endl;
			this->parseCommandList(command[i], fd);
		}
		if (getClientFduser(fd)) // clear le buffer si le user existe toujours
			getClientFduser(fd)->removeBuffer();
	}
}

void	Server::closeFd()
{
	for (size_t i = 0; i < sockclient.size(); i++)
	{
		std::cout << "FD[" << sockfd << "] disconnected" << std::endl;
		close(sockclient[i].getFduser());
	}
	if (sockfd != -1)
	{
		std::cout << "Server (FD[" << sockfd << "]) disconnected" << std::endl;
		close(sockfd);
	}
}

void	Server::signalHandler(int signum)
{
	(void)signum; // evite l'avertissement "unused parameter"
	std::cout << " signal received!" << std::endl;
	Server::signal = true; // arreter le serveur
}
