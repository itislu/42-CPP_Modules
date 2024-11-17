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

	static bool bad();
	static void clear();

	int getRawBits() const;
	void setRawBits(int raw);
	int toInt() const;
	float toFloat() const;

private:
	static const int _fractional_bits = FRACT_BITS;
	static bool _bad;

	int _value;
};

std::ostream& operator<<(std::ostream& os, const Fixed& fixed);

#endif
