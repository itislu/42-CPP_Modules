#include "Weapon.hpp"
#include <string>

Weapon::Weapon(const std::string& type) : _type(type) {}

const std::string& Weapon::getType() const
{
	return this->_type;
}

void Weapon::setType(const std::string& new_type)
{
	this->_type = new_type;
}
