#ifndef MATERIASOURCE_HPP
#define MATERIASOURCE_HPP

#include "AMateria.hpp"
#include "IMateriaSource.hpp"
#include "List.hpp"
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

	static const int size = 4;

private:
	static List<AMateria> _history;

	AMateria* _templates[MateriaSource::size];
};

#endif
