#include "RPN.hpp"
#include "libftpp/Expected.hpp"
#include "libftpp/format.hpp"
#include <exception>
#include <iostream>
#include <sstream>
#include <string>

/**
 * RPN Calculator
 *
 * Works interactively and with command line arguments (whitespace separated
 * string and/or separate arguments).
 */
int main(int argc, char* argv[])
try {
	std::istream* input = &std::cin;
	char delim = '\n';
	std::stringstream args;

	if (argc > 1) {
		// Chain all arguments together
		for (int i = 1; i < argc; ++i) {
			// NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-pointer-arithmetic)
			args << argv[i] << ' ';
		}
		input = &args;
		delim = '\0';
	}

	RPN rpn;
	std::string line;
	while (std::getline(*input, line, delim)) {
		const ft::Expected<long, std::string> result = rpn.calculate(line);
		if (result) {
			std::cout << *result << '\n';
		}
		else {
			std::cout << result.error() << '\n';
		}
	}

	return 0;
}
catch (const std::exception& e) {
	std::cerr << ft::log::error(BOLD("Unexpected exception: ") + e.what())
	          << '\n';
	return 1;
}
