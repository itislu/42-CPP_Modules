#ifndef CURE_HPP
#define CURE_HPP

#include "AMateria.hpp"
#include "ICharacter.hpp"

class Cure : public AMateria {
public:
	Cure();
	Cure(const Cure& other);
	~Cure();

	Cure& operator=(Cure other);

	AMateria* clone() const;
	void use(ICharacter& target);
};

#endif
