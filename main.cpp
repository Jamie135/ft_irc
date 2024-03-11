#include <cstring>
#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <iomanip>
#include <cstdlib>
#include <sys/types.h>
#include <sys/socket.h>

int	main(int argc, char **argv)
{
	if (argc != 3)
	{
		std::cerr << "Error: Syntax must be ./ircserv <port> <password>";
		return (0);
	}
}