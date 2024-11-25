#ifndef MATERIASOURCE_HPP
#define MATERIASOURCE_HPP

#include "AMateria.hpp"
#include "IMateriaSource.hpp"
#include <string>

class MateriaSource : public IMateriaSource {
public:
	MateriaSource();
	MateriaSource(const MateriaSource& other);
	~MateriaSource();

	MateriaSource& operator=(const MateriaSource& other);

	void learnMateria(AMateria* m);
	AMateria* createMateria(std::string const& type);

	static const int size = 4;

private:
	AMateria* _templates[MateriaSource::size];
};

#endif
