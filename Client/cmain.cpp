#include "Client.hpp"

int	main( int argc, char **argv )
{
	if (argc != 2)
	{
		std::cout << "Error: main(): Wrong nb of arguments." << std::endl;
	}
	Client	client(argv[1]);
	
	if (client.sendConnectionRequest() != 0)
	{
		return (1);
	}
	return (0);
}