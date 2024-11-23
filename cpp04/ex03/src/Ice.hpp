#ifndef ICE_HPP
#define ICE_HPP

#include "AMateria.hpp"
#include "ICharacter.hpp"

class Ice : public AMateria {
public:
	Ice();
	Ice(const Ice& other);
	~Ice();

	Ice& operator=(const Ice& other);

	virtual AMateria* clone() const;
	void use(ICharacter& target);
};

#endif
