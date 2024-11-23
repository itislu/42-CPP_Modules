#include "Cure.hpp"
#include "AMateria.hpp"
#include <iostream>

Cure::Cure() : AMateria("cure") {}

Cure::Cure(const Cure& other) : AMateria(other._type) {}

Cure::~Cure() {}

Cure& Cure::operator=(const Cure& other)
{
	if (this != &other) {
	}
	return *this;
}

AMateria* Cure::clone() const
{
	return new Cure;
}

void Cure::use(ICharacter& target)
{
	std::cout << "* heals " << target.getName() << "'s wounds *" << '\n';
}
