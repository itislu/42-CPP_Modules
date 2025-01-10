#include "Fixed.hpp"
#include <climits>
#include <cmath>
#include <iostream>

bool Fixed::_bad = false;

Fixed::Fixed() : _value(0)
{
	std::cout << "Default constructor called" << '\n';
}

Fixed::Fixed(const Fixed& other) : _value(other.getRawBits())
{
	std::cout << "Copy constructor called" << '\n';
}

Fixed::Fixed(const int num)
{
	std::cout << "Int constructor called" << '\n';
	const unsigned int save_bits = UINT_MAX >> Fixed::_fractional_bits;

	if (num > 0 && ((num & ~save_bits) != 0)) {
		Fixed::_bad = true;
		this->_value = INT_MAX;
	}
	else if (num < 0 && ((~num & ~save_bits) != 0)) {
		Fixed::_bad = true;
		this->_value = INT_MIN;
	}
	else {
		this->_value = num * (1 << Fixed::_fractional_bits);
	}
}

Fixed::Fixed(const float num)
{
	std::cout << "Float constructor called" << '\n';
	const float scaled = roundf(num * (1 << Fixed::_fractional_bits));

	if (isnan(scaled) != 0 || scaled < (float)INT_MIN) {
		Fixed::_bad = true;
		this->_value = INT_MIN;
	}
	else if (scaled >= (float)INT_MAX) {
		Fixed::_bad = true;
		this->_value = INT_MAX;
	}
	else {
		this->_value = (int)scaled;
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

bool Fixed::bad()
{
	return Fixed::_bad;
}

void Fixed::clear()
{
	Fixed::_bad = false;
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
	return this->getRawBits() / (1 << Fixed::_fractional_bits);
}

float Fixed::toFloat() const
{
	return (float)this->getRawBits() / (1 << Fixed::_fractional_bits);
}

std::ostream& operator<<(std::ostream& os, const Fixed& fixed)
{
	return os << fixed.toFloat();
}
