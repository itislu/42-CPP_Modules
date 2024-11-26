#include "AMateria.hpp"
#include "ICharacter.hpp"
#include <iostream>
#include <string>

AMateria::AMateria(std::string const& type) : _type(type) {}

AMateria::AMateria(const AMateria& other) : _type(other._type) {}

AMateria::~AMateria() {}

AMateria& AMateria::AMateria::operator=(const AMateria& other)
{
	(void)other;
	// AMateria* tmp = other.clone();
	// this->swap(*tmp);
	// delete tmp;
	return *this;
}

std::string const& AMateria::getType() const
{
	return this->_type;
}

void AMateria::use(ICharacter& target)
{
	std::cout << "* uses " << this->_type << "on " << target.getName() << " *"
	          << '\n';
}

void AMateria::swap(AMateria& other)
{
	(void)other;
}
