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

/*
The Copy-and-Swap Idiom

The main benefit of the copy-and-swap idiom is that it provides strong exception
guarantee. In the copy assignment operator, this means that all operations which
could throw an exception (the copying) are made before the object being assigned
to gets changed.

It also helps to reuse code because assignment essentially boils down to
deletion of the original value and copying over the new value. This idiom allows
us to reuse the copy constructor and the destructor because of that fact.

It works by:
1. Taking the argument by value (which creates a copy using the copy
constructor).
2. Swapping the contents of *this with the parameter (which mustn't throw).
3. Letting the destructor clean up the old data when the parameter goes out of
scope.
*/
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
