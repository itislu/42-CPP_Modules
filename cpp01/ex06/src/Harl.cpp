// NOLINTBEGIN(cppcoreguidelines-pro-bounds-constant-array-index)

#include "Harl.hpp"
#include <iostream>
#include <string>

const std::string Harl::_levels[Harl::_num_levels] = {"DEBUG",
													  "INFO",
													  "WARNING",
													  "ERROR"};

void Harl::complain(std::string level) // NOLINT
{
	switch (Harl::_index(level)) {
	case Harl::DEBUG:
		Harl::_debug();
	case Harl::INFO:
		Harl::_info();
	case Harl::WARNING:
		Harl::_warning();
	case Harl::ERROR:
		Harl::_error();
		break;
	default:
		std::cout << "I cannot complain about THAT..." << '\n';
	}
}

Harl::Level Harl::_index(const std::string& level)
{
	for (int i = 0; i < Harl::_num_levels; ++i) {
		if (level == Harl::_levels[i]) {
			return Harl::Level(i);
		}
	}
	return Harl::UNKNOWN;
}

void Harl::_debug()
{
	std::cout << "[ DEBUG ]\n"
			  << "🚧🚧🚧🚧🚧" << "\n\n";
}

void Harl::_info()
{
	std::cout << "[ INFO ]\n"
			  << "📣📣📣📣📣" << "\n\n";
}
void Harl::_warning()
{
	std::cout << "[ WARNING ]\n"
			  << "❗❗❗❗❗" << "\n\n";
}

void Harl::_error()
{
	std::cout << "[ ERROR ]\n"
			  << "🚨🚨🚨🚨🚨" << "\n\n";
}

// NOLINTEND(cppcoreguidelines-pro-bounds-constant-array-index)
