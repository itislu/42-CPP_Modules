#include "Contact.hpp"
#include "utils.hpp"
#include <cstdio>
#include <iomanip>
#include <iostream>

bool Contact::prompt_to_fill(void)
{
	if (!prompt(L"First name", this->_first_name)
		|| !prompt(L"Last name", this->_last_name)
		|| !prompt(L"Nickname", this->_nickname)
		|| !prompt(L"Phone number", this->_phone_number)
		|| !prompt(L"Darkest secret", this->_darkest_secret)) {
		return false;
	}
	return true;
}

void Contact::print_preview(const int index) const
{
	std::wcout << L"┝" << std::setw(Contact::DISPLAY_WIDTH) << index << L"│"
			   << Contact::_get_printable_str(this->_first_name) << L"│"
			   << Contact::_get_printable_str(this->_last_name) << L"│"
			   << Contact::_get_printable_str(this->_nickname) << L"│\n";
}

void Contact::print_full(void) const
{
	std::wcout << std::setw(18) << L"First name: " << this->_first_name
			   << L"\n";
	std::wcout << std::setw(18) << L"Last name: " << this->_last_name << L"\n";
	std::wcout << std::setw(18) << L"Nickname: " << this->_nickname << L"\n";
	std::wcout << std::setw(18) << L"Phone number: " << this->_phone_number
			   << L"\n";
	std::wcout << std::setw(18) << L"Darkest secret: " << this->_darkest_secret
			   << L"\n";
}

void Contact::print_header(void)
{
	Contact::print_delim_top();
	std::wcout << L"┝" << std::setw(Contact::DISPLAY_WIDTH) << L"INDEX" << L"│"
			   << std::setw(Contact::DISPLAY_WIDTH) << L"FIRST NAME" << L"│"
			   << std::setw(Contact::DISPLAY_WIDTH) << L"LAST NAME" << L"│"
			   << std::setw(Contact::DISPLAY_WIDTH) << L"NICKNAME" << L"│\n";
}

void Contact::print_delim_top(void)
{
	std::wcout << L"╭" << std::setfill(L'─')
			   << std::setw(Contact::DISPLAY_WIDTH + 1) << L"┬"
			   << std::setw(Contact::DISPLAY_WIDTH + 1) << L"┬"
			   << std::setw(Contact::DISPLAY_WIDTH + 1) << L"┬"
			   << std::setw(Contact::DISPLAY_WIDTH + 1) << L"╮" << L"\n"
			   << std::setfill(L' ');
}

void Contact::print_delim_middle(void)
{
	std::wcout << L"├" << std::setfill(L'─')
			   << std::setw(Contact::DISPLAY_WIDTH + 1) << L"┼"
			   << std::setw(Contact::DISPLAY_WIDTH + 1) << L"┼"
			   << std::setw(Contact::DISPLAY_WIDTH + 1) << L"┼"
			   << std::setw(Contact::DISPLAY_WIDTH + 1) << L"┤" << L"\n"
			   << std::setfill(L' ');
}

void Contact::print_delim_bottom(void)
{
	std::wcout << L"╰" << std::setfill(L'─')
			   << std::setw(Contact::DISPLAY_WIDTH + 1) << L"┴"
			   << std::setw(Contact::DISPLAY_WIDTH + 1) << L"┴"
			   << std::setw(Contact::DISPLAY_WIDTH + 1) << L"┴"
			   << std::setw(Contact::DISPLAY_WIDTH + 1) << L"╯" << L"\n"
			   << std::setfill(L' ');
}

std::wstring Contact::_get_printable_str(const std::wstring &str)
{
	std::wstring result;
	int width = 0;

	for (std::wstring::const_iterator it = str.begin(); it != str.end(); ++it) {
		int w = wcwidth(*it);
		if (w < 0) {
			continue;
		}
		if (width + w > Contact::DISPLAY_WIDTH
			|| (width + w == Contact::DISPLAY_WIDTH && it + 1 != str.end())) {
			result.push_back(L'.');
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
