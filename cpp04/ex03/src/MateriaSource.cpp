// NOLINTBEGIN(cppcoreguidelines-pro-bounds-constant-array-index)

#include "MateriaSource.hpp"
#include "AMateria.hpp"
#include <cstddef>
#include <string>

MateriaSource::MateriaSource() : _templates() {}

MateriaSource::MateriaSource(const MateriaSource& other) : _templates()
{
	for (int i = 0; i < MateriaSource::size; ++i) {
		if (other._templates[i] != NULL) {
			this->_templates[i] = other._templates[i]->clone();
		}
		else {
			this->_templates[i] = NULL;
		}
	}
}

MateriaSource::~MateriaSource()
{
	for (int i = 0; i < MateriaSource::size; ++i) {
		delete this->_templates[i];
	}
}

MateriaSource& MateriaSource::operator=(const MateriaSource& other)
{
	if (this != &other) {
		for (int i = 0; i < MateriaSource::size; ++i) {
			if (other._templates[i] != NULL) {
				this->_templates[i] = other._templates[i]->clone();
			}
			else {
				this->_templates[i] = NULL;
			}
		}
	}
	return *this;
}

void MateriaSource::learnMateria(AMateria* m)
{
	for (int i = 0; i < MateriaSource::size; ++i) {
		if (this->_templates[i] != NULL) {
			this->_templates[i] = m->clone();
			break;
		}
	}
}

AMateria* MateriaSource::createMateria(std::string const& type)
{
	for (int i = 0; i < MateriaSource::size; ++i) {
		if (this->_templates[i] != NULL
		    && this->_templates[i]->getType() == type) {
			return this->_templates[i]->clone();
		}
	}
	return NULL;
}

// NOLINTEND(cppcoreguidelines-pro-bounds-constant-array-index)
