#include "Brain.hpp"
#include <iostream>

Brain::Brain()
{
	std::cout << "Brain constructor called." << '\n';
}

Brain::Brain(const Brain& other)
{
	std::cout << "Brain copy constructor called." << '\n';
	for (int i = 0; i < Brain::brain_size; ++i) {
		this->_ideas[i] = other._ideas[i];
	}
}

Brain::~Brain()
{
	std::cout << "Brain destructor called." << '\n';
}

Brain& Brain::operator=(const Brain& other)
{
	if (this != &other) {
		for (int i = 0; i < Brain::brain_size; ++i) {
			this->_ideas[i] = other._ideas[i];
		}
	}
	return *this;
}
