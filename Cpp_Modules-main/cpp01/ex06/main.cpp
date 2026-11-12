
#include "Harl.hpp"
#include <iostream>

int	main(int ac, char **av)
{
	Harl	harl;

	if (ac == 2)
	{
		harl.complain(av[1]);
		return (0);
	}
	std::cout << "Usage: ./harlFilter <level>" << std::endl;
	std::cout << "Levels are: DEBUG - INFO - WARNING - ERROR"
		<< std::endl;
	return (0);
}
