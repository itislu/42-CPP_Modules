#include "Fixed.hpp"
#include <iostream>

Fixed::Fixed() : _value(0)
{
	std::cout << "Default constructor called" << '\n';
}

Fixed::Fixed(const Fixed& other) : _value(other.getRawBits())
{
	std::cout << "Copy constructor called" << '\n';
}

Fixed::Fixed(const int num) : _value(num * (2 << Fixed::_fractional_bits))
{
	std::cout << "Int constructor called" << '\n';
}

Fixed::Fixed(const float num) :
	_value((int)(num * (2 << Fixed::_fractional_bits)))
{
	std::cout << "Float constructor called" << '\n';
}

Fixed::~Fixed()
{
	std::cout << "Destructor called" << '\n';
}

Fixed& Fixed::operator=(const Fixed& right)
{
	std::cout << "Copy assignment operator called" << '\n';
	if (this != &right) {
		this->_value = right.getRawBits();
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
	return this->getRawBits() / (2 << Fixed::_fractional_bits);
}

float Fixed::toFloat() const
{
	return (float)this->getRawBits() / (2 << Fixed::_fractional_bits);
}

std::ostream& operator<<(std::ostream& os, const Fixed& fixed)
{
	return os << fixed.toFloat();
}
