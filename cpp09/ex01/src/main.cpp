#include "RPN.hpp"
#include "libftpp/Expected.hpp"
#include "libftpp/format.hpp"
#include <algorithm>
#include <exception>
#include <iostream>
#include <iterator>
#include <limits>
#include <sstream>
#include <string>

/**
 * RPN Calculator
 *
 * Works interactively and with command line arguments (whitespace separated
 * string and/or separate arguments).
 * Be aware though that the terminal line buffer has a limit, commonly 4096
 * bytes on Linux.
 */
int main(int argc, char* argv[])
try {
	std::istream* input = &std::cin;
	char delim = '\n';
	std::stringstream args;

	if (argc > 1) {
		// Chain all arguments together.
		std::copy(argv + 1,
		          argv + argc,
		          std::ostream_iterator<const char*>(args, " "));
		input = &args;
		delim = '\0';
	}

	RPN rpn;
	std::string line;
	std::cout.precision(std::numeric_limits<RPN::value_type>::digits10);
	while (std::getline(*input, line, delim)) {
		const ft::Expected<RPN::value_type, std::string> result =
		    rpn.calculate(line);
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
