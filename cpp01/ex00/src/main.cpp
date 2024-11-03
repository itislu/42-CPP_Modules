#include "Zombie.hpp"

Zombie* newZombie(std::string name);
void randomChump(std::string name);

int main()
{
	Zombie* zombie;

	randomChump("Stack");

	{
		zombie = newZombie("Dyno");
		randomChump("Stick");
	}

	randomChump("Stuck");
	delete zombie;
}
