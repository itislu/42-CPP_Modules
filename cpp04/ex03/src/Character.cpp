#include "Character.hpp"
#include "AMateria.hpp"
#include <cstddef>
#include <string>

Character::Character(const std::string& name) :
    _name(name), _inventory(Character::inventory_size)
{
}

Character::Character(const Character& other) :
    _name(other._name), _inventory(other._inventory)
{
}

Character::Character(const ICharacter& other) :
    _inventory(Character::inventory_size)
{
	*this = other;
}

Character::~Character() {}

Character& Character::operator=(Character other)
{
	this->swap(other);
	return *this;
}

Character& Character::operator=(const ICharacter& other)
{
	const Character* derived = dynamic_cast<const Character*>(&other);
	if (derived != NULL) {
		*this = *derived;
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

void Character::swap(Character& other)
{
	this->_name.swap(other._name);
	this->_inventory.swap(other._inventory);
}
