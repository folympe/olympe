
#include "Point.hpp"
#include "Fixed.hpp"
#include <cmath>

Fixed	getTriangleArea(Point const a, Point const b, Point const c)
{
	Fixed	area;
	Fixed	absoluteArea;

	area = a.getX() * (b.getY() - c.getY());
	area = area + b.getX() * (c.getY() - a.getY());
	area = area + c.getX() * (a.getY() - b.getY()) / 2;

	absoluteArea = Fixed(abs(area.toFloat()));
	return (absoluteArea);
}

bool	bsp(Point const a, Point const b, Point const c, Point const p)
{
	Fixed	totalArea;
	Fixed	areaAB;
	Fixed	areaBC;
	Fixed	areaAC;

	totalArea = getTriangleArea(a, b, c);
	areaAB = getTriangleArea(p, a, b);
	areaBC = getTriangleArea(p, b, c);
	areaAC = getTriangleArea(p, a, c);

	if (areaAB == 0 || areaBC == 0 || areaAC == 0)
		return (false);
	if (areaAB + areaBC + areaAC > totalArea)
		return (false);
	return (true);
}
