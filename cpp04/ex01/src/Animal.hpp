// NOLINTBEGIN(cppcoreguidelines-non-private-member-variables-in-classes)

#ifndef ANIMAL_HPP
#define ANIMAL_HPP

#include "Brain.hpp"
#include <string>

class Animal {
public:
	Animal();
	Animal(const std::string& type);
	Animal(const Animal& other);
	virtual ~Animal();

	Animal& operator=(const Animal& other);

	const std::string& getType() const;
	virtual void makeSound() const;
	virtual Brain* brain() = 0;

protected:
	std::string _type;
};

#endif

// NOLINTEND(cppcoreguidelines-non-private-member-variables-in-classes)
