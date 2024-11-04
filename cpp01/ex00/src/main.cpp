#include "Zombie.hpp"
#include <cstddef>
#include <string>

Zombie* newZombie(std::string name);
void randomChump(std::string name);

int main()
{
	Zombie* zombie = NULL;

	randomChump("Stack");

	{
		zombie = newZombie("Dyno");
		randomChump("Stick");
	}

	randomChump("Stuck");
	delete zombie;
}
