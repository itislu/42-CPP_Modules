// NOLINTBEGIN(cppcoreguidelines-non-private-member-variables-in-classes)

#ifndef AANIMAL_HPP
#define AANIMAL_HPP

#include "Brain.hpp"
#include <string>

class AAnimal {
public:
	virtual ~AAnimal();

	virtual void makeSound() const = 0;
	virtual Brain* brain() = 0;
	const std::string& getType() const;

protected:
	AAnimal();
	AAnimal(const std::string& type);
	AAnimal(const AAnimal& other);

	AAnimal& operator=(const AAnimal& other);

	std::string _type;
};

#endif

// NOLINTEND(cppcoreguidelines-non-private-member-variables-in-classes)
