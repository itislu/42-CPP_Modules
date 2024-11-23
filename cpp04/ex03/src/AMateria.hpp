#ifndef AMATERIA_HPP
#define AMATERIA_HPP

#include <string>

class ICharacter;

class AMateria {
public:
	AMateria(std::string const& type);
	virtual ~AMateria();

	std::string const& getType() const; // Returns the materia type

	virtual AMateria* clone() const = 0;
	virtual void use(ICharacter& target);

protected:
	AMateria();
	AMateria(const AMateria& other);

	AMateria& operator=(const AMateria& other);

	std::string _type;

private:
};

#endif
