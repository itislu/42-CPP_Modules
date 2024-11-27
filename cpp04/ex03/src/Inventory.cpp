// NOLINTBEGIN(cppcoreguidelines-pro-bounds-pointer-arithmetic)

#include "Inventory.hpp"
#include "AMateria.hpp"
#include "List.hpp"
#include <cstddef>
#include <string>

List<AMateria> Inventory::_history;

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
			Inventory::_history.push_back(m);
			this->_inventory[i] = m;
		}
	}
}

Inventory::~Inventory()
{
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
			if (Inventory::_history.find(m) == NULL) {
				Inventory::_history.push_back(m);
			}
			return;
		}
	}
	delete m;
}

void Inventory::remove(unsigned int idx)
{
	if (idx < this->_size) {
		this->_inventory[idx] = NULL;
	}
}

void Inventory::swap(Inventory& other)
{
	AMateria** tmp_inventory = this->_inventory;
	this->_inventory = other._inventory;
	other._inventory = tmp_inventory;

	unsigned int tmp_size = this->_size;
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
