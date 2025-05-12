#include "Slow.hpp"
#include "libftpp/format.hpp"
#include <cstddef>
#include <iostream>

Slow::Slow() { std::cerr << ft::log::info("Default constructor") << '\n'; }

Slow::Slow(std::size_t size, char c)
    : _str(size, c)
{
	std::cerr << ft::log::info("Constructor(") << size << ", '" << c << "')"
	          << '\n';
}

Slow::Slow(const Slow& other)
    : _str(other._str)
{
	std::cerr << ft::log::info("Copy constructor") << '\n';
}

Slow& Slow::operator=(const Slow& other)
{
	std::cerr << ft::log::info("Copy assignment operator") << '\n';
	if (&other == this) {
		return *this;
	}
	_str = other._str;
	return *this;
}

Slow::~Slow() { std::cerr << ft::log::info("Destructor") << '\n'; }
