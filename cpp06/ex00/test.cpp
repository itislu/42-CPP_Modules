#include <cmath>
#include <iostream>

template <typename T>
void f(T nbr)
{
	int i = static_cast<int>(nbr);
	std::cout << i << '\n';
}

int main(int argc, char *argv[])
{
	(void)argv;

	f(2.1f);
}
