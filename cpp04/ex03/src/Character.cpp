#include "Character.hpp"
#include "AMateria.hpp"
#include <cstddef>
#include <string>

Character::Character(const std::string& name) : _name(name) {}

Character::Character(const Character& other) :
    _name(other._name), _inventory(other._inventory)
{
}

Character::~Character() {}

Character& Character::operator=(const Character& other)
{
	if (this != &other) {
		this->_name = other._name;
		this->_inventory = other._inventory;
	}
	return *this;
}

std::string const& Character::getName() const
{
	return this->_name;
}

void Character::equip(AMateria* m)
{
	this->_inventory.add(m);
}

void Character::unequip(int idx)
{
	this->_inventory.remove(idx);
}

void Character::use(int idx, ICharacter& target)
{
	if (this->_inventory[idx] != NULL) {
		this->_inventory[idx]->use(target);
	}
}
