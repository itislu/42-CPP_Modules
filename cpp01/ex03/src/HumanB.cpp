#include "HumanB.hpp"
#include "Weapon.hpp"
#include <cstddef>
#include <iostream>
#include <string>

HumanB::HumanB(const std::string& name) : _name(name), _weapon(NULL) {}

void HumanB::setWeapon(Weapon& weapon)
{
	if (this->_weapon != NULL) {
		std::cout << this->_name << " changes from " << this->_weapon->getType()
		          << " to " << weapon.getType() << '\n';
	}
	else {
		std::cout << this->_name << " picks up " << weapon.getType() << '\n';
	}
	this->_weapon = &weapon;
}

void HumanB::dropWeapon()
{
	if (this->_weapon != NULL) {
		std::cout << this->_name << " drops " << this->_weapon->getType()
		          << '\n';
	}
	else {
		std::cout << this->_name << " has no weapon to drop" << '\n';
	}
	this->_weapon = NULL;
}

void HumanB::attack() const
{
	if (this->_weapon != NULL) {
		std::cout << this->_name << " attacks with their "
		          << this->_weapon->getType() << '\n';
	}
	else {
		std::cout << this->_name << " is unarmed" << '\n';
	}
}
