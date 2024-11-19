#ifndef SCAVTRAP_HPP
#define SCAVTRAP_HPP

#include "ClapTrap.hpp"
#include <ostream>
#include <string>

class ScavTrap : public virtual ClapTrap {
public:
	ScavTrap();
	ScavTrap(const std::string& name);
	ScavTrap(const ScavTrap& other);
	~ScavTrap();

	ScavTrap& operator=(const ScavTrap& other);

	void attack(const std::string& target);
	void guardGate() const;

	static const std::string type;

protected:
	static const unsigned int _hp_start = 100;
	static const unsigned int _ep_start = 50;
	static const unsigned int _dmg_start = 20;
};

std::ostream& operator<<(std::ostream& os, const ScavTrap& scavtrap);

#endif
