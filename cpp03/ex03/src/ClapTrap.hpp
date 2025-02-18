// NOLINTBEGIN(cppcoreguidelines-non-private-member-variables-in-classes)

#ifndef CLAPTRAP_HPP
#define CLAPTRAP_HPP

#include <ostream>
#include <string>

/**
 * Virtual functions just for polymorphism (pointer type different than object
 * type)
 */
class ClapTrap {
public:
	ClapTrap();
	ClapTrap(const std::string& name);
	ClapTrap(unsigned int hp, unsigned int ep, unsigned int dmg);
	ClapTrap(const std::string& name,
	         unsigned int hp,
	         unsigned int ep,
	         unsigned int dmg);
	ClapTrap(const ClapTrap& other);
	virtual ~ClapTrap();

	ClapTrap& operator=(const ClapTrap& other);

	virtual void attack(const std::string& target);
	virtual void print() const;
	void takeDamage(unsigned int amount);
	void beRepaired(unsigned int amount);

	const std::string& name() const;

	static const std::string type;

protected:
	std::string _name;
	unsigned int _hp;
	unsigned int _ep;
	unsigned int _dmg;

private:
	static const unsigned int _hp_start = 10;
	static const unsigned int _ep_start = 10;
	static const unsigned int _dmg_start = 0;
};

std::ostream& operator<<(std::ostream& os, const ClapTrap& claptrap);

#endif

// NOLINTEND(cppcoreguidelines-non-private-member-variables-in-classes)
