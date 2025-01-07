#include "AMateria.hpp"
#include "ICharacter.hpp"
#include "RefCountedList.hpp"
#include <cstddef>
#include <iostream>
#include <new>
#include <string>

RefCountedList<AMateria*> AMateria::_history;

AMateria::AMateria(std::string const& type) : _type(type) {}

AMateria::AMateria(const AMateria& other) : _type(other._type) {}

AMateria::~AMateria() {}

AMateria& AMateria::operator=(const AMateria& other)
{
	(void)other;
	// AMateria* tmp = other.clone();
	// this->swap(*tmp);
	// delete tmp;
	return *this;
}

void* AMateria::operator new(size_t size)
{
	std::cout << "Custom AMateria new with size " << size << '\n';
	AMateria* ptr = (AMateria*)::operator new(size); //NOLINT tmp
	AMateria::_history.push_back(ptr);
	return ptr;
}

void AMateria::operator delete(void* ptr)
{
	std::cout << "Custom AMateria delete" << '\n';
	AMateria::_history.remove((AMateria*)ptr); //NOLINT tmp
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
