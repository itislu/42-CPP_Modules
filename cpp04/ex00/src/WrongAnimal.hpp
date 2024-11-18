#ifndef WRONGANIMAL_HPP
#define WRONGANIMAL_HPP

#include <string>

class WrongAnimal {
public:
	WrongAnimal();
	WrongAnimal(const std::string& type);
	WrongAnimal(const WrongAnimal& other);
	~WrongAnimal();

	WrongAnimal& operator=(const WrongAnimal& other);

	void makeSound() const;
	const std::string& getType() const;

protected:
	std::string _type;

private:
};

#endif
