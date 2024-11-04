// NOLINTBEGIN

#include "Zombie.hpp"
#include <sstream>
#include <string>

Zombie* zombieHorde(int N, std::string name);
static int to_int(const char* str);

int main(int argc, char* argv[])
{
	int n = 10;
	std::string name("Frank");

	if (argc > 1) {
		n = to_int(argv[1]);
	}
	if (argc > 2) {
		name = argv[2];
	}

	Zombie* horde = zombieHorde(n, name);

	for (int i = 0; i < n; ++i) {
		horde[i].announce();
	}

	delete[] horde;
}

static int to_int(const char* str)
{
	int res = 0;
	std::istringstream iss(str);

	iss >> res;
	return res;
}

// NOLINTEND
