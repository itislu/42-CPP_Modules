#ifndef DIAMONDTRAP_HPP
#define DIAMONDTRAP_HPP

#include "FragTrap.hpp"
#include "ScavTrap.hpp"
#include <ostream>
#include <string>

class DiamondTrap : public ScavTrap, public FragTrap {
public:
	DiamondTrap();
	DiamondTrap(const std::string& name);
	DiamondTrap(const DiamondTrap& other);
	~DiamondTrap();

	DiamondTrap& operator=(const DiamondTrap& other);

	void whoAmI() const;
	void print() const;

	const std::string& name() const;

	static const std::string type;

private:
	static const unsigned int _hp_start = FragTrap::_hp_start;
	static const unsigned int _ep_start = ScavTrap::_ep_start;
	static const unsigned int _dmg_start = FragTrap::_dmg_start;

	std::string _name;
};

std::ostream& operator<<(std::ostream& os, const DiamondTrap& diamondtrap);

#endif
