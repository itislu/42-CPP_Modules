#include "MateriaSource.hpp"
#include "AMateria.hpp"
#include <cstddef>
#include <string>

MateriaSource::MateriaSource() : _inventory(MateriaSource::inventory_size) {}

MateriaSource::MateriaSource(const MateriaSource& other) :
    _inventory(other._inventory)
{
}

MateriaSource::~MateriaSource() {}

MateriaSource& MateriaSource::operator=(MateriaSource other)
{
	this->swap(other);
	return *this;
}

void MateriaSource::learnMateria(AMateria* m)
{
	this->_inventory.add(m);
}

AMateria* MateriaSource::createMateria(std::string const& type)
{
	AMateria* m = this->_inventory.find(type);
	if (m != NULL) {
		return m->clone();
	}
	return NULL;
}

void MateriaSource::swap(MateriaSource& other)
{
	this->_inventory.swap(other._inventory);
}
