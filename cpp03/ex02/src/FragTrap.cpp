#include "FragTrap.hpp"
#include "ClapTrap.hpp"
#include <iostream>
#include <string>

const std::string FragTrap::_type = "FragTrap";

FragTrap::FragTrap() :
	ClapTrap(FragTrap::_hp_start, FragTrap::_ep_start, FragTrap::_dmg_start)
{
	std::cout << "Unnamed " << FragTrap::_type << " default constructed."
			  << '\n';
}

FragTrap::FragTrap(const std::string& name) :
	ClapTrap(name,
			 FragTrap::_hp_start,
			 FragTrap::_ep_start,
			 FragTrap::_dmg_start)
{
	std::cout << FragTrap::_type << " " << this->_name << " constructed."
			  << '\n';
}

FragTrap::FragTrap(const FragTrap& other) :
	ClapTrap(other._name, other._hp, other._ep, other._dmg)
{
	std::cout << FragTrap::_type << " " << this->_name << " copy constructed."
			  << '\n';
}

FragTrap::~FragTrap()
{
	std::cout << FragTrap::_type << " " << this->_name << " destructed."
			  << '\n';
}

FragTrap& FragTrap::operator=(const FragTrap& other)
{
	std::cout << FragTrap::_type << " " << this->_name << " copy assigned";
	if (this != &other) {
		ClapTrap::operator=(other);
	}
	else {
		std::cout << " to itself";
	}
	std::cout << "." << '\n';
	return *this;
}

void FragTrap::highFivesGuys()
{
	std::cout << FragTrap::_type << " " << this->_name;
	if (this->_hp == 0) {
		std::cout << " cannot request a high five because it's already dead."
				  << '\n';
	}
	else {
		std::cout << " requests a high five." << '\n';
	}
}
