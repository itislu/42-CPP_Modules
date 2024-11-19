#ifndef FRAGTRAP_HPP
#define FRAGTRAP_HPP

#include "ClapTrap.hpp"
#include <ostream>
#include <string>

class FragTrap : public ClapTrap {
public:
	FragTrap();
	FragTrap(const std::string& name);
	FragTrap(const FragTrap& other);
	~FragTrap();

	FragTrap& operator=(const FragTrap& other);

	void highFivesGuys() const;

	static const std::string type;

private:
	static const unsigned int _hp_start = 100;
	static const unsigned int _ep_start = 100;
	static const unsigned int _dmg_start = 30;
};

std::ostream& operator<<(std::ostream& os, const FragTrap& fragtrap);

#endif
