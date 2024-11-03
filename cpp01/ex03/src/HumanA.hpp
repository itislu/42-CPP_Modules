#ifndef HUMANA_HPP
#define HUMANA_HPP

#include "Weapon.hpp"
#include <string>

class HumanA {
public:
	HumanA(const std::string& name, Weapon& weapon);

	void attack() const;

private:
	std::string _name;
	Weapon* _weapon;
};

#endif
