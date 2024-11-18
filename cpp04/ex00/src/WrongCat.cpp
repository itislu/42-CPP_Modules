#include "WrongCat.hpp"
#include "WrongAnimal.hpp"
#include <iostream>

WrongCat::WrongCat() : WrongAnimal("WrongCat")
{
	std::cout << this->_type << " constructor called." << '\n';
}

WrongCat::WrongCat(const WrongCat& other) : WrongAnimal(other)
{
	std::cout << this->_type << " copy constructor called." << '\n';
}

WrongCat::~WrongCat()
{
	std::cout << this->_type << " destructor called." << '\n';
}

WrongCat& WrongCat::operator=(const WrongCat& other)
{
	if (this != &other) {
		this->_type = other._type;
	}
	return *this;
}

void WrongCat::makeSound() const
{
	std::cout << "Meow!" << '\n';
}
