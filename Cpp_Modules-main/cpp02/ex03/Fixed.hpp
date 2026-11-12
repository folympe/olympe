
#ifndef FIXED_CLASS_H
# define FIXED_CLASS_H

# include <iostream>

class Fixed
{
	public:
		Fixed(void);
		Fixed(const Fixed& src);
		Fixed(const int n);
		Fixed(const float f);
		~Fixed(void);

		Fixed& operator=(const Fixed& src);

		bool operator>(const Fixed& rhs) const;
		bool operator<(const Fixed& rhs) const;
		bool operator>=(const Fixed& rhs) const;
		bool operator<=(const Fixed& rhs) const;
		bool operator==(const Fixed& rhs) const;
		bool operator!=(const Fixed& rhs) const;

		Fixed operator+(const Fixed& rhs) const;
		Fixed operator-(const Fixed& rhs) const;
		Fixed operator*(const Fixed& rhs) const;
		Fixed operator/(const Fixed& rhs) const;

		Fixed& operator++(void);
		Fixed operator++(int);
		Fixed& operator--(void);
		Fixed operator--(int);

		int getRawBits(void) const;
		void setRawBits(const int raw);
		float toFloat(void) const;
		int toInt(void) const;

		static Fixed& min(Fixed& lhs, Fixed& rhs);
		static Fixed& max(Fixed& lhs, Fixed& rhs);
		static const Fixed& min(const Fixed& lhs, const Fixed& rhs);
		static const Fixed& max(const Fixed& lhs, const Fixed& rhs);

	private:
		int _raw;
		static const int _fractionalBits = 8;
};

std::ostream & operator<<( std::ostream & os, const Fixed & number );

#endif