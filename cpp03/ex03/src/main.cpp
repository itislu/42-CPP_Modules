// NOLINTBEGIN

#include "ClapTrap.hpp"
#include "DiamondTrap.hpp"
#include "FragTrap.hpp"
#include "ScavTrap.hpp"
#include <iostream>

int main()
{
	{
		std::cout << "**************** INHERITANCE ****************" << "\n\n";

		DiamondTrap diamond1("Diamond1");
		DiamondTrap diamond2("Diamond2");
		DiamondTrap diamond3(diamond1);
		std::cout << '\n';

		diamond1.whoAmI();
		std::cout << '\n';

		diamond1.takeDamage(50);
		diamond1.takeDamage(60); // Die
		diamond1.takeDamage(10); // Already dead
		diamond1.takeDamage(0);
		std::cout << '\n';

		diamond1.beRepaired(5); // Dead
		diamond1.beRepaired(0);
		diamond2.beRepaired(5);
		diamond2.beRepaired(6);
		diamond2.beRepaired(0);
		std::cout << '\n';

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
		std::cout << '\n';

		diamond1.guardGate();
		diamond2.guardGate();
		std::cout << '\n';

		diamond1.highFivesGuys();
		diamond2.highFivesGuys();
		std::cout << '\n';

		diamond1.whoAmI();
		diamond2.whoAmI();
		std::cout << '\n';

		diamond1.print();
		std::cout << '\n';
		diamond2.print();
		std::cout << '\n';
		diamond2 = diamond1;
		diamond2.attack("Target3"); // Dead
		std::cout << '\n';
	}
	{
		std::cout << "\n\n"
		          << "*************** POLYMORPHISM ***************" << "\n\n";

		DiamondTrap* diamondPTR = new DiamondTrap;
		FragTrap* fragPTR = diamondPTR;
		ScavTrap* scavPTR = diamondPTR;
		ClapTrap* clapPTR = diamondPTR;
		std::cout << '\n';

		std::cout << "Diamond Address: " << diamondPTR << '\n';
		std::cout << "   Frag Address: " << fragPTR << '\n';
		std::cout << "   Scav Address: " << scavPTR << '\n';
		std::cout << "   Clap Address: " << clapPTR << '\n';
		std::cout << '\n';

		diamondPTR->attack("Target");
		diamondPTR->print();
		std::cout << '\n';
		fragPTR->attack("Target");
		fragPTR->print();
		std::cout << '\n';
		scavPTR->attack("Target");
		scavPTR->print();
		std::cout << '\n';
		clapPTR->attack("Target");
		clapPTR->print();
		std::cout << '\n';
		delete clapPTR;
	}
	return 0;
}

// NOLINTEND
