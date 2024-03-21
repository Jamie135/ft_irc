#include "Server.hpp"

Server::Server(char **argv)
{
	std::cout << "Server constructed" << std::endl;
	port = atoi(argv[1]);
	password = argv[2];
	opt_val = 1;
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
	std::cout << "Passive socket = " << sockfd << std::endl;
	addr_len = sizeof(addr);
    new_client.fd = sockfd;
    new_client.events = POLLIN;
    new_client.revents = 0;
	poll_fd.push_back(new_client);
}

// boucle qui surveille les activités des files descriptors avec poll()
void	Server::checkPoll()
{
	std::cout << "Waiting to accept a connection...\n";
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
}

// accepte une nouvelle connexion entrante sur un sockfd et récupère le fd du nouveau socket créé
void 	Server::acceptClient()
{
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
	// ajoute le fd de cli_sock dans la tableau de structure pollfd a l'indice pollnum
	new_client.fd = cli_sock;
    new_client.events = POLLIN | POLLOUT;
	new_client.revents = 0;
	poll_fd.push_back(new_client);
}

// lire les données provenant d'un socket et traite les données lues en fonction du socket expéditeur
void	Server::receiveEvent(int fd)
{
	char	buf[1024] = {0}; // array pour stocker les datas recus
	int	bytes_read;

	bytes_read = recv(fd, buf, sizeof(buf) - 1, 0); // recevoir les datas du socket connecté et les stocker dans buf
	if (bytes_read <= 0) // recv retourne -1 si le socket est deconnecté, dans ce cas, on enleve le socket dans le tableau poll_fd
	{
		std::cout << "FD[" << fd << "] disconnected" << std::endl;
		close(fd);
	}
	else
	{
		buf[bytes_read] = 0; // NULL terminated the buffer

		// ici nous allons mettre les codes de traitement des datas recus: 
		// tels que le parsing, l'authentification, les commandes, etc...

		// si le socket expéditeur n'est pas déjà enregistré dans sockclient,
		// les données lues sont ajoutées au map buffer associé au socket expéditeur,
		// puis la fonction acceptUser() est appelée pour traiter les données du client
		std::cout << "FD[" << fd << "] connected" << std::endl;
		if (sockclient.find(fd) == sockclient.end())
		{
			buffer[fd] += buf;
			Server::acceptUser(fd, buffer[fd]);
		}
		// sinon, les données lues sont ajoutées au map buffer,
		// puis on traite les commandes
		else
		{
			buffer[fd] += buf;
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
		// std::cout << "compare: " << pass.compare(this->password) << std::endl;
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
