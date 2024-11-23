#include "AMateria.hpp"
#include <string>

AMateria::AMateria(std::string const& type) : _type(type) {}

std::string const& AMateria::getType() const
{
	return this->_type;
}
