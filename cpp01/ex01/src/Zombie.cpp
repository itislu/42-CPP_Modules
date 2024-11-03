#include "Zombie.hpp"
#include <iostream>

Zombie::Zombie(std::string name) : _name(name)
{
	this->announce();
}

Zombie::Zombie(void) {}

Zombie::~Zombie(void)
{
	std::cout << this->_name << " destructed" << std::endl;
}

void Zombie::announce(void)
{
	std::cout << this->_name << ": BraiiiiiiinnnzzzZ..." << std::endl;
}

void Zombie::set_name(std::string name)
{
	this->_name = name;
}
