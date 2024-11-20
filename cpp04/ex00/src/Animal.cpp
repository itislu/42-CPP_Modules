#include "Animal.hpp"
#include <iostream>
#include <string>

Animal::Animal() : _type("Animal")
{
	std::cout << "Animal constructor called." << '\n';
}

Animal::Animal(const std::string& type) : _type(type)
{
	std::cout << "Animal parameterized constructor called." << '\n';
}

Animal::Animal(const Animal& other) : _type(other._type)
{
	std::cout << "Animal copy constructor called." << '\n';
}

Animal::~Animal()
{
	std::cout << "Animal destructor called." << '\n';
}

Animal& Animal::operator=(const Animal& other)
{
	if (this != &other) {
		this->_type = other._type;
	}
	return *this;
}

void Animal::makeSound() const
{
	std::cout << "Silence..." << '\n';
}

const std::string& Animal::getType() const
{
	return this->_type;
}
