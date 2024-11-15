#include "WrongAnimal.hpp"
#include <iostream>
#include <string>

WrongAnimal::WrongAnimal() : _type("WrongAnimal")
{
	std::cout << this->_type << " constructor called." << '\n';
}

WrongAnimal::WrongAnimal(const std::string& type) : _type(type)
{
	std::cout << this->_type << " parameterized constructor called." << '\n';
}

WrongAnimal::WrongAnimal(const WrongAnimal& other) : _type(other._type)
{
	std::cout << this->_type << " copy constructor called." << '\n';
}

WrongAnimal::~WrongAnimal()
{
	std::cout << this->_type << " destructor called." << '\n';
}

void WrongAnimal::makeSound()
{
	std::cout << "Silence..." << '\n';
}

const std::string& WrongAnimal::getType() const
{
	return this->_type;
}
