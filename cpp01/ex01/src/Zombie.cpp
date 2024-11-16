#include "Zombie.hpp"
#include <iostream>
#include <string>

Zombie::Zombie(const std::string& name) : _name(name)
{
	this->announce();
}

Zombie::Zombie() {}

Zombie::~Zombie()
{
	std::cout << this->_name << " destructed" << '\n';
}

void Zombie::announce()
{
	std::cout << this->_name << ": BraiiiiiiinnnzzzZ..." << '\n';
}

void Zombie::set_name(const std::string& name)
{
	this->_name = name;
}
