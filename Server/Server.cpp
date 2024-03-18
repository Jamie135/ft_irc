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
	while (Server::signal == false)
	{
		status = poll(poll_fd, poll_num, -1);
		if (status < 0 && Server::signal == false)
			break;
		else if (status == 0)
		{
			std::cout << "Waiting for connection..." << std::endl;
			continue;
		}
		for (int i = 1; i < poll_num; i++)
		{
			if ((poll_fd[i].revents & POLLIN) != 1) //verfier si on peut read le socket
			{
				continue;
			}
			std::cout << "[" << poll_fd[i].fd << "] Ready" << std::endl;
			if (poll_fd[i].fd == sockfd)
				Server::acceptClient();
			else
				Server::receiveEvent(i);
		}
	}
}

// accepte une nouvelle connexion entrante sur un sockfd et récupère le fd du nouveau socket créé
void 	Server::acceptClient()
{
	int	cli_sock;
	struct sockaddr_in	client_addr;
 	socklen_t	socklen = sizeof(client_addr);

	std::cout << "listening ..." << std::endl;
	cli_sock = accept(sockfd, (sockaddr *) &client_addr, &socklen);
    if (cli_sock == -1)
    {
        std::cerr << "Error: Server::acceptClient(): accept() failed." << std::endl;
		exit(EXIT_FAILURE);
    }

	// ajoute le fd de cli_sock dans la tableau de structure pollfd a l'indice pollnum
	poll_fd[poll_num].fd = cli_sock;
    poll_fd[poll_num].events = POLLIN | POLLOUT;
	poll_fd[poll_num].revents = 0;
    poll_num++;
}

// lire les données provenant d'un socket et traite les données lues en fonction du socket expéditeur
void	Server::receiveEvent(int i)
{
	char	buf[1024] = {0}; // array pour stocker les datas recus
	int	sender_fd;
	int	bytes_read;

	sender_fd = poll_fd[i].fd;
	bytes_read = recv(sender_fd, buf, sizeof(buf) - 1, 0); // recevoir les datas du socket connecté et les stocker dans buf
	if (bytes_read <= 0) // recv retourne -1 si le socket est deconnecté, dans ce cas, on enleve le socket dans le tableau poll_fd
	{
		std::cout << "Client" << sender_fd << "disconnected" << std::endl;
		close(sender_fd);
		poll_fd[i] = poll_fd[poll_num - 1];
		poll_num--;
	}
	else
	{
		buf[bytes_read] = 0; // NULL terminated the buffer

		// ici nous allons mettre les codes de traitement des datas recus: 
		// tels que le parsing, l'authentification, les commandes, etc...

		// si le socket expéditeur n'est pas déjà enregistré dans sockclient,
		// les données lues sont ajoutées au map buffer associé au socket expéditeur,
		// puis la fonction acceptUser() est appelée pour traiter les données du client
		if (sockclient.find(sender_fd) == sockclient.end())
		{
			buffer[sender_fd] += buf;
			Server::acceptUser(sender_fd, buffer[sender_fd]);
		}
		// sinon, les données lues sont ajoutées au map buffer,
		// puis on traite les commandes
		else
		{
			buffer[sender_fd] += buf;
			// traiter les commandes
		}
	}
}

// cette fonction traite les données reçues 
// lorsqu'un nouvel utilisateur tente de se connecter au serveur, 
// elle vérifie les informations fournies par le client 
// et crée un nouvel utilisateur s'il remplit toutes les conditions nécessaires
void	Server::acceptUser(int fd, std::string str)
{
}
