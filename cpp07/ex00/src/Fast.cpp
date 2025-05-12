#include "Fast.hpp"
#include "Slow.hpp"
#include "libftpp/format.hpp"
#include <cstddef>
#include <iostream>

Fast::Fast() {}

Fast::Fast(std::size_t size, char c)
    : Slow(size, c)
{}

Fast::Fast(const Fast& other)
    : Slow(other)
{}

Fast& Fast::operator=(const Fast& other)
{
	static_cast<Slow>(*this) = other;
	return *this;
}

Fast::~Fast() {}

void Fast::swap(Fast& other)
{
	std::cerr << ft::log::info("swap") << '\n';
	_str.swap(other._str);
}
