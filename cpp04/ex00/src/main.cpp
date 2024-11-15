#include "Animal.hpp"
#include "Cat.hpp"
#include "Dog.hpp"
#include "WrongAnimal.hpp"
#include "WrongCat.hpp"
#include <iostream>

int main()
{
	std::cout << "SUBJECT TEST CASES:" << '\n';
	const Animal* meta = new Animal();
	const Animal* j = new Dog();
	const Animal* i = new Cat();
	std::cout << j->getType() << " " << std::endl;
	std::cout << i->getType() << " " << std::endl;
	i->makeSound(); // will output the cat sound!
	j->makeSound();
	meta->makeSound();

	delete meta;
	delete i;
	delete j;


	std::cout << "\nMY TEST CASES:" << '\n';

	Animal* animal = new Animal();
	Animal* dog = new Dog();
	Animal* cat = new Cat();
	std::cout << animal->getType() << '\n';
	std::cout << dog->getType() << '\n';
	std::cout << cat->getType() << '\n';
	animal->makeSound();
	dog->makeSound();
	cat->makeSound();

	delete animal;
	delete dog;
	delete cat;


	std::cout << "\nMY WRONG_ANIMAL TEST CASES:" << '\n';
	WrongAnimal* wrong_animal = new WrongAnimal();
	WrongAnimal* wrong_cat = new WrongCat();
	std::cout << wrong_animal->getType() << '\n';
	std::cout << wrong_cat->getType() << '\n';
	wrong_animal->makeSound();
	wrong_cat->makeSound();

	delete wrong_animal;
	delete wrong_cat;

}
