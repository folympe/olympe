
#include <iostream>
#include <cmath>
#include "Fixed.hpp"

#define RESET "\e[0m"
#define CYAN "\e[36m"
#define YELLOW "\e[33m"
#define GREEN "\e[32m"

#define PRINT_MESSAGE 0

Fixed::Fixed(void) : _raw(0)
{
	if (PRINT_MESSAGE == 1)
		std::cerr << CYAN "Default constructor called." RESET
			<< std::endl;
}

Fixed::Fixed(Fixed const &src)
{
	if (PRINT_MESSAGE == 1)
		std::cerr << CYAN "Copy constructor called." RESET
			<< std::endl;
	*this = src;
}

Fixed::Fixed(int const n) : _raw(n << _fractionalBits)
{
	if (PRINT_MESSAGE == 1)
		std::cerr << CYAN "Int constructor called." RESET
			<< std::endl;
}

Fixed::Fixed(float const f)
	: _raw(roundf(f * (1 << _fractionalBits)))
{
	if (PRINT_MESSAGE == 1)
		std::cerr << CYAN "Float constructor called." RESET
			<< std::endl;
}

Fixed::~Fixed( void )
{
	if ( PRINT_MESSAGE == 1 )
		std::cerr << CYAN "Destructor called." RESET << std::endl;
	return ;
}

Fixed &	Fixed::operator=( Fixed const & src )
{
	if ( PRINT_MESSAGE == 1 )
		std::cerr << YELLOW "Copy assignment operator called." RESET << std::endl;
	if ( this != &src )
		this->_raw = src.getRawBits();
	return ( *this );
}

bool	Fixed::operator>(Fixed const &rhs) const
{
	return (_raw > rhs.getRawBits());
}

bool	Fixed::operator<(Fixed const &rhs) const
{
	return (_raw < rhs.getRawBits());
}

bool	Fixed::operator>=(Fixed const &rhs) const
{
	return (_raw >= rhs.getRawBits());
}

bool	Fixed::operator<=(Fixed const &rhs) const
{
	return (_raw <= rhs.getRawBits());
}

bool	Fixed::operator==(Fixed const &rhs) const
{
	return (_raw == rhs.getRawBits());
}

bool	Fixed::operator!=(Fixed const &rhs) const
{
	return (_raw != rhs.getRawBits());
}

Fixed	Fixed::operator+(Fixed const &rhs) const
{
	float	result = toFloat() + rhs.toFloat();

	return (Fixed(result));
}

Fixed	Fixed::operator-(Fixed const &rhs) const
{
	float	result = toFloat() - rhs.toFloat();

	return (Fixed(result));
}

Fixed	Fixed::operator*(Fixed const &rhs) const
{
	float	result = toFloat() * rhs.toFloat();

	return (Fixed(result));
}

Fixed	Fixed::operator/(Fixed const &rhs) const
{
	float	result = toFloat() / rhs.toFloat();

	return (Fixed(result));
}

Fixed	&Fixed::operator++(void)
{
	_raw++;
	return (*this);
}

Fixed	Fixed::operator++(int)
{
	Fixed	previous(*this);

	operator++();
	return (previous);
}

Fixed	&Fixed::operator--(void)
{
	_raw--;
	return (*this);
}

Fixed	Fixed::operator--(int)
{
	Fixed	previous(*this);

	operator--();
	return (previous);
}

int	Fixed::getRawBits(void) const
{
	if (PRINT_MESSAGE == 1)
		std::cerr << GREEN "getRawBits member function called."
			RESET << std::endl;
	return (_raw);
}

void	Fixed::setRawBits(int const raw)
{
	if (PRINT_MESSAGE == 1)
		std::cerr << GREEN "setRawBits member funtion called."
			RESET << std::endl;
	_raw = raw;
}

int	Fixed::toInt(void) const
{
	return (_raw >> _fractionalBits);
}

float	Fixed::toFloat(void) const
{
	return (static_cast<float>(_raw) / (1 << _fractionalBits));
}

Fixed	&Fixed::min(Fixed &lhs, Fixed &rhs)
{
	if (lhs <= rhs)
		return (lhs);
	return (rhs);
}

Fixed const	&Fixed::min(Fixed const &lhs, Fixed const &rhs)
{
	if (lhs <= rhs)
		return (lhs);
	return (rhs);
}

Fixed	&Fixed::max(Fixed &lhs, Fixed &rhs)
{
	if (lhs >= rhs)
		return (lhs);
	return (rhs);
}

Fixed const	&Fixed::max(Fixed const &lhs, Fixed const &rhs)
{
	if (lhs >= rhs)
		return (lhs);
	return (rhs);
}

std::ostream	&operator<<(std::ostream &os, Fixed const &number)
{
	os << number.toFloat();
	return (os);
}