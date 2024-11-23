// NOLINTBEGIN(cppcoreguidelines-pro-bounds-constant-array-index)

#include "Inventory.hpp"
#include "AMateria.hpp"
#include <cstddef>

Inventory::Inventory()
{
	for (int i = 0; i < Inventory::inventory_size; ++i) {
		this->_inventory[i] = NULL;
	}
}

Inventory::Inventory(const Inventory& other)
{
	*this = other;
	// for (int i = 0; i < Inventory::inventory_size; ++i) {
	// 	AMateria* m = other._inventory[i]->clone();
	// 	this->_history.push_back(m);
	// 	this->_inventory[i] = m;
	// }
}

Inventory::~Inventory()
{
	this->_history.clear();
}

Inventory& Inventory::operator=(const Inventory& other)
{
	if (this != &other) {
		this->_history.clear();
		// this->_history = other._history;
		for (int i = 0; i < Inventory::inventory_size; ++i) {
			AMateria* m = other._inventory[i]->clone();
			this->_history.push_back(m);
			this->_inventory[i] = m;
		}
	}
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

// AMateria* Inventory::index(int idx)
// {
// 	return (*this)[idx];
// }

// NOLINTEND(cppcoreguidelines-pro-bounds-constant-array-index)
