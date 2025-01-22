#include "MateriaSource.hpp"
#include "AMateria.hpp"
#include "IMateriaSource.hpp"
#include <cstddef>
#include <string>

MateriaSource::MateriaSource() : _inventory(MateriaSource::inventory_size) {}

MateriaSource::MateriaSource(const MateriaSource& other) :
    _inventory(other._inventory)
{
}

MateriaSource::MateriaSource(const IMateriaSource& other) :
    _inventory(MateriaSource::inventory_size)
{
	*this = other;
}

MateriaSource::~MateriaSource() {}

MateriaSource& MateriaSource::operator=(MateriaSource other)
{
	this->swap(other);
	return *this;
}

MateriaSource& MateriaSource::operator=(const IMateriaSource& other)
{
	const MateriaSource* derived = dynamic_cast<const MateriaSource*>(&other);
	if (derived != NULL) {
		*this = *derived;
	}
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
