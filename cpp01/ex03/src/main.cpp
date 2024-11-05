#include "HumanA.hpp"
#include "HumanB.hpp"
#include "Weapon.hpp"
#include <iostream>

int main()
{
	std::cout << "GIVEN TEST CASE:" << "\n\n";
	{
		std::cout << "HUMAN A:" << '\n';
		Weapon club = Weapon("crude spiked club");

		HumanA bob("Bob", club);
		bob.attack();
		club.setType("some other type of club");
		bob.attack();
	}
	{
		std::cout << '\n' << "HUMAN B:" << '\n';
		Weapon club = Weapon("crude spiked club");

		HumanB jim("Jim");
		jim.setWeapon(club);
		jim.attack();
		club.setType("some other type of club");
		jim.attack();
	}

	std::cout << "\n-----\n\n"
			  << "MY TEST CASE:" << "\n\n";
	{
		std::cout << "HUMAN A:" << '\n';
		Weapon shovel = Weapon("shovel");
		Weapon axe = Weapon("axe");

		HumanA alice("Alice", shovel);
		alice.attack();
		alice.setWeapon(axe);
		alice.attack();
		axe.setType("pickaxe");
		alice.attack();
		shovel.setType("hammer");
		alice.attack();
		alice.setWeapon(shovel);
		alice.attack();
	}
	{
		std::cout << '\n' << "HUMAN B:" << '\n';
		Weapon shovel = Weapon("shovel");
		Weapon axe = Weapon("axe");

		HumanB bob("Bob");
		bob.setWeapon(shovel);
		bob.attack();
		bob.setWeapon(axe);
		bob.attack();
		axe.setType("pickaxe");
		bob.attack();
		shovel.setType("hammer");
		bob.attack();
		bob.setWeapon(shovel);
		bob.attack();
	}

	{
		std::cout << '\n' << "HUMAN B:" << '\n';
		Weapon axe = Weapon("axe");

		HumanB knopf("Knopf");
		knopf.attack();
		knopf.setWeapon(axe);
		knopf.attack();
		axe.setType("pickaxe");
		knopf.attack();
		knopf.dropWeapon();
		knopf.attack();
		knopf.dropWeapon();
	}

	return 0;
}
