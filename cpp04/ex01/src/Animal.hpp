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

	virtual void makeSound() const;
	virtual Brain* brain();
	const std::string& getType() const;

protected:
	std::string _type;
};

#endif

// NOLINTEND(cppcoreguidelines-non-private-member-variables-in-classes)
