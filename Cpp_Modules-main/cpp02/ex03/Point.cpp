
#include "Point.hpp"
#include "Fixed.hpp"

#define RESET "\e[0m"
#define CYAN "\e[36m"
#define YELLOW "\e[33m"
#define GREEN "\e[32m"

# define PRINT_MESSAGE 0

Point::Point(void) : _x(0), _y(0)
{
	if (PRINT_MESSAGE == 1)
		std::cerr << CYAN
			<< "Point default constructor called."
			<< RESET << std::endl;
}

Point::Point(const Fixed x, const Fixed y) : _x(x), _y(y)
{
	if (PRINT_MESSAGE == 1)
		std::cerr << CYAN
			<< "Point fixed constructor called."
			<< RESET << std::endl;
}

Point::Point(const Point& src) : _x(src.getX()), _y(src.getY())
{
	if (PRINT_MESSAGE == 1)
		std::cerr << CYAN
			<< "Point copy constructor called."
			<< RESET << std::endl;
}

Point::~Point(void)
{
	if (PRINT_MESSAGE == 1)
		std::cerr << CYAN
			<< "Point destructor called."
			<< RESET << std::endl;
}

Point& Point::operator=(const Point& rhs)
{
	if (PRINT_MESSAGE == 1)
		std::cerr << YELLOW
			<< "Point assignment operator called."
			<< RESET << std::endl;
	std::cerr << "Warning: cannot assign to Point const attributes. "
		"Use a Point copy constructor instead."
		<< std::endl;
	(void)rhs;
	return (*this);
}

Fixed const &	Point::getX( void ) const
{
	return ( this->_x );
}

Fixed const &	Point::getY( void ) const
{
	return ( this->_y );
}
