#include "Animal.hpp"
#include <iostream>
#include <string>

Animal::Animal() : _type("Animal")
{
	std::cout << this->_type << " constructor called." << '\n';
}

Animal::Animal(const std::string& type) : _type(type)
{
	std::cout << this->_type << " parameterized constructor called." << '\n';
}

Animal::Animal(const Animal& other) : _type(other._type)
{
	std::cout << this->_type << " copy constructor called." << '\n';
}

Animal::~Animal()
{
	std::cout << this->_type << " destructor called." << '\n';
}

void Animal::makeSound() const
{
	std::cout << "Silence..." << '\n';
}

const std::string& Animal::getType() const
{
	return this->_type;
}
