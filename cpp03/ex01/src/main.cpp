// NOLINTBEGIN

#include "ScavTrap.hpp"

int main()
{
	ScavTrap scav1("Scav1");
	ScavTrap scav2("Scav2");
	ScavTrap scav3(scav1);

	scav1.takeDamage(50);
	scav1.takeDamage(60); // Die
	scav1.takeDamage(10); // Already dead
	scav1.takeDamage(0);

	scav1.beRepaired(5); // Dead
	scav1.beRepaired(0);
	scav2.beRepaired(5);
	scav2.beRepaired(6);
	scav2.beRepaired(0);

	scav1.attack("Target1"); // Dead
	scav2.attack("Target2");

	scav1.guardGate();
	scav2.guardGate();

	scav2 = scav1;
	scav2.attack("Target3"); // Dead

	return 0;
}

// NOLINTEND
