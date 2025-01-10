#include "Fixed.hpp"
#include <climits>
#include <cmath>
#include <iomanip>
#include <iostream>

bool Fixed::_bad = false;

Fixed::Fixed() : _value(0) {}

Fixed::Fixed(const Fixed& other) : _value(other.getRawBits()) {}

Fixed::Fixed(const int num)
{
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
	return this->toFloat() + other.toFloat();
}

Fixed Fixed::operator-(const Fixed& other) const
{
	return this->toFloat() - other.toFloat();
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
	if (this->getRawBits() != INT_MAX) {
		this->setRawBits(this->getRawBits() + 1);
	}
	return *this;
}

Fixed Fixed::operator++(int)
{
	const Fixed prev(*this);
	++*this;
	return prev;
}

Fixed& Fixed::operator--()
{
	if (this->getRawBits() != INT_MIN) {
		this->setRawBits(this->getRawBits() - 1);
	}
	return *this;
}

Fixed Fixed::operator--(int)
{
	const Fixed prev(*this);
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

bool Fixed::bad()
{
	return Fixed::_bad;
}

void Fixed::clear()
{
	Fixed::_bad = false;
}

int Fixed::fractional_bits()
{
	return Fixed::_fractional_bits;
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
	return os << std::left << std::setprecision(Fixed::fractional_bits())
	          << std::setw(Fixed::fractional_bits() + 2) << fixed.toFloat();
}
