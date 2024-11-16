#ifndef FIXED_HPP
#define FIXED_HPP

#ifndef FRACT_BITS
#define FRACT_BITS 8
#endif

class Fixed {
public:
	Fixed();
	Fixed(const Fixed& other);
	~Fixed();

	Fixed& operator=(const Fixed& other);

	int getRawBits() const;
	void setRawBits(int raw);

private:
	static const int _fractional_bits = FRACT_BITS;
	int _value;
};

#endif
