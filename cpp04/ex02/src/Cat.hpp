#ifndef CAT_HPP
#define CAT_HPP

#include "AAnimal.hpp"
#include "Brain.hpp"

class Cat : public AAnimal {
public:
	Cat();
	Cat(const Cat& other);
	~Cat();

	Cat& operator=(const Cat& other);

	void makeSound() const;

	Brain* brain();

private:
	Brain* _brain;
};

#endif
