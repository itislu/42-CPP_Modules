#include "Slow.hpp"
#include "libftpp/log.hpp"
#include <cstddef>
#include <iostream>

std::size_t Slow::string_init_size = 1024LU * 1024; // 1 MiB

Slow::Slow()
    : _str(string_init_size, 'A')
{
	std::cerr << ft::log::info("Default constructor") << '\n';
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
