#include "Zombie.hpp"

Zombie *newZombie(std::string name);
void randomChump(std::string name);

int main(void)
{
	Zombie *zombie;

	randomChump("Stack");

	{
		zombie = newZombie("Dyno");
		randomChump("Stick");
	}

	randomChump("Stuck");
	delete zombie;
}
