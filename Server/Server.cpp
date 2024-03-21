#include "Server.hpp"

Server::Server(char **argv)
{
	std::cout << "Server constructed" << std::endl;
	port = atoi(argv[1]);
	password = argv[2];
	poll_size = 10;
	max_client = 10;
}

Server::~Server()
{
	std::cout << "Server destroyed" << std::endl;
	for (std::map<int, User*>::iterator it = sockclient.begin(); it != sockclient.end(); ++it)
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

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
    {
        std::cerr << "Error: initServer(): socket() failed." << std::endl;
        exit(EXIT_FAILURE);
    }

	std::cout << "Passive socket = " << sockfd << std::endl;
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
		status = poll(poll_fd, poll_num, 5000);
		if (status < 0 && Server::signal == false)
			break;
		else if (status == 0)
		{
			std::cout << "Waiting for connection..." << std::endl;
			continue;
		}
		for (int i = 0; i < poll_num; i++)
		{
			if ((poll_fd[i].revents & POLLIN) != 1) //verfier si on peut read le socket
			{
				continue;
			}
			if (poll_fd[i].fd == sockfd)
			{
				Server::acceptClient();
			}
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
		std::cout << "FD[" << sender_fd << "] disconnected" << std::endl;
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
			std::cout << "FD[" << poll_fd[i].fd << "] connected" << std::endl;
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

// cette fonction va traiter les données reçues 
// lorsqu'un nouvel utilisateur tente de se connecter au serveur, 
// elle va vérifier les informations fournies par le client 
// et créer un nouvel utilisateur s'il remplit toutes les conditions nécessaires
void	Server::acceptUser(int fd, std::string buff)
{
	// std::cout << "buff:\n" << buff << std::endl;

	std::string	cap_ls;
	std::string pass;
	std::string nickname;
	int	endline;
	std::string	error;

	if (std::count(buff.begin(), buff.end(), '\n') < 3)
		return;
	endline = buff.find('\n');
	cap_ls = buff.substr(0, endline);
	std::cout << cap_ls << std::endl;
	buff.erase(0, endline + 1);
	endline = buff.find('\n');
	pass = buff.substr(0, endline);

	// vérifie si la ligne du mot de passe contient "PASS :"
	if (pass.find("PASS ") == std::string::npos)
	{
		std::cout << "Missing password" << std::endl;
		error = ":localhost 461 PASS :\n";
		send(fd, error.c_str(), error.length(), 0);
		buffer[fd] = "";
		return ;
	}
	pass = pass.substr(5);
	// vérifie si le mot de passe est correcte
	if (pass.compare(this->password) != 0)
	{
		// std::cout << "pass: " << pass << std::endl;
		// std::cout << "password: " << this->password << std::endl;
		std::cout << "Wrong password" << std::endl;
		error = ":localhost 461 PASS :\n";
		send(fd, error.c_str(), error.length(), 0);
		buffer[fd] = "";
		return ;
	}
	buff.erase(0, endline + 1);
	endline = buff.find('\n');
	nickname = buff.substr(0, endline);
	nickname = nickname.substr(5);
	std::cout << nickname << std::endl;

	// vérifie si le nickname est deja pris
	for (std::map<int, User*>::iterator it = sockclient.begin(); it != sockclient.end(); it++)
	{
		if (it->second->getNickName() == nickname)
		{
			error = ":localhost 433 " + nickname + " :\n";
			send(fd, error.c_str(), error.length(), 0);
			buffer[fd] = "";
			return ;
		}
	}
	buff.erase(0, endline + 1);
	sockclient[fd] = new User(fd, nickname);
	buffer[fd] = "";
}
