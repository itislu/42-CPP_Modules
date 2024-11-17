#include "Fixed.hpp"
#include <climits>
#include <cmath>
#include <iostream>

Fixed::Fixed() : _value(0)
{
	std::cout << "Default constructor called" << '\n';
}

Fixed::Fixed(const Fixed& other) : _value(other.getRawBits())
{
	std::cout << "Copy constructor called" << '\n';
}

Fixed::Fixed(const int num) : _value(num << Fixed::_fractional_bits)
{
	std::cout << "Int constructor called" << '\n';
}

Fixed::Fixed(const float num)
{
	std::cout << "Float constructor called" << '\n';
	float scaled = roundf(num * (1 << Fixed::_fractional_bits));

	if (isnan(scaled) != 0 || scaled < (float)INT_MIN) {
		_value = INT_MIN;
	}
	else if (scaled >= (float)INT_MAX) {
		_value = INT_MAX;
	}
	else {
		_value = (int)scaled;
	}
}

Fixed::~Fixed()
{
	std::cout << "Destructor called" << '\n';
}

Fixed& Fixed::operator=(const Fixed& other)
{
	std::cout << "Copy assignment operator called" << '\n';
	if (this != &other) {
		this->_value = other.getRawBits();
	}
	return *this;
}

int Fixed::getRawBits() const
{
	return this->_value;
}

void Fixed::setRawBits(const int raw)
{
	this->_value = raw;
}

int Fixed::toInt() const
{
	return this->getRawBits() >> Fixed::_fractional_bits;
}

float Fixed::toFloat() const
{
	return (float)this->getRawBits() / (1 << Fixed::_fractional_bits);
}

std::ostream& operator<<(std::ostream& os, const Fixed& fixed)
{
	return os << fixed.toFloat();
}
