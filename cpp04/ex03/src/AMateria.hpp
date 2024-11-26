// NOLINTBEGIN(cppcoreguidelines-avoid-const-or-ref-data-members)
// NOLINTBEGIN(cppcoreguidelines-non-private-member-variables-in-classes)

#ifndef AMATERIA_HPP
#define AMATERIA_HPP

#include <string>

class ICharacter;

class AMateria {
public:
	AMateria(std::string const& type);
	AMateria(const AMateria& other);
	virtual ~AMateria();

	AMateria& operator=(const AMateria& other);

	std::string const& getType() const; // Returns the materia type

	virtual AMateria* clone() const = 0;
	virtual void use(ICharacter& target);

protected:
	const std::string _type;

private:
	AMateria();
};

#endif

// NOLINTEND(cppcoreguidelines-non-private-member-variables-in-classes)
// NOLINTEND(cppcoreguidelines-avoid-const-or-ref-data-members)
