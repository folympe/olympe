
/* Check results with:	https://www.geogebra.org/calculator
						https://planetcalc.com/8108/			*/

#include "Fixed.hpp"
#include "Point.hpp"
#include <iostream>

#define RESET "\e[0m"
#define CYAN "\e[36m"
#define YELLOW "\e[33m"
#define GREEN "\e[32m"
#define RED	"\e[31m"

bool bsp( Point const a, Point const b, Point const c, Point const p );

void	printIsPointInsideTriangle(Point const a, Point const b,
			Point const c, Point const p, bool expected)
{
	bool	result;

	result = bsp(a, b, c, p);
	std::cerr << YELLOW
		<< "-- Triangle: A(" << a.getX() << ", " << a.getY() << ") "
		<< "B(" << b.getX() << ", " << b.getY() << ") "
		<< "C(" << c.getX() << ", " << c.getY() << ")"
		<< RESET << std::endl;
	std::cerr << YELLOW
		<< "-- Point: P(" << p.getX() << ", " << p.getY() << ")"
		<< RESET << std::endl;
	std::cout << "Is point P inside triangle ABC? ";
	if (result)
		std::cout << GREEN << "YES!" << RESET;
	else
		std::cout << RED << "NO." << RESET;
	std::cout << " (Expected: ";
	if (expected)
		std::cout << GREEN << "YES" << RESET;
	else
		std::cout << RED << "NO" << RESET;
	std::cout << ")" << std::endl << std::endl;
}

void	testSimpleTriangle(void)
{
	Point const	a(0, 0);
	Point const	b(6, 0);
	Point const	c(0, 6);

	std::cout << std::endl
		<< "--- Simple triangle test"
		<< std::endl << std::endl;
	{
		Point const	p(1.5f, 1.5f);
		printIsPointInsideTriangle(a, b, c, p, true);
	}
	{
		Point const	p(a);
		printIsPointInsideTriangle(a, b, c, p, false);
	}
	{
		Point const	p(10.0f, 1.5f);
		printIsPointInsideTriangle(a, b, c, p, false);
	}
	{
		Point const	p(4.5f, 0.5f);
		printIsPointInsideTriangle(a, b, c, p, true);
	}
}

void	testFloatPointTriangle(void)
{
	Point const	a(-5.44f, 0.29f);
	Point const	b(2.62f, 2.95f);
	Point const	c(1.0f, -1.45f);

	std::cout << std::endl
		<< "--- Floating point triangle test"
		<< std::endl << std::endl;
	{
		Point const	p;
		printIsPointInsideTriangle(a, b, c, p, true);
	}
	{
		Point const	p(c);
		printIsPointInsideTriangle(a, b, c, p, false);
	}
	{
		Point const	p(-5.45f, 0.29f);
		printIsPointInsideTriangle(a, b, c, p, false);
	}
	{
		Point const	p(3.5f, 1.5f);
		printIsPointInsideTriangle(a, b, c, p, false);
	}
}

int	main( void )
{
	testSimpleTriangle();
	testFloatPointTriangle();
	return ( 0 );
}
