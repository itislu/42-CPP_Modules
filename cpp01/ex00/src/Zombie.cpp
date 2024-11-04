#include "Zombie.hpp"
#include <iostream>
#include <string>

Zombie::Zombie(const std::string& name) : _name(name)
{
	this->announce();
}

Zombie::~Zombie()
{
	std::cout << this->_name << " destructed" << '\n';
}

void Zombie::announce()
{
	std::cout << this->_name << ": BraiiiiiiinnnzzzZ..." << '\n';
}
