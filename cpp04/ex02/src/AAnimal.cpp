#include "AAnimal.hpp"
#include <iostream>
#include <string>

AAnimal::AAnimal() : _type("AAnimal")
{
	std::cout << "AAnimal constructor called." << '\n';
}

AAnimal::AAnimal(const std::string& type) : _type(type)
{
	std::cout << "AAnimal parameterized constructor called." << '\n';
}

AAnimal::AAnimal(const AAnimal& other) : _type(other._type)
{
	std::cout << "AAnimal copy constructor called." << '\n';
}

AAnimal::~AAnimal()
{
	std::cout << "AAnimal destructor called." << '\n';
}

AAnimal& AAnimal::operator=(const AAnimal& other)
{
	if (this != &other) {
		this->_type = other._type;
	}
	return *this;
}

const std::string& AAnimal::getType() const
{
	return this->_type;
}
