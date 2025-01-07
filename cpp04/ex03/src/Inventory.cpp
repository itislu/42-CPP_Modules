// NOLINTBEGIN(cppcoreguidelines-pro-bounds-pointer-arithmetic)

#include "Inventory.hpp"
#include "AMateria.hpp"
// #include "RefCountedList.hpp"
#include <cstddef>
#include <string>

// RefCountedList<AMateria*> Inventory::_history;

Inventory::Inventory(unsigned int size) :
    _inventory(new AMateria*[size]()), _size(size)
{
}

Inventory::Inventory(const Inventory& other) :
    _inventory(new AMateria*[other._size]()), _size(other._size)
{
	for (unsigned int i = 0; i < this->_size; ++i) {
		if (other._inventory[i] != NULL) {
			AMateria* m = other._inventory[i]->clone();
			// Inventory::_history.push_back(m);
			this->_inventory[i] = m;
		}
		// this->_inventory[i] = other._inventory[i];
	}
}

Inventory::~Inventory()
{
	// for (unsigned int i = 0; i < this->_size; ++i) {
	// 	if (this->_inventory[i] != NULL) {
	// 		Inventory::_history.remove(this->_inventory[i]);
	// 	}
	// }
	delete[] this->_inventory;
}

Inventory& Inventory::operator=(Inventory other)
{
	this->swap(other);
	return *this;
}

AMateria* Inventory::operator[](unsigned int idx)
{
	if (idx < this->_size) {
		return this->_inventory[idx];
	}
	return NULL;
}

void Inventory::add(AMateria* m)
{
	for (unsigned int i = 0; i < this->_size; ++i) {
		if (this->_inventory[i] == NULL) {
			this->_inventory[i] = m;
			// Inventory::_history.push_back(m);
			return;
		}
	}
	// if (Inventory::_history.find(m) == NULL) {
	// 	delete m;
	// }
}

// Does not decrease references
void Inventory::remove(unsigned int idx)
{
	if (idx < this->_size) {
		this->_inventory[idx] = NULL;
	}
}

// void Inventory::track(AMateria* m)
// {
// 	Inventory::_history.push_back(m);
// }

void Inventory::swap(Inventory& other)
{
	AMateria** tmp_inventory = this->_inventory;
	this->_inventory = other._inventory;
	other._inventory = tmp_inventory;

	const unsigned int tmp_size = this->_size;
	this->_size = other._size;
	other._size = tmp_size;
}

AMateria* Inventory::find(const std::string& type)
{
	for (unsigned int i = 0; i < this->_size; ++i) {
		if (this->_inventory[i] != NULL
		    && this->_inventory[i]->getType() == type) {
			return this->_inventory[i];
		}
	}
	return NULL;
}

// NOLINTEND(cppcoreguidelines-pro-bounds-pointer-arithmetic)
