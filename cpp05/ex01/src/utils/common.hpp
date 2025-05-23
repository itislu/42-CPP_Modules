#pragma once

#include <cstddef>
#include <fstream>
#include <ios>
#include <string>

#define BOLD(msg)   (std::string("\033[1m") + msg + "\033[0m")
#define RED(msg)    (std::string("\033[31m") + msg + "\033[0m")
#define GREEN(msg)  (std::string("\033[32m") + msg + "\033[0m")
#define YELLOW(msg) (std::string("\033[33m") + msg + "\033[0m")
#define BLUE(msg)   (std::string("\033[34m") + msg + "\033[0m")
#define GRAY(msg)   (std::string("\033[37m") + msg + "\033[0m")

#define WHERE (utils::where(__FILE__, __LINE__, __FUNCTION__))

namespace utils {

std::string where(const char* file, size_t line, const char* function);

template <typename T>
void swap(T& a, T& b) throw()
{
	T tmp = a;
	a = b;
	b = tmp;
}

// NOLINTBEGIN(cppcoreguidelines-pro-type-reinterpret-cast)
template <typename T>
void rand(T* v, std::streamsize size)
{
	std::ifstream urandom;

	urandom.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	urandom.open("/dev/urandom", std::ios::binary);
	urandom.read(reinterpret_cast<char*>(v), size);
	urandom.close();
}
// NOLINTEND(cppcoreguidelines-pro-type-reinterpret-cast)

} // namespace utils
