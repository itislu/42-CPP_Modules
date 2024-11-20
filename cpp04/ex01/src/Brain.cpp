// NOLINTBEGIN(cppcoreguidelines-pro-bounds-constant-array-index)

#include "Brain.hpp"
#include <iostream>
#include <string>

Brain::Brain() : _index(0)
{
	std::cout << "Brain constructor called." << '\n';
}

Brain::Brain(const Brain& other) : _index(0)
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
		this->_index = other._index;
	}
	return *this;
}

void Brain::add_idea(const std::string& idea)
{
	this->_ideas[this->_index] = idea;
	this->_index = (this->_index + 1) % Brain::brain_size;
}

std::string Brain::get_idea(int index) const
{
	if (index >= Brain::brain_size) {
		return "";
	}
	return this->_ideas[index];
}

// NOLINTEND(cppcoreguidelines-pro-bounds-constant-array-index)
