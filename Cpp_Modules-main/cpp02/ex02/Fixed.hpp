
#ifndef FIXED_CLASS_H
# define FIXED_CLASS_H

# include <iostream>

class Fixed
{
	private:
		int					_raw;
		static const int	_fractionalBits = 8;

	public:
		Fixed(void);
		Fixed(Fixed const &src);
		Fixed(int const n);
		Fixed(float const f);
		~Fixed(void);

		Fixed	&operator=(Fixed const &src);

		bool	operator>(Fixed const &rhs) const;
		bool	operator<(Fixed const &rhs) const;
		bool	operator>=(Fixed const &rhs) const;
		bool	operator<=(Fixed const &rhs) const;
		bool	operator==(Fixed const &rhs) const;
		bool	operator!=(Fixed const &rhs) const;

		Fixed	operator+(Fixed const &rhs) const;
		Fixed	operator-(Fixed const &rhs) const;
		Fixed	operator*(Fixed const &rhs) const;
		Fixed	operator/(Fixed const &rhs) const;

		Fixed	&operator++(void);
		Fixed	operator++(int);
		Fixed	&operator--(void);
		Fixed	operator--(int);

		int		getRawBits(void) const;
		void	setRawBits(int const raw);
		float	toFloat(void) const;
		int		toInt(void) const;

		static Fixed			&min(Fixed &lhs, Fixed &rhs);
		static Fixed			&max(Fixed &lhs, Fixed &rhs);
		static Fixed const		&min(Fixed const &lhs, Fixed const &rhs);
		static Fixed const		&max(Fixed const &lhs, Fixed const &rhs);
};

std::ostream & operator<<( std::ostream & os, const Fixed & number );

#endif