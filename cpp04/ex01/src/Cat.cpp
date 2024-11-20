#include "Cat.hpp"
#include "Animal.hpp"
#include "Brain.hpp"
#include <iostream>

Cat::Cat() : Animal("Cat"), _brain(new Brain())
{
	std::cout << this->_type << " constructor called." << '\n';
}

Cat::Cat(const Cat& other) : Animal(other), _brain(new Brain(*other._brain))
{
	std::cout << this->_type << " copy constructor called." << '\n';
}

Cat::~Cat()
{
	std::cout << this->_type << " destructor called." << '\n';
	delete this->_brain;
}

Cat& Cat::operator=(const Cat& other)
{
	if (this != &other) {
		this->Animal::operator=(other);
		this->_brain = other._brain;
	}
	return *this;
}

void Cat::makeSound() const
{
	std::cout << "Meow!" << '\n';
}
