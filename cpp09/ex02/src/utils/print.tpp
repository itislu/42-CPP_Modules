#pragma once

#include "utils.hpp"
#include <algorithm>
#include <iostream>
#include <iterator>
#include <string>

template <typename C>
void print_container(const C& container, const std::string& prefix)
{
	std::cout << prefix;
	std::copy(container.begin(),
	          container.end(),
	          std::ostream_iterator<typename C::value_type>(std::cout, " "));
	std::cout << '\n';
}
