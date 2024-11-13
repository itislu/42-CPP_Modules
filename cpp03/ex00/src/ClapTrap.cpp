#include "ClapTrap.hpp"
#include <iostream>
#include <string>

ClapTrap::ClapTrap() :
	_hp(ClapTrap::_hp_start),
	_ep(ClapTrap::_ep_start),
	_dmg(ClapTrap::_dmg_start)
{
	std::cout << "Unnamed ClapTrap constructed." << '\n';
}

ClapTrap::ClapTrap(const std::string& name) :
	_name(name),
	_hp(ClapTrap::_hp_start),
	_ep(ClapTrap::_ep_start),
	_dmg(ClapTrap::_dmg_start)
{
	std::cout << "ClapTrap " << this->_name << " constructed." << '\n';
}

ClapTrap::ClapTrap(const ClapTrap& other) :
	_name(other._name), _hp(other._hp), _ep(other._ep), _dmg(other._dmg)
{
	std::cout << "ClapTrap " << this->_name << " copy constructed." << '\n';
}

ClapTrap::~ClapTrap()
{
	std::cout << "ClapTrap " << this->_name << " destructed." << '\n';
}

ClapTrap& ClapTrap::operator=(const ClapTrap& other)
{
	std::cout << "ClapTrap " << this->_name << " copy assigned";
	if (this != &other) {
		this->_name = other._name;
		this->_hp = other._hp;
		this->_ep = other._ep;
		this->_dmg = other._dmg;
	}
	else {
		std::cout << " to itself";
	}
	std::cout << "." << '\n';
	return *this;
}

void ClapTrap::attack(const std::string& target) const
{
	std::cout << "ClapTrap " << this->_name;
	if (this->_hp == 0) {
		std::cout << " cannot attack because it's already dead." << '\n';
	}
	else if (this->_ep == 0) {
		std::cout << " cannot attack because it has no energy points left."
				  << '\n';
	}
	else {
		std::cout << " attacks " << target << ", causing " << this->_dmg
				  << " points of damage!" << '\n';
	}
}

void ClapTrap::takeDamage(unsigned int amount)
{
	std::cout << "ClapTrap " << this->_name;
	if (this->_hp == 0) {
		std::cout << " cannot take more damage because it's already dead."
				  << '\n';
	}
	else if (this->_hp <= amount) {
		this->_hp = 0;
		std::cout << " takes " << amount << " points of damage and dies!"
				  << '\n';
	}
	else {
		this->_hp -= amount;
		std::cout << " takes " << amount << " points of damage!" << '\n';
	}
}

void ClapTrap::beRepaired(unsigned int amount)
{
	std::cout << "ClapTrap " << this->_name;
	if (this->_hp == 0) {
		std::cout << " cannot repair itself because it's already dead." << '\n';
	}
	else if (this->_ep == 0) {
		std::cout
			<< " cannot repair itself because it has no energy points left."
			<< '\n';
	}
	else {
		this->_ep -= 1;
		this->_hp += amount;
		std::cout << " repairs itself for " << amount << " points of damage!"
				  << '\n';
	}
}
