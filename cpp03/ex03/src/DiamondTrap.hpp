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
	std::string _name;
};

std::ostream& operator<<(std::ostream& os, const DiamondTrap& diamondtrap);

#endif
