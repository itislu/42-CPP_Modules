#ifndef INVENTORY_HPP
#define INVENTORY_HPP

#include "AMateria.hpp"
#include "List.hpp"

class Character;

class Inventory {
public:
	Inventory();
	Inventory(const Inventory& other);
	~Inventory();

	Inventory& operator=(const Inventory& other);
	AMateria* operator[](int idx);

	void add(AMateria *m);
	void remove(int idx);
	// AMateria *index(int idx);

	static const int inventory_size = 4;

private:
	AMateria* _inventory[inventory_size]; // Maybe make dynamic with param for constructor
	List _history;
};

#endif
