#include "AMateria.hpp"
#include "ICharacter.hpp"
#include "RcList.hpp"
#include <cstddef>
#include <iostream>
#include <new>
#include <string>

RcList<AMateria*> AMateria::_history;

AMateria::AMateria(std::string const& type) : _type(type) {}

AMateria::AMateria(const AMateria& other) : _type(other._type) {}

AMateria::~AMateria()
{
	std::cout << "AMateria destructor of " << this << '\n';
}

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
	AMateria* ptr = static_cast<AMateria*>(::operator new(size));
	AMateria::_history.push_back(ptr);
	return ptr;
}

void AMateria::operator delete(void* ptr)
{
	std::cout << "Custom AMateria delete" << '\n';
	AMateria::_history.forget(static_cast<AMateria*>(ptr));
	::operator delete(ptr);
}

void AMateria::clear()
{
	AMateria::_history.clear();
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
