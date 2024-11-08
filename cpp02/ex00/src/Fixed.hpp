#ifndef FIXED_HPP
#define FIXED_HPP

class Fixed {
public:
	Fixed();
	Fixed(const Fixed& other);
	~Fixed();
	Fixed& operator=(const Fixed& right);

	int getRawBits() const;
	void setRawBits(int raw);

private:
	static const int _fractional_bits = 8;
	int _value;
};

#endif
