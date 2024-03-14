#include "Server.hpp"

Server::Server(char **argv)
{
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	std::cout << "Server constructed: Passive Socket == " << sockfd << std::endl;
	port = atoi(argv[1]);
	pass = argv[2];
	poll_size = 10;
}

Server::~Server()
{
	std::cout << "Server destructed" << std::endl;
	for (std::map<int, Client*>::iterator it = clients.begin(); it != clients.end(); ++it)
	{
		delete it->second;
	}
}

bool	Server::signal = false;

void	Server::signalHandler(int signum)
{
	(void)signum; // evite l'avertissement "unused parameter"
	std::cout << std::endl << "Signal Received!" << std::endl;
	Server::signal = true; // arreter le serveur
}

void    Server::initServer()
{
    struct sockaddr_in addr;

    if (sockfd == -1)
    {
        std::cerr << "Error: initServer(): socket() failed." << std::endl;
        exit(EXIT_FAILURE);
    }

	(addr).sin_family = AF_INET;
    (addr).sin_addr.s_addr = INADDR_ANY;
	(addr).sin_port = htons(port);

    int opt_val = 1;
    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &opt_val, sizeof(opt_val)) < 0)
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
    poll_fd[0].fd = sockfd;
    poll_fd[0].events = POLLIN;
    poll_fd[0].revents = 0;
	poll_num = 1;
}

// boucle qui surveille les activités des files descriptors avec poll()
void	Server::checkPoll()
{
	while (Server::signal = false)
	{
		status = poll(poll_fd, poll_num, -1);
		if (status < 0)
			break;
		else if (status == 0)
		{
			std::cout << "Waiting for connection..." << std::endl;
			continue;
		}
		for (int i = 1; i < poll_num; i++)
		{
			std::cout << "[" << poll_fd[i].fd << "] Ready" << std::endl;
			if (poll_fd[i].fd == sockfd)
				Server::newConnection();
			else
				// on regarde les datas provenant d'un user existant
		}
	}
}

// accepte une nouvelle connexion entrante sur un sockfd et récupère le fd du nouveau socket créé
void 	Server::newConnection()
{
	int	new_socket;

	new_socket = accept(sockfd, NULL, NULL);
	if (new_socket == -1) 
	{
		perror("accept");
		exit(EXIT_FAILURE);
	}
	addPoll(new_socket);
}

// ajoute un fd dans le tableaux poll_fd qui attend pour etre read/write
void	Server::addPoll()
{
	poll_fd[poll_num].fd = new_fd;
    poll_fd[poll_num].events = POLLIN | POLLOUT;
	poll_fd[poll_num].revents = 0;
    poll_num++;
}
