#include "Contact.hpp"
#include "utils.hpp"
#include <cstdio>
#include <iomanip>
#include <iostream>

bool Contact::prompt_to_fill(void)
{
	if (!prompt("First name", this->first_name)
		|| !prompt("Last name", this->last_name)
		|| !prompt("Nickname", this->nickname)
		|| !prompt("Phone number", this->phone_number)
		|| !prompt("Darkest secret", this->darkest_secret)) {
		return false;
	}
	return true;
}

void Contact::print(int index)
{
	std::wcout << "|" << std::setw(DISPLAY_WIDTH) << index << "|"
			   << Contact::_get_printable_str(this->first_name) << "|"
			   << Contact::_get_printable_str(this->last_name) << "|"
			   << Contact::_get_printable_str(this->nickname) << "|\n";
}

void Contact::print_full(void)
{
	std::wcout << "First name: " << this->first_name << "\n";
	std::wcout << "Last name: " << this->last_name << "\n";
	std::wcout << "Nickname: " << this->nickname << "\n";
	std::wcout << "Phone number: " << this->phone_number << "\n";
	std::wcout << "Darkest secret: " << this->darkest_secret << "\n";
}

void Contact::print_header(void)
{
	Contact::print_delim();
	std::wcout << "|" << std::setw(DISPLAY_WIDTH) << "INDEX"
			   << "|" << std::setw(DISPLAY_WIDTH) << "FIRST NAME"
			   << "|" << std::setw(DISPLAY_WIDTH) << "LAST NAME"
			   << "|" << std::setw(DISPLAY_WIDTH) << "NICKNAME"
			   << "|\n";
	Contact::print_delim();
}

void Contact::print_delim(void)
{
	std::wcout << "+" << std::setfill(L'-') << std::setw(DISPLAY_WIDTH + 1)
			   << "+" << std::setw(DISPLAY_WIDTH + 1) << "+"
			   << std::setw(DISPLAY_WIDTH + 1) << "+"
			   << std::setw(DISPLAY_WIDTH + 1) << "+" << "\n"
			   << std::setfill(L' ');
}

std::wstring Contact::_get_printable_str(std::wstring &str)
{
	std::wstring result;
	int width = 0;

	for (std::wstring::iterator it = str.begin(); it != str.end(); ++it) {
		int w = wcwidth(*it);
		if (w < 0) {
			continue;
		}
		if (width + w > Contact::DISPLAY_WIDTH
			|| (width + w == Contact::DISPLAY_WIDTH && it + 1 != str.end())) {
			result.push_back('.');
			width++;
			break;
		}
		result.push_back(*it);
		width += w;
	}

	while (width < Contact::DISPLAY_WIDTH) {
		result.insert(0, L" ");
		width++;
	}
	return result;
}
