#include "Dog.hpp"
#include "Animal.hpp"
#include <iostream>

Dog::Dog() : Animal("Dog")
{
	std::cout << this->_type << " constructor called." << '\n';
}

Dog::Dog(const Dog& other) : Animal(other)
{
	std::cout << this->_type << " copy constructor called." << '\n';

}

Dog::~Dog()
{
	std::cout << this->_type << " destructor called." << '\n';
}

Dog& Dog::operator=(const Dog& other)
{
	if (this != &other) {
		this->_type = other._type;
	}
	return *this;
}

void Dog::makeSound() const
{
	std::cout << "Woof!" << '\n';
}
