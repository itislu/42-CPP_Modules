#ifndef CURE_HPP
#define CURE_HPP

#include "AMateria.hpp"
#include "ICharacter.hpp"

class Cure : public AMateria {
public:
	Cure();
	Cure(const Cure& other);
	~Cure();

	Cure& operator=(const Cure& other);

	virtual AMateria* clone() const;
	void use(ICharacter& target);
};

#endif
