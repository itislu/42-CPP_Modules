#include "HumanA.hpp"
#include "HumanB.hpp"
#include "Weapon.hpp"

int main()
{
	{
		Weapon club = Weapon("crude spiked club");

		HumanA bob("Bob", club);
		bob.attack();
		club.setType("some other type of club");
		bob.attack();
	}
	{
		Weapon club = Weapon("crude spiked club");

		HumanB jim("Jim");
		jim.setWeapon(club);
		jim.attack();
		club.setType("some other type of club");
		jim.attack();
	}

	{
		Weapon axe = Weapon("axe");

		HumanB knopf("Knopf");
		knopf.attack();
		knopf.setWeapon(axe);
		knopf.attack();
		axe.setType("fist");
		knopf.attack();
	}

	return 0;
}
