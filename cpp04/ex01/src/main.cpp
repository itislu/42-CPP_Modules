// NOLINTBEGIN

#include "Animal.hpp"
#include "Brain.hpp"
#include "Cat.hpp"
#include "Dog.hpp"
#include <iostream>

void fill_array(Animal* animals[]);
void delete_array(Animal* animals[]);

int main()
{
	{
		std::cout << "SUBJECT TEST CASE:\n" << '\n';
		const Animal* j = new Dog();
		const Animal* i = new Cat();

		delete j; // should not create a leak
		delete i;
	}
	std::cout << "\n\n--------------------------------------------\n\n" << '\n';
	{
		std::cout << "ARRAY OF ANIMAL POINTERS:\n" << '\n';
		Animal* animals[10];
		fill_array(animals);
		for (int i = 0; i < 10; ++i) {
			std::cout << animals[i]->getType() << ": ";
			animals[i]->makeSound();
		}
		delete_array(animals);
	}
	std::cout << "\n\n--------------------------------------------\n\n" << '\n';
	{
		std::cout << "DEEP COPY OF BRAIN:\n" << '\n';
		Cat cat1;
		Cat cat2;

		for (int _ = 0; _ < Brain::brain_size; ++_) {
			cat1.brain()->add_idea("An idea!");
		}
		std::cout << "\n🧠 CAT1 BRAIN 🧠" << '\n';
		std::cout << *cat1.brain();
		std::cout << "\n🧠 CAT2 BRAIN 🧠" << '\n';
		std::cout << *cat2.brain() << '\n';
		cat2 = cat1;
		std::cout << "\n🧠 CAT2 BRAIN 🧠" << '\n';
		std::cout << *cat2.brain();
	}
}

void fill_array(Animal* animals[])
{
	for (int i = 0; i < 10; ++i) {
		if (i % 2 == 0) {
			animals[i] = new Dog();
		}
		else {
			animals[i] = new Cat();
		}
	}
}

void delete_array(Animal* animals[])
{
	for (int i = 0; i < 10; ++i) {
		delete animals[i];
	}
}

// NOLINTEND
