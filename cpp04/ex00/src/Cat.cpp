#include "Cat.hpp"
#include "Animal.hpp"
#include <iostream>

Cat::Cat() : Animal("Cat")
{
	std::cout << this->_type << " constructor called." << '\n';
}

Cat::Cat(const Cat& other) : Animal(other)
{
	std::cout << this->_type << " copy constructor called." << '\n';

}

Cat::~Cat()
{
	std::cout << this->_type << " destructor called." << '\n';
}

Cat& Cat::operator=(const Cat& other)
{
	if (this != &other) {
		this->_type = other._type;
	}
	return *this;
}

void Cat::makeSound() const
{
	std::cout << "Meow!" << '\n';
}
