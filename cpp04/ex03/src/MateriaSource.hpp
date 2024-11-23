#ifndef MATERIASOURCE_HPP
#define MATERIASOURCE_HPP

#include "IMateriaSource.hpp"

class MateriaSource : IMateriaSource {
public:
	MateriaSource();
	MateriaSource(const MateriaSource& other);
	~MateriaSource();

	MateriaSource& operator=(const MateriaSource& other);
};

#endif
