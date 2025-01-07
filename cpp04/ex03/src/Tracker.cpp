// // NOLINTBEGIN(cppcoreguidelines-pro-bounds-pointer-arithmetic)

// #include "Tracker.hpp"
// #include "AMateria.hpp"
// #include "RefCountedList.hpp"
// #include <cstddef>
// #include <string>

// RefCountedList<AMateria*> Tracker::_history;

// Tracker::Tracker() {}

// Tracker::Tracker(const Tracker& other)
// {
// 	Tracker::_history(other);
// 	for (unsigned int i = 0; i < this->_size; ++i) {
// 		if (other._inventory[i] != NULL) {
// 			AMateria* m = other._inventory[i]->clone();
// 			// Tracker::_history.push_back(m);
// 			this->_inventory[i] = m;
// 		}
// 	}
// }

// Tracker::~Tracker()
// {
// 	// for (unsigned int i = 0; i < this->_size; ++i) {
// 	// 	if (this->_inventory[i] != NULL) {
// 	// 		Tracker::_history.remove(this->_inventory[i]);
// 	// 	}
// 	// }
// 	delete[] this->_inventory;
// }

// Tracker& Tracker::operator=(Tracker other)
// {
// 	this->swap(other);
// 	return *this;
// }

// AMateria* Tracker::operator[](unsigned int idx)
// {
// 	if (idx < this->_size) {
// 		return this->_inventory[idx];
// 	}
// 	return NULL;
// }

// void Tracker::add(AMateria* m)
// {
// 	for (unsigned int i = 0; i < this->_size; ++i) {
// 		if (this->_inventory[i] == NULL) {
// 			this->_inventory[i] = m;
// 			// Tracker::_history.push_back(m);
// 			return;
// 		}
// 	}
// 	// if (Tracker::_history.find(m) == NULL) {
// 	// 	delete m;
// 	// }
// }

// // Does not decrease references
// void Tracker::remove(unsigned int idx)
// {
// 	if (idx < this->_size) {
// 		this->_inventory[idx] = NULL;
// 	}
// }

// // void Tracker::track(AMateria* m)
// // {
// // 	Tracker::_history.push_back(m);
// // }

// void Tracker::swap(Tracker& other)
// {
// 	AMateria** tmp_inventory = this->_inventory;
// 	this->_inventory = other._inventory;
// 	other._inventory = tmp_inventory;

// 	const unsigned int tmp_size = this->_size;
// 	this->_size = other._size;
// 	other._size = tmp_size;
// }

// AMateria* Tracker::find(const std::string& type)
// {
// 	for (unsigned int i = 0; i < this->_size; ++i) {
// 		if (this->_inventory[i] != NULL
// 		    && this->_inventory[i]->getType() == type) {
// 			return this->_inventory[i];
// 		}
// 	}
// 	return NULL;
// }

// // NOLINTEND(cppcoreguidelines-pro-bounds-pointer-arithmetic)
