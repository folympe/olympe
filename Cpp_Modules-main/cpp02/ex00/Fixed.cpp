
#include <iostream>
#include "Fixed.hpp"

#define RESET "\e[0m"
#define CYAN "\e[36m"
#define YELLOW "\e[33m"
#define GREEN "\e[32m"

Fixed::Fixed( void ) : _raw( 0 )
{
	std::cerr << CYAN "Default constructor called." RESET << std::endl;
}

Fixed::Fixed( Fixed const & src )
{
	std::cerr << CYAN "Copy constructor called." RESET << std::endl;
	*this = src;
}

Fixed::~Fixed( void )
{
	std::cerr << CYAN "Destructor called." RESET << std::endl;
}

Fixed	&Fixed::operator=(Fixed const &src)
{
	std::cerr << YELLOW "Copy assignment operator called."
		RESET << std::endl;
	if (this != &src)
		_raw = src.getRawBits();
	return (*this);
}

int	Fixed::getRawBits(void) const
{
	std::cerr << GREEN "getRawBits member function called."
		RESET << std::endl;
	return (_raw);
}

void	Fixed::setRawBits(int const raw)
{
	std::cerr << GREEN "setRawBits member funtion called."
		RESET << std::endl;
	_raw = raw;
}
