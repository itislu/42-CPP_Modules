#include "WrongAnimal.hpp"
#include <iostream>
#include <string>

WrongAnimal::WrongAnimal() : _type("WrongAnimal")
{
	std::cout << "WrongAnimal constructor called." << '\n';
}

WrongAnimal::WrongAnimal(const std::string& type) : _type(type)
{
	std::cout << "WrongAnimal parameterized constructor called." << '\n';
}

WrongAnimal::WrongAnimal(const WrongAnimal& other) : _type(other._type)
{
	std::cout << "WrongAnimal copy constructor called." << '\n';
}

WrongAnimal::~WrongAnimal()
{
	std::cout << "WrongAnimal destructor called." << '\n';
}

void WrongAnimal::makeSound() const
{
	std::cout << "Silence..." << '\n';
}

const std::string& WrongAnimal::getType() const
{
	return this->_type;
}
