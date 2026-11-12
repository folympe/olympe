
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
		std::cerr << CYAN "Default constructor called." RESET << std::endl;
}

Fixed::Fixed(Fixed const &src)
{
	if (PRINT_MESSAGE == 1)
		std::cerr << CYAN "Copy constructor called." RESET << std::endl;
	*this = src;
}

Fixed::Fixed(int const n) : _raw(n << _fractionalBits)
{
	if (PRINT_MESSAGE == 1)
		std::cerr << CYAN "Int constructor called." RESET << std::endl;
}

Fixed::Fixed(float const f) : _raw(roundf(f * (1 << _fractionalBits)))
{
	if (PRINT_MESSAGE == 1)
		std::cerr << CYAN "Float constructor called." RESET << std::endl;
}

Fixed::~Fixed(void)
{
	if (PRINT_MESSAGE == 1)
		std::cerr << CYAN "Destructor called." RESET << std::endl;
}

Fixed	&Fixed::operator=(Fixed const &src)
{
	if (this == &src)
		return (*this);

	if (PRINT_MESSAGE == 1)
		std::cerr << YELLOW "Copy assignment operator called." RESET << std::endl;

	_raw = src.getRawBits();
	return (*this);
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
	Fixed	result(toFloat() + rhs.toFloat());
	return (result);
}

Fixed	Fixed::operator-(Fixed const &rhs) const
{
	Fixed	result(toFloat() - rhs.toFloat());
	return (result);
}

Fixed	Fixed::operator*(Fixed const &rhs) const
{
	Fixed	result(toFloat() * rhs.toFloat());
	return (result);
}

Fixed	Fixed::operator/(Fixed const &rhs) const
{
	Fixed	result(toFloat() / rhs.toFloat());
	return (result);
}

Fixed	&Fixed::operator++(void)
{
	_raw++;
	return (*this);
}

Fixed	Fixed::operator++(int)
{
	Fixed	oldValue(*this);

	operator++();
	return (oldValue);
}

Fixed	&Fixed::operator--(void)
{
	_raw--;
	return (*this);
}

Fixed	Fixed::operator--(int)
{
	Fixed	oldValue(*this);

	operator--();
	return (oldValue);
}

int	Fixed::getRawBits(void) const
{
	if (PRINT_MESSAGE == 1)
		std::cerr << GREEN "getRawBits member function called." RESET << std::endl;
	return (_raw);
}

void	Fixed::setRawBits(int const raw)
{
	if (PRINT_MESSAGE == 1)
		std::cerr << GREEN "setRawBits member funtion called." RESET << std::endl;
	_raw = raw;
}

int	Fixed::toInt(void) const
{
	return (_raw >> _fractionalBits);
}

float	Fixed::toFloat(void) const
{
	float	value = static_cast<float>(_raw);

	return (value / (1 << _fractionalBits));
}

Fixed	&Fixed::min(Fixed &lhs, Fixed &rhs)
{
	if (lhs > rhs)
		return (rhs);
	return (lhs);
}


const Fixed& Fixed::min(const Fixed& lhs, const Fixed& rhs)
{
    if (lhs <= rhs)
        return (lhs);
    return (rhs);
}

Fixed& Fixed::max(Fixed& lhs, Fixed& rhs)
{
    if (lhs >= rhs)
        return (lhs);
    return (rhs);
}

const Fixed& Fixed::max(const Fixed& lhs, const Fixed& rhs)
{
    if (lhs >= rhs)
        return (lhs);
    return (rhs);
}

std::ostream& operator<<(std::ostream& os, const Fixed& number)
{
    os << number.toFloat();
    return (os);
}