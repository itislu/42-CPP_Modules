#include "Harl.hpp"

int main(int argc, char* argv[])
{
	Harl harl;

	if (argc == 1) {
		harl.complain("DEBUG");
		harl.complain("INFO");
		harl.complain("WARNING");
		harl.complain("ERROR");
		harl.complain("BLABLA");
		harl.complain("");
	}
	else {
		for (int i = 1; i < argc; ++i) {
			harl.complain(argv[i]); // NOLINT
		}
	}
}
