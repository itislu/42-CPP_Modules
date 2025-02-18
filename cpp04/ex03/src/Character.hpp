#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include "AMateria.hpp"
#include "ICharacter.hpp"
#include "Inventory.hpp"
#include <string>

class Character : public ICharacter {
public:
	Character(const std::string& name);
	Character(const Character& other);
	Character(const ICharacter& other);
	~Character();

	Character& operator=(Character other);
	Character& operator=(const ICharacter& other);

	std::string const& getName() const;
	void equip(AMateria* m);
	void unequip(int idx);
	void use(int idx, ICharacter& target);
	void swap(Character& other);

	static const unsigned int inventory_size = 4;

private:
	Character();

	std::string _name;
	Inventory _inventory;
};

#endif
