// NOLINTBEGIN(cppcoreguidelines-pro-bounds-pointer-arithmetic)

#include "Inventory.hpp"
#include "AMateria.hpp"
#include "RcList.hpp"
#include <cstddef>
#include <cstring>
#include <string>

extern RcList<AMateria*> g_ref_counter; // NOLINT

Inventory::Inventory(unsigned int size) :
    _inventory(new AMateria*[size]()), _size(size)
{
}

Inventory::Inventory(const Inventory& other) :
    _inventory(new AMateria*[other._size]()), _size(other._size)
{
	for (unsigned int i = 0; i < this->_size; ++i) {
		if (other._inventory[i] != NULL) {
			this->_inventory[i] = other._inventory[i]->clone();
		}
	}
}

Inventory::~Inventory()
{
	for (unsigned int i = 0; i < this->_size; ++i) {
		if (this->_inventory[i] != NULL) {
			g_ref_counter.remove(this->_inventory[i]);
		}
	}
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
	if (m == NULL) {
		return;
	}
	for (unsigned int i = 0; i < this->_size; ++i) {
		if (this->_inventory[i] == NULL) {
			// Since every newed AMateria is already in the history, this is a
			// check to only increase the refs for heap-based AMaterias
			if (g_ref_counter.contains(m)) {
				g_ref_counter.push_back(m);
			}
			this->_inventory[i] = m;
			return;
		}
	}
}

void Inventory::remove(unsigned int idx)
{
	if (idx < this->_size && this->_inventory[idx] != NULL) {
		g_ref_counter.remove(this->_inventory[idx]);
		this->_inventory[idx] = NULL;
	}
}

void Inventory::swap(Inventory& other)
{
	char tmp[sizeof(Inventory)];

	memcpy(
	    static_cast<void*>(tmp), static_cast<void*>(this), sizeof(Inventory));
	memcpy(static_cast<void*>(this),
	       static_cast<void*>(&other),
	       sizeof(Inventory));
	memcpy(
	    static_cast<void*>(&other), static_cast<void*>(tmp), sizeof(Inventory));
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
