#include "DiamondTrap.hpp"
#include "ClapTrap.hpp"
#include "FragTrap.hpp"
#include "ScavTrap.hpp"
#include <iostream>
#include <string>

const std::string DiamondTrap::type = "DiamondTrap";

DiamondTrap::DiamondTrap() :
    ClapTrap("_clap_name",
             FragTrap::_hp_start,
             ScavTrap::_ep_start,
             FragTrap::_dmg_start)
{
	std::cout << *this << " default constructed." << '\n';
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
	std::cout << *this << " constructed." << '\n';
}

DiamondTrap::DiamondTrap(const DiamondTrap& other) :
    ClapTrap(other._name + "_clap_name", other._hp, other._ep, other._dmg),
    ScavTrap(other),
    FragTrap(other),
    _name(other._name)
{
	std::cout << *this << " copy constructed." << '\n';
}

DiamondTrap::~DiamondTrap()
{
	std::cout << *this << " destructed." << '\n';
}

DiamondTrap& DiamondTrap::operator=(const DiamondTrap& other)
{
	std::cout << other << " copy assigned to " << *this << "." << '\n';
	if (this != &other) {
		ClapTrap::operator=(other);
		this->_name = other._name;
	}
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

void DiamondTrap::print() const
{
	std::cout << "\tDiamondTrap name: " << this->_name << '\n';
	this->ClapTrap::print();
}

const std::string& DiamondTrap::name() const
{
	return this->_name;
}

std::ostream& operator<<(std::ostream& os, const DiamondTrap& diamondtrap)
{
	if (diamondtrap.name().empty()) {
		os << "Unnamed " << DiamondTrap::type;
	}
	else {
		os << DiamondTrap::type << " " << "'" << diamondtrap.name() << "'";
	}
	return os;
}
