#include "Cat.hpp"
#include "AAnimal.hpp"
#include "Brain.hpp"
#include <iostream>

Cat::Cat() : AAnimal("Cat"), _brain(new Brain())
{
	std::cout << this->_type << " constructor called." << '\n';
}

Cat::Cat(const Cat& other) : AAnimal(other), _brain(new Brain(*other._brain))
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
	std::cout << this->_type << " copy assignment operator called." << '\n';
	if (this != &other) {
		this->AAnimal::operator=(other);
		*this->_brain = *other._brain;
	}
	return *this;
}

void Cat::makeSound() const
{
	std::cout << "Meow!" << '\n';
}

Brain* Cat::brain()
{
	return this->_brain;
}