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

Harl::Harl()
{
	Harl::_complaints[0] = &Harl::_debug;
	Harl::_complaints[1] = &Harl::_info;
	Harl::_complaints[2] = &Harl::_warning;
	Harl::_complaints[3] = &Harl::_error;
}

void Harl::complain(std::string level) // NOLINT
{
	size_t index = Harl::_index(level);

	if (index != std::string::npos) {
		Harl::_complaints[index]();
	}
	else {
		std::cout << "\nI cannot complain about THAT..." << "\n\n";
	}
}

size_t Harl::_index(const std::string& level)
{
	for (int i = 0; i < Harl::_num_levels; ++i) {
		if (level == Harl::_levels[i]) {
			return i;
		}
	}
	return std::string::npos;
}

void Harl::_debug()
{
	std::cout << "\n[ DEBUG ]\n"
			  << "🚧🚧🚧🚧🚧" << "\n\n";
}

void Harl::_info()
{
	std::cout << "\n[ INFO ]\n"
			  << "📣📣📣📣📣" << "\n\n";
}
void Harl::_warning()
{
	std::cout << "\n[ WARNING ]\n"
			  << "❗❗❗❗❗" << "\n\n";
}

void Harl::_error()
{
	std::cout << "\n[ ERROR ]\n"
			  << "🚨🚨🚨🚨🚨" << "\n\n";
}

// NOLINTEND(cppcoreguidelines-pro-bounds-constant-array-index)
