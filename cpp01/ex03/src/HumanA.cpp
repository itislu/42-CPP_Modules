#include "HumanA.hpp"
#include "Weapon.hpp"
#include <iostream>
#include <string>

HumanA::HumanA(const std::string& name, Weapon& weapon) :
	_name(name), _weapon(&weapon)
{
}

void HumanA::setWeapon(Weapon& weapon)
{
	std::cout << this->_name << " changes from " << this->_weapon->getType()
			  << " to " << weapon.getType() << "\n";
	this->_weapon = &weapon;
}

void HumanA::attack() const
{
	std::cout << this->_name << " attacks with their "
			  << this->_weapon->getType() << "\n";
}
