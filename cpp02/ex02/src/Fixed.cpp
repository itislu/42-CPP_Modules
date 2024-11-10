#include "Fixed.hpp"
#include <cmath>
#include <iostream>

Fixed::Fixed() : _value(0) {}

Fixed::Fixed(const Fixed& other) : _value(other.getRawBits()) {}

Fixed::Fixed(const int num) : _value(num << Fixed::_fractional_bits) {}

Fixed::Fixed(const float num) :
	_value((int)roundf(num * (1 << Fixed::_fractional_bits)))
{
}

Fixed::~Fixed() {}

Fixed& Fixed::operator=(const Fixed& other)
{
	if (this != &other) {
		this->_value = other.getRawBits();
	}
	return *this;
}

bool Fixed::operator>(const Fixed& other) const
{
	return this->getRawBits() > other.getRawBits();
}

bool Fixed::operator<(const Fixed& other) const
{
	return this->getRawBits() < other.getRawBits();
}

bool Fixed::operator>=(const Fixed& other) const
{
	return this->getRawBits() >= other.getRawBits();
}

bool Fixed::operator<=(const Fixed& other) const
{
	return this->getRawBits() <= other.getRawBits();
}

bool Fixed::operator==(const Fixed& other) const
{
	return this->getRawBits() == other.getRawBits();
}

bool Fixed::operator!=(const Fixed& other) const
{
	return this->getRawBits() != other.getRawBits();
}

Fixed Fixed::operator+(const Fixed& other) const
{
	return this->getRawBits() + other.getRawBits();
}

Fixed Fixed::operator-(const Fixed& other) const
{
	return this->getRawBits() - other.getRawBits();
}

Fixed Fixed::operator*(const Fixed& other) const
{
	return this->toFloat() * other.toFloat();
}

Fixed Fixed::operator/(const Fixed& other) const
{
	return this->toFloat() / other.toFloat();
}

Fixed& Fixed::operator++()
{
	this->setRawBits(this->getRawBits() + 1);
	return *this;
}

Fixed Fixed::operator++(int)
{
	Fixed prev(*this);
	++*this;
	return prev;
}

Fixed& Fixed::operator--()
{
	this->setRawBits(this->getRawBits() - 1);
	return *this;
}

Fixed Fixed::operator--(int)
{
	Fixed prev(*this);
	--*this;
	return prev;
}

Fixed& Fixed::min(Fixed& a, Fixed& b)
{
	return a <= b ? a : b;
}

const Fixed& Fixed::min(const Fixed& a, const Fixed& b)
{
	return a <= b ? a : b;
}

Fixed& Fixed::max(Fixed& a, Fixed& b)
{
	return a >= b ? a : b;
}

const Fixed& Fixed::max(const Fixed& a, const Fixed& b)
{
	return a >= b ? a : b;
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
