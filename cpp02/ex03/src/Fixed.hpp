#ifndef FIXED_HPP
#define FIXED_HPP

#ifndef FRACT_BITS
#define FRACT_BITS 8
#endif

#include <ostream>

class Fixed {
public:
	Fixed();
	Fixed(const Fixed& other);
	Fixed(int num);
	Fixed(float num);
	~Fixed();

	Fixed& operator=(const Fixed& other);
	bool operator>(const Fixed& other) const;
	bool operator<(const Fixed& other) const;
	bool operator>=(const Fixed& other) const;
	bool operator<=(const Fixed& other) const;
	bool operator==(const Fixed& other) const;
	bool operator!=(const Fixed& other) const;
	Fixed operator+(const Fixed& other) const;
	Fixed operator-(const Fixed& other) const;
	Fixed operator*(const Fixed& other) const;
	Fixed operator/(const Fixed& other) const;
	Fixed& operator++();
	Fixed operator++(int);
	Fixed& operator--();
	Fixed operator--(int);

	static Fixed& min(Fixed& a, Fixed& b);
	static const Fixed& min(const Fixed& a, const Fixed& b);
	static Fixed& max(Fixed& a, Fixed& b);
	static const Fixed& max(const Fixed& a, const Fixed& b);
	static int fractional_bits();

	int getRawBits() const;
	void setRawBits(int raw);
	int toInt() const;
	float toFloat() const;

private:
	static const int _fractional_bits = FRACT_BITS;
	int _value;
};

std::ostream& operator<<(std::ostream& os, const Fixed& fixed);

#endif
