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

	Inventory& operator=(Inventory other);
	AMateria* operator[](int idx);

	void add(AMateria* m);
	void remove(int idx);
	void swap(Inventory& other);
	// AMateria *index(int idx);

	static const int inventory_size = 4;

private:
	AMateria* _inventory[inventory_size];
	List<AMateria> _history;
};

#endif
