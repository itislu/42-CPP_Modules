#include "ScavTrap.hpp"
#include "ClapTrap.hpp"
#include <iostream>
#include <string>

const std::string ScavTrap::_type = "ScavTrap";

ScavTrap::ScavTrap() :
	ClapTrap(ScavTrap::_hp_start, ScavTrap::_ep_start, ScavTrap::_dmg_start)
{
	std::cout << "Unnamed " << ScavTrap::_type << " default constructed."
			  << '\n';
}

ScavTrap::ScavTrap(const std::string& name) :
	ClapTrap(name,
			 ScavTrap::_hp_start,
			 ScavTrap::_ep_start,
			 ScavTrap::_dmg_start)
{
	std::cout << ScavTrap::_type << " " << this->_name << " constructed."
			  << '\n';
}

ScavTrap::ScavTrap(const ScavTrap& other) :
	ClapTrap(other._name, other._hp, other._ep, other._dmg)
{
	std::cout << ScavTrap::_type << " " << this->_name << " copy constructed."
			  << '\n';
}

ScavTrap::~ScavTrap()
{
	std::cout << ScavTrap::_type << " " << this->_name << " destructed."
			  << '\n';
}

ScavTrap& ScavTrap::operator=(const ScavTrap& other)
{
	std::cout << ScavTrap::_type << " " << this->_name << " copy assigned";
	if (this != &other) {
		ClapTrap::operator=(other);
	}
	else {
		std::cout << " to itself";
	}
	std::cout << "." << '\n';
	return *this;
}

void ScavTrap::attack(const std::string& target)
{
	std::cout << ScavTrap::_type << " " << this->_name;
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

void ScavTrap::guardGate()
{
	std::cout << ScavTrap::_type << " " << this->_name;
	if (this->_hp == 0) {
		std::cout
			<< " cannot go into Gate keeper mode because it's already dead."
			<< '\n';
	}
	else {
		std::cout << " is now in Gate keeper mode." << '\n';
	}
}
