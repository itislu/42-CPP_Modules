#ifndef INVENTORY_HPP
#define INVENTORY_HPP

#include "AMateria.hpp"
#include "List.hpp"
#include <string>

class Character;

class Inventory {
public:
	Inventory(unsigned int size);
	Inventory(const Inventory& other);
	~Inventory();

	Inventory& operator=(Inventory other);
	AMateria* operator[](unsigned int idx);

	void add(AMateria* m);
	void remove(unsigned int idx);
	void swap(Inventory& other);
	AMateria* find(const std::string& type);

private:
	Inventory();

	static List<AMateria> _history;

	AMateria** _inventory;
	unsigned int _size;
};

#endif
