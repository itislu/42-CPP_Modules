// NOLINTBEGIN(cppcoreguidelines-avoid-const-or-ref-data-members)
// NOLINTBEGIN(cppcoreguidelines-non-private-member-variables-in-classes)

#ifndef AMATERIA_HPP
#define AMATERIA_HPP

#include "RcList.hpp"
#include <cstddef>
#include <string>

class ICharacter;

class AMateria {
public:
	AMateria(std::string const& type);
	AMateria(const AMateria& other);
	virtual ~AMateria();

	AMateria& operator=(const AMateria& other);
	static void* operator new(size_t size);
	static void operator delete(void* ptr);

	std::string const& getType() const; // Returns the materia type

	virtual AMateria* clone() const = 0;
	virtual void use(ICharacter& target);
	virtual void swap(AMateria& other);

protected:
	const std::string _type;

private:
	AMateria();

	static RcList<AMateria*> _history;
};

#endif

// NOLINTEND(cppcoreguidelines-non-private-member-variables-in-classes)
// NOLINTEND(cppcoreguidelines-avoid-const-or-ref-data-members)
