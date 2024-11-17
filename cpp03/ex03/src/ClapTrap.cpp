#include "ClapTrap.hpp"
#include <iostream>
#include <string>

const std::string ClapTrap::_type = "ClapTrap";

ClapTrap::ClapTrap() :
	_hp(ClapTrap::_hp_start),
	_ep(ClapTrap::_ep_start),
	_dmg(ClapTrap::_dmg_start)
{
	std::cout << "Unnamed " << ClapTrap::_type << " default constructed."
			  << '\n';
}

ClapTrap::ClapTrap(const std::string& name) :
	_name(name),
	_hp(ClapTrap::_hp_start),
	_ep(ClapTrap::_ep_start),
	_dmg(ClapTrap::_dmg_start)
{
	std::cout << ClapTrap::_type << " " << "'" << this->_name << "'"
			  << " with default values constructed." << '\n';
}

ClapTrap::ClapTrap(unsigned int hp, unsigned int ep, unsigned int dmg) :
	_hp(hp), _ep(ep), _dmg(dmg)
{
	std::cout << "Unnamed " << ClapTrap::_type << " constructed." << '\n';
}

ClapTrap::ClapTrap(const std::string& name,
				   unsigned int hp,
				   unsigned int ep,
				   unsigned int dmg) :
	_name(name), _hp(hp), _ep(ep), _dmg(dmg)
{
	std::cout << ClapTrap::_type << " " << "'" << this->_name << "'"
			  << " with custom values constructed." << '\n';
}

ClapTrap::ClapTrap(const ClapTrap& other) :
	_name(other._name), _hp(other._hp), _ep(other._ep), _dmg(other._dmg)
{
	std::cout << ClapTrap::_type << " " << "'" << this->_name << "'"
			  << " copy constructed." << '\n';
}

ClapTrap::~ClapTrap()
{
	std::cout << ClapTrap::_type << " " << "'" << this->_name << "'"
			  << " destructed." << '\n';
}

ClapTrap& ClapTrap::operator=(const ClapTrap& other)
{
	std::cout << ClapTrap::_type << " " << "'" << this->_name << "'"
			  << " copy assigned";
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

void ClapTrap::attack(const std::string& target)
{
	std::cout << ClapTrap::_type << " " << "'" << this->_name << "'";
	if (this->_hp == 0) {
		std::cout << " cannot attack because it's already dead." << '\n';
	}
	else if (this->_ep == 0) {
		std::cout << " cannot attack because it has no energy points left."
				  << '\n';
	}
	else {
		this->_ep -= 1;
		std::cout << " attacks " << target << ", causing " << this->_dmg
				  << " points of damage!" << '\n';
	}
}

void ClapTrap::takeDamage(unsigned int amount)
{
	std::cout << ClapTrap::_type << " " << "'" << this->_name << "'";
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
	std::cout << ClapTrap::_type << " " << "'" << this->_name << "'";
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

const std::string& ClapTrap::name() const
{
	return this->_name;
}

unsigned int ClapTrap::hp() const
{
	return this->_hp;
}

unsigned int ClapTrap::ep() const
{
	return this->_ep;
}

unsigned int ClapTrap::dmg() const
{
	return this->_dmg;
}

std::ostream& operator<<(std::ostream& os, const ClapTrap& claptrap)
{
	os << "\tClapTrap name: " << claptrap.name() << '\n';
	os << "\tHealth: " << claptrap.hp() << '\n';
	os << "\tEnergy: " << claptrap.ep() << '\n';
	os << "\tDamage: " << claptrap.dmg() << '\n';
	return os;
}