
#include <iostream>
#include "Fixed.hpp"

int	main(void)
{
	Fixed	first;
	Fixed	copy(first);
	Fixed	assigned;

	assigned = copy;

	std::cout << first.getRawBits() << std::endl;
	std::cout << copy.getRawBits() << std::endl;
	std::cout << assigned.getRawBits() << std::endl;

	first.setRawBits(42);
	std::cout << first.getRawBits() << std::endl;
	return (0);
}
