#ifndef FIXED_HPP
#define FIXED_HPP

#include <ostream>

class Fixed {
public:
	Fixed();
	Fixed(const Fixed& other);
	Fixed(int num);
	Fixed(float num);
	~Fixed();
	Fixed& operator=(const Fixed& right);
	Fixed& operator<<(const Fixed& right);

	int getRawBits() const;
	void setRawBits(int raw);
	int toInt() const;
	float toFloat() const;

private:
	static const int _fractional_bits = 8;
	int _value;
};

std::ostream& operator<<(std::ostream& os, const Fixed& fixed);

#endif
