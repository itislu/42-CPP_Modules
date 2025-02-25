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
	std::cout << "getRawBits member function called" << '\n';
	return this->_value;
}

void Fixed::setRawBits(const int raw)
{
	std::cout << "setRawBits member function called" << '\n';
	this->_value = raw;
}
