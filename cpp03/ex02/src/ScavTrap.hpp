#ifndef SCAVTRAP_HPP
#define SCAVTRAP_HPP

#include "ClapTrap.hpp"
#include <string>

class ScavTrap : public ClapTrap {
public:
	ScavTrap();
	ScavTrap(const std::string& name);
	ScavTrap(const ScavTrap& other);
	~ScavTrap();

	ScavTrap& operator=(const ScavTrap& other);

	void attack(const std::string& target) const;
	void guardGate() const;

private:
	static const std::string _type;
	static const unsigned int _hp_start = 100;
	static const unsigned int _ep_start = 50;
	static const unsigned int _dmg_start = 20;
};

#endif
