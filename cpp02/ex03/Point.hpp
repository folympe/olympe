
#ifndef POINT_CLASS_H
# define POINT_CLASS_H

# include "Fixed.hpp"

class Point
{
	public:
		Point(void);
		Point(const Fixed x, const Fixed y);
		Point(const Point& src);
		~Point(void);

		Point& operator=(const Point& src);

		const Fixed& getX(void) const;
		const Fixed& getY(void) const;

	private:
		const Fixed _x;
		const Fixed _y;
};

#endif