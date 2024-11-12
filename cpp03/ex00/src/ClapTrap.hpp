#ifndef CLAPTRAP_HPP
#define CLAPTRAP_HPP

#include <string>

class ClapTrap {
public:
	ClapTrap();
	ClapTrap(const std::string& name);
	ClapTrap(const ClapTrap& other);
	~ClapTrap();

	ClapTrap& operator=(const ClapTrap& other);

	void attack(const std::string& target);
	void takeDamage(unsigned int amount);
	void beRepaired(unsigned int amount);

private:
	static const unsigned int _hp_start = 10;
	static const unsigned int _ep_start = 10;
	static const unsigned int _dmg_start = 0;

	std::string _name;
	unsigned int _hp;
	unsigned int _ep;
	unsigned int _dmg;
};

#endif
