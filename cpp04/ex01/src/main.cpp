// NOLINTBEGIN

#include "Animal.hpp"
#include "Cat.hpp"
#include "Dog.hpp"
#include <iostream>

void fill_array(Animal* animals[]);
void delete_array(Animal* animals[]);

int main()
{
	std::cout << "SUBJECT TEST CASES:" << '\n';
	const Animal* j = new Dog();
	const Animal* i = new Cat();

	delete j; // should not create a leak
	delete i;


	std::cout << "\nMY TEST CASES:" << '\n';
	Animal* animals[10];
	fill_array(animals);
	for (int i = 0; i < 10; ++i) {
		animals[i]->makeSound();
	}
	delete_array(animals);

	Animal* animal = new Animal();
	Animal* dog = new Dog();
	Animal* cat = new Cat();

	delete animal;
	delete dog;
	delete cat;

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
