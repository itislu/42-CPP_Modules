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

	void attack(const std::string& target);
	void whoAmI() const;

	const std::string& name() const;

private:
	static const std::string _type;
	static const unsigned int _hp_start = 100;
	static const unsigned int _ep_start = 100;
	static const unsigned int _dmg_start = 30;

	std::string _name;
};

std::ostream& operator<<(std::ostream& os, const DiamondTrap& diamondtrap);

#endif
