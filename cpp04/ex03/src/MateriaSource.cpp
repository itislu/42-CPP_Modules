// NOLINTBEGIN(cppcoreguidelines-pro-bounds-constant-array-index)

#include "MateriaSource.hpp"
#include "AMateria.hpp"
#include "List.hpp"
#include <cstddef>
#include <string>

List<AMateria> MateriaSource::_history;

MateriaSource::MateriaSource() : _templates() {}

MateriaSource::MateriaSource(const MateriaSource& other) : _templates()
{
	for (int i = 0; i < MateriaSource::size; ++i) {
		if (other._templates[i] != NULL) {
			AMateria* m = other._templates[i]->clone();
			MateriaSource::_history.push_back(m);
			this->_templates[i] = m;
		}
	}
}

MateriaSource::~MateriaSource() {}

MateriaSource& MateriaSource::operator=(MateriaSource other)
{
	this->swap(other);
	return *this;
}

void MateriaSource::learnMateria(AMateria* m)
{
	for (int i = 0; i < MateriaSource::size; ++i) {
		if (this->_templates[i] == NULL) {
			this->_templates[i] = m;
			if (MateriaSource::_history.find(m) == NULL) {
				MateriaSource::_history.push_back(m);
			}
			return;
		}
	}
	delete m;
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

void MateriaSource::swap(MateriaSource& other)
{
	for (int i = 0; i < MateriaSource::size; ++i) {
		AMateria* tmp = this->_templates[i];
		this->_templates[i] = other._templates[i];
		other._templates[i] = tmp;
	}
}

// NOLINTEND(cppcoreguidelines-pro-bounds-constant-array-index)
