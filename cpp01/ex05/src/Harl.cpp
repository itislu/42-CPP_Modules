// NOLINTBEGIN(cppcoreguidelines-pro-bounds-constant-array-index)

#include "Harl.hpp"
#include <cstddef>
#include <iostream>
#include <string>

const std::string Harl::_levels[Harl::_num_levels] = {"DEBUG",
													  "INFO",
													  "WARNING",
													  "ERROR"};
void (*Harl::_complaints[Harl::_num_levels])();
size_t Harl::_max_len;
std::string Harl::_lookup;

Harl::Harl()
{
	Harl::_complaints[0] = &Harl::debug;
	Harl::_complaints[1] = &Harl::info;
	Harl::_complaints[2] = &Harl::warning;
	Harl::_complaints[3] = &Harl::error;
	Harl::_max_len = 0;
	for (int i = 0; i < Harl::_num_levels; ++i) {
		if (Harl::_levels[i].length() > Harl::_max_len) {
			Harl::_max_len = Harl::_levels[i].length();
		}
	}
	for (int i = 0; i < Harl::_num_levels; ++i) {
		std::string padded = Harl::_levels[i];
		padded.resize(Harl::_max_len, ' ');
		Harl::_lookup += padded;
	}
}

void Harl::complain(std::string level) // NOLINT
{
	size_t index = Harl::_index(level);

	if (index != std::string::npos) {
		Harl::_complaints[index]();
	}
	else {
		std::cout << "I cannot complain about THAT thing..." << '\n';
	}
}

size_t Harl::_index(const std::string& level)
{
	size_t index =
		level.empty() ? std::string::npos : Harl::_lookup.find(level);

	return index == std::string::npos ? std::string::npos
									  : index / Harl::_max_len;
}

void Harl::debug()
{
	std::cout << "DEBUG" << '\n';
}

void Harl::info()
{
	std::cout << "INFO" << '\n';
}
void Harl::warning()
{
	std::cout << "WARNING" << '\n';
}

void Harl::error()
{
	std::cout << "ERROR" << '\n';
}

// NOLINTEND(cppcoreguidelines-pro-bounds-constant-array-index)
