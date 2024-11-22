// NOLINTBEGIN

#include "Animal.hpp"
#include "Brain.hpp"
#include "Cat.hpp"
#include "Dog.hpp"
#include <iostream>
#include <sstream>

static unsigned int ft_atoui(char* str);
static void fill_array(Animal**& animals, unsigned int size);
static void delete_array(Animal**& animals, unsigned int size);

int main(int argc, char* argv[])
{
	unsigned int animal_count = 10;

	if (argc > 2) {
		std::cerr << "Usage: " << argv[0]
		          << " [animal_count (default: " << animal_count << ")]"
		          << '\n';
		return 1;
	}
	if (argc == 2) {
		animal_count = ft_atoui(argv[1]);
	}

	{
		std::cout << "SUBJECT TEST CASE:\n" << '\n';
		const Animal* j = new Dog();
		const Animal* i = new Cat();

		delete j; // should not create a leak
		delete i;
	}
	std::cout << "\n\n--------------------------------------------\n\n" << '\n';
	{
		std::cout << "ARRAY OF AANIMAL POINTERS:\n" << '\n';
		Animal** animals;

		fill_array(animals, animal_count);
		for (unsigned int i = 0; i < animal_count; ++i) {
			std::cout << animals[i]->getType() << ": ";
			animals[i]->makeSound();
		}
		delete_array(animals, animal_count);
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
		std::cout << '\n';
	}
}

static unsigned int ft_atoui(char* str)
{
	std::istringstream ss(str);
	unsigned int n;
	ss >> n;
	return n;
}

static void fill_array(Animal**& animals, unsigned int size)
{
	animals = new Animal*[size];
	for (unsigned int i = 0; i < size; ++i) {
		if (i % 2 == 0) {
			animals[i] = new Dog();
		}
		else {
			animals[i] = new Cat();
		}
	}
}

static void delete_array(Animal**& animals, unsigned int size)
{
	for (unsigned int i = 0; i < size; ++i) {
		delete animals[i];
	}
	delete[] animals;
}

// NOLINTEND
