#include "Dog.hpp"
#include "Animal.hpp"
#include "Brain.hpp"
#include <iostream>

Dog::Dog() : Animal("Dog"), _brain(new Brain())
{
	std::cout << this->_type << " constructor called." << '\n';
}

Dog::Dog(const Dog& other) : Animal(other), _brain(new Brain(*other._brain))
{
	std::cout << this->_type << " copy constructor called." << '\n';
}

Dog::~Dog()
{
	std::cout << this->_type << " destructor called." << '\n';
	delete this->_brain;
}

Dog& Dog::operator=(const Dog& other)
{
	std::cout << this->_type << " copy assignment operator called." << '\n';
	if (this != &other) {
		this->Animal::operator=(other);
		*this->_brain = *other._brain;
	}
	return *this;
}

void Dog::makeSound() const
{
	std::cout << "Woof!" << '\n';
}

Brain* Dog::brain()
{
	return this->_brain;
}
