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

static bool
get_line(std::istream& input, bool is_interactive, std::string& line_out);

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
	std::stringstream args;
	bool is_interactive = true;

	if (argc > 1) {
		// Chain all arguments together.
		std::copy(argv + 1,
		          argv + argc,
		          std::ostream_iterator<const char*>(args, " "));
		input = &args;
		is_interactive = false;
	}

	RPN rpn;
	std::cout.precision(std::numeric_limits<RPN::value_type>::digits10);
	for (std::string line; get_line(*input, is_interactive, line);) {
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

static bool
get_line(std::istream& input, bool is_interactive, std::string& line_out)
{
	if (!input.good()) {
		return false;
	}
	char delim = '\0';
	if (is_interactive) {
		delim = '\n';
		std::cout << "> " << std::flush;
	}
	if (std::getline(input, line_out, delim).eof() && is_interactive) {
		std::cout << '\n';
		return false;
	}
	return !input.fail();
}
