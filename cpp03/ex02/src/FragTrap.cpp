#include "FragTrap.hpp"
#include "ClapTrap.hpp"
#include <iostream>
#include <string>

const std::string FragTrap::type = "FragTrap";

FragTrap::FragTrap() :
    ClapTrap(FragTrap::_hp_start, FragTrap::_ep_start, FragTrap::_dmg_start)
{
	std::cout << *this << " default constructed." << '\n';
}

FragTrap::FragTrap(const std::string& name) :
    ClapTrap(name,
             FragTrap::_hp_start,
             FragTrap::_ep_start,
             FragTrap::_dmg_start)
{
	std::cout << *this << " with default values constructed." << '\n';
}

FragTrap::FragTrap(const FragTrap& other) :
    ClapTrap(other._name, other._hp, other._ep, other._dmg)
{
	std::cout << *this << " copy constructed." << '\n';
}

FragTrap::~FragTrap()
{
	std::cout << *this << " destructed." << '\n';
}

FragTrap& FragTrap::operator=(const FragTrap& other)
{
	std::cout << other << " copy assigned to " << *this << "." << '\n';
	if (this != &other) {
		ClapTrap::operator=(other);
	}
	return *this;
}

void FragTrap::highFivesGuys() const
{
	std::cout << *this;
	if (this->_hp == 0) {
		std::cout << " cannot request a high five because it's already dead."
		          << '\n';
	}
	else {
		std::cout << " requests a high five." << '\n';
	}
}

std::ostream& operator<<(std::ostream& os, const FragTrap& fragtrap)
{
	if (fragtrap.name().empty()) {
		os << "Unnamed " << FragTrap::type;
	}
	else {
		os << FragTrap::type << " " << "'" << fragtrap.name() << "'";
	}
	return os;
}
