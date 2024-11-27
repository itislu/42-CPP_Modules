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

	static const unsigned int inventory_size = 4;

private:
	Inventory _templates; // TODO Rename to _inventory
};

#endif
