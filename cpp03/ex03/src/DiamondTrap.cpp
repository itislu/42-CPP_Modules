#include "DiamondTrap.hpp"
#include "ClapTrap.hpp"
#include "FragTrap.hpp"
#include "ScavTrap.hpp"
#include <iostream>
#include <string>

const std::string DiamondTrap::_type = "DiamondTrap";

DiamondTrap::DiamondTrap() :
	ClapTrap("_clap_name",
			 FragTrap::_hp_start,
			 ScavTrap::_ep_start,
			 FragTrap::_dmg_start)
{
	std::cout << "Unnamed " << DiamondTrap::_type << " default constructed."
			  << '\n';
}

/**
 * This constructor starts the inheritance chain, therefore this constructor
 * decides which base class constructors get called - even for multi-level
 * inheritance.
 * If no constructor gets specified, the default constructor is chosen - even if
 * other constructors in the chain specify something else.
 */
DiamondTrap::DiamondTrap(const std::string& name) :
	ClapTrap(name + "_clap_name",
			 FragTrap::_hp_start,
			 ScavTrap::_ep_start,
			 FragTrap::_dmg_start),
	ScavTrap(name),
	FragTrap(name),
	_name(name)
{
	std::cout << DiamondTrap::_type << " " << "'" << this->_name << "'"
			  << " constructed." << '\n';
}

DiamondTrap::DiamondTrap(const DiamondTrap& other) :
	ClapTrap(other._name + "_clap_name", other._hp, other._ep, other._dmg),
	ScavTrap(other),
	FragTrap(other),
	_name(other._name)
{
	std::cout << DiamondTrap::_type << " " << "'" << this->_name << "'"
			  << " copy constructed." << '\n';
}

DiamondTrap::~DiamondTrap()
{
	std::cout << DiamondTrap::_type << " " << "'" << this->_name << "'"
			  << " destructed." << '\n';
}

DiamondTrap& DiamondTrap::operator=(const DiamondTrap& other)
{
	std::cout << DiamondTrap::_type << " " << "'" << this->_name << "'"
			  << " copy assigned";
	if (this != &other) {
		ClapTrap::operator=(other);
		this->_name = other._name;
	}
	else {
		std::cout << " to itself";
	}
	std::cout << "." << '\n';
	return *this;
}

void DiamondTrap::whoAmI() const
{
	std::cout << "I am " << "'" << this->_name << "'"
			  << " and my ClapTrap name is " << "'" << this->ClapTrap::name()
			  << "'";
	if (this->_hp == 0) {
		std::cout << ", and I'm dead";
	}
	std::cout << "." << '\n';
}

const std::string& DiamondTrap::name() const
{
	return this->_name;
}

std::ostream& operator<<(std::ostream& os, const DiamondTrap& diamondtrap)
{
	os << "\tDiamondTrap name: " << diamondtrap.name() << '\n';
	os << (const ClapTrap&)diamondtrap;
	return os;
}
