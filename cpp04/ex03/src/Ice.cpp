#include "Ice.hpp"
#include "AMateria.hpp"
#include <iostream>

Ice::Ice() : AMateria("ice") {}

Ice::Ice(const Ice& other) : AMateria(other) {}

Ice::~Ice() {}

Ice& Ice::operator=(const Ice& other)
{
	if (this != &other) {
		this->AMateria::operator=(other);
	}
	return *this;
}

AMateria* Ice::clone() const
{
	return new Ice;
}

void Ice::use(ICharacter& target)
{
	std::cout << "* shoots an ice bolt at " << target.getName() << " *" << '\n';
}
