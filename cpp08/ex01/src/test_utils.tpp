#pragma once

#include "Span.hpp"
#include "libftpp/format.hpp"
#include "libftpp/string.hpp"
#include "test_utils.hpp"
#include <cstdlib>
#include <iostream>
#include <limits>
#include <stdexcept>
#include <string>

template <typename InputIt>
void print_addNumber(Span& sp, const InputIt& first, const InputIt& last)
{
	const std::string amount_str =
	    ft::to_string(std::labs(std::distance(first, last)));
	const std::string max_str = ft::to_string(std::numeric_limits<int>::min());
	std::cerr << GRAY(
	    amount_str + " numbers "
	    + std::string(3 + max_str.length() - amount_str.length(), '.') + " ");

	try {
		sp.addNumber(first, last);
		std::cerr << GRAY("added") << '\n';
	}
	catch (const std::runtime_error& e) {
		std::cerr << GRAY("failed") << '\n';
		std::cerr << ft::log::error(e.what()) << '\n';
	}
}
