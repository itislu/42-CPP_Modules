#include "Weapon.hpp"
#include <iostream>
#include <string>

Weapon::Weapon(const std::string& type) : _type(type) {}

const std::string& Weapon::getType() const
{
	return this->_type;
}

void Weapon::setType(const std::string& new_type)
{
	std::cout << "  " << this->_type << " dropped, " << new_type << " picked up"
			  << '\n';
	this->_type = new_type;
}
