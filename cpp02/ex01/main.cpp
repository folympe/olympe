
#include "Fixed.hpp"
#include <iostream>

int	main(void)
{
	Fixed		value;
	Fixed const	integer(10);
	Fixed const	decimal(42.42f);
	Fixed const	copy(integer);

	value = Fixed(1234.4321f);

	std::cout << "a is " << value << std::endl;
	std::cout << "b is " << integer << std::endl;
	std::cout << "c is " << decimal << std::endl;
	std::cout << "d is " << copy << std::endl;

	std::cout << "a is " << value.toInt() << " as integer" << std::endl;
	std::cout << "b is " << integer.toInt() << " as integer" << std::endl;
	std::cout << "c is " << decimal.toInt() << " as integer" << std::endl;
	std::cout << "d is " << copy.toInt() << " as integer" << std::endl;
	return (0);
}
