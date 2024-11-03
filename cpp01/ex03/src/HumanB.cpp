#include "HumanB.hpp"
#include "Weapon.hpp"
#include <cstddef>
#include <iostream>
#include <string>

HumanB::HumanB(const std::string& name) : _name(name), _weapon(NULL) {}

void HumanB::setWeapon(Weapon& weapon)
{
	this->_weapon = &weapon;
}

void HumanB::attack() const
{
	if (this->_weapon != NULL) {
		std::cout << this->_name << " attacks with their "
				  << this->_weapon->getType() << "\n";
	}
	else {
		std::cout << this->_name << " is unarmed" << "\n";
	}
}
