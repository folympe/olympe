
#include <iostream>
#include <cmath>
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

Fixed::Fixed( int const n ) : _raw( n << _fractionalBits )
{
	std::cerr << CYAN "Int constructor called." RESET << std::endl;
}

Fixed::Fixed( float const f ) : _raw( roundf(f * (1 << _fractionalBits)) )
{
	std::cerr << CYAN "Float constructor called." RESET << std::endl;
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

void	Fixed::setRawBits( int const raw )
{
	std::cerr << GREEN "setRawBits member funtion called." RESET << std::endl;
	this->_raw = raw;
}

int	Fixed::toInt(void) const
{
	return (_raw >> _fractionalBits);
}

float	Fixed::toFloat( void ) const
{
	return ( (float)this->_raw / (1 << _fractionalBits) );
}

std::ostream& operator<<( std::ostream& os, const Fixed& number )
{
	os << number.toFloat();
	return ( os );
}