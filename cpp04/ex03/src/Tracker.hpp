#ifndef TRACKER_HPP
#define TRACKER_HPP

#include "AMateria.hpp"
#include "RefCountedList.hpp"
#include <string>

class Character;

class Tracker {
public:
	Tracker();
	Tracker(const Tracker& other);
	~Tracker();

	Tracker& operator=(Tracker other);
	AMateria* operator[](unsigned int idx);

	void add(AMateria* m);
	void remove(unsigned int idx);
	// static void track(AMateria* m);
	void swap(Tracker& other);
	AMateria* find(const std::string& type);

private:
	static RefCountedList<AMateria*> _history;
};

#endif
