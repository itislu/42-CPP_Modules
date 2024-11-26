// NOLINTBEGIN(cppcoreguidelines-pro-bounds-constant-array-index)

#include "Inventory.hpp"
#include "AMateria.hpp"
#include <cstddef>

Inventory::Inventory() : _inventory() {}

Inventory::Inventory(const Inventory& other) : _inventory()
{
	for (int i = 0; i < Inventory::inventory_size; ++i) {
		if (other._inventory[i] != NULL) {
			AMateria* m = other._inventory[i]->clone();
			this->_history.push_back(m);
			this->_inventory[i] = m;
		}
	}
}

Inventory::~Inventory()
{
	this->_history.clear();
}

Inventory& Inventory::operator=(Inventory other)
{
	this->swap(other);
	return *this;
}

AMateria* Inventory::operator[](int idx)
{
	if (idx >= 0 && idx < Inventory::inventory_size) {
		return this->_inventory[idx];
	}
	return NULL;
}

void Inventory::add(AMateria* m)
{
	for (int i = 0; i < Inventory::inventory_size; ++i) {
		if (this->_inventory[i] == NULL) {
			this->_inventory[i] = m;
			this->_history.push_back(m);
			break;
		}
	}
}

void Inventory::remove(int idx)
{
	if (idx >= 0 && idx < Inventory::inventory_size) {
		this->_inventory[idx] = NULL;
	}
}

void Inventory::swap(Inventory& other)
{
	for (int i = 0; i < Inventory::inventory_size; ++i) {
		AMateria* tmp = this->_inventory[i];
		this->_inventory[i] = other._inventory[i];
		other._inventory[i] = tmp;
	}
	this->_history.swap(other._history);
}

// AMateria* Inventory::index(int idx)
// {
// 	return (*this)[idx];
// }

// NOLINTEND(cppcoreguidelines-pro-bounds-constant-array-index)
