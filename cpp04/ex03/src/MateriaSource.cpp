#include "MateriaSource.hpp"
#include "AMateria.hpp"
#include <cstddef>
#include <string>

MateriaSource::MateriaSource() {}

MateriaSource::MateriaSource(const MateriaSource& other) :
    _templates(other._templates)
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
	this->_templates.add(m);
}

AMateria* MateriaSource::createMateria(std::string const& type)
{
	AMateria* m = this->_templates.find(type);
	if (m != NULL) {
		return m->clone();
	}
	return NULL;
}

void MateriaSource::swap(MateriaSource& other)
{
	this->_templates.swap(other._templates);
}
