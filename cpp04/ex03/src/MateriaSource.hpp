#ifndef MATERIASOURCE_HPP
#define MATERIASOURCE_HPP

#include "AMateria.hpp"
#include "IMateriaSource.hpp"
#include "Inventory.hpp"
#include <string>

class MateriaSource : public IMateriaSource {
public:
	MateriaSource();
	MateriaSource(const MateriaSource& other);
	~MateriaSource();

	MateriaSource& operator=(MateriaSource other);

	void learnMateria(AMateria* m);
	AMateria* createMateria(std::string const& type);
	void swap(MateriaSource& other);

private:
	Inventory _templates;
};

#endif
