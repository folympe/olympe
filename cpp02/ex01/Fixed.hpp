
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

		int		getRawBits(void) const;
		void	setRawBits(int const raw);
		float	toFloat(void) const;
		int		toInt(void) const;
};

std::ostream& operator<<( std::ostream& os, const Fixed& number );

#endif