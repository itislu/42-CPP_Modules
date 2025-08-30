#include "libftpp/format.hpp"
#include "libftpp/numeric.hpp"
#include "utils.hpp"
#include <iostream>
#include <string>

void print_seperator(const std::string& title)
{
	const std::string::size_type width = 60;
	const std::string::size_type padding = 2;

	const std::string::size_type available =
	    ft::sub_sat(width, title.length() + padding);
	const std::string::size_type left = available / 2;
	const std::string::size_type right = available - left;

	std::cout << "\n\n"
	          << BOLD(std::string(left, '=') + ' ' + title + ' '
	                  + std::string(right, '='))
	          << "\n\n";
}
