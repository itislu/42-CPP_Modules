// NOLINTBEGIN

#include "ClapTrap.hpp"
#include "DiamondTrap.hpp"
#include "ScavTrap.hpp"
#include <iostream>

int main()
{
	DiamondTrap diamond1("Diamond1");
	diamond1.whoAmI();
	// std::cout << '\n' << diamond1 << '\n';
	std::cout << '\n';
	diamond1.print();
	std::cout << '\n';

	ClapTrap* scav1 = new ScavTrap("Scav");
	ClapTrap* clap1 = new ClapTrap("Clap");
	diamond1.attack("Target1");
	scav1->attack("Target2");
	clap1->attack("Target3");
	std::cout << "Scav Address: " << scav1 << '\n';
	std::cout << "Clap Address: " << clap1 << '\n';
	delete scav1;
	delete clap1;

	std::cout << '\n';

	DiamondTrap diamond2("Diamond2");
	DiamondTrap diamond3(diamond1);

	// std::cout << '\n' << diamond3 << '\n';
	std::cout << '\n';
	diamond3.print();
	std::cout << '\n';

	diamond1.takeDamage(50);
	diamond1.takeDamage(60); // Die
	diamond1.takeDamage(10); // Already dead
	diamond1.takeDamage(0);

	diamond1.beRepaired(5); // Dead
	diamond1.beRepaired(0);
	diamond2.beRepaired(5);
	diamond2.beRepaired(6);
	diamond2.beRepaired(0);

	diamond1.attack("Target1"); // Dead
	diamond2.attack("Target2");
	diamond2.attack("Target3");
	diamond2.attack("Target4");
	diamond2.attack("Target5");
	diamond2.attack("Target6");
	diamond2.attack("Target7");
	diamond2.attack("Target8");
	diamond2.attack("Target9");
	diamond2.attack("Target10");

	diamond1.guardGate();
	diamond2.guardGate();

	diamond1.highFivesGuys();
	diamond2.highFivesGuys();

	diamond1.whoAmI();
	diamond2.whoAmI();

	diamond2 = diamond1;
	diamond2.attack("Target3"); // Dead

	return 0;
}

// NOLINTEND
