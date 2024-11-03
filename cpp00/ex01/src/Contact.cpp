#include "Contact.hpp"
#include "utils.hpp"
#include <cstdio>
#include <iomanip>
#include <iostream>
#include <string>
#include <wchar.h>

bool Contact::prompt_to_fill()
{
	return prompt(L"First name", this->_first_name)
		   && prompt(L"Last name", this->_last_name)
		   && prompt(L"Nickname", this->_nickname)
		   && prompt(L"Phone number", this->_phone_number)
		   && prompt(L"Darkest secret", this->_darkest_secret);
}

void Contact::print_preview(int index) const
{
	std::wcout << L"┝" << std::setw(Contact::display_width) << index << L"│"
			   << Contact::_get_printable_str(this->_first_name) << L"│"
			   << Contact::_get_printable_str(this->_last_name) << L"│"
			   << Contact::_get_printable_str(this->_nickname) << L"│\n";
}

void Contact::print_full() const
{
	static const int max_key_width = 18;

	std::wcout << std::setw(max_key_width) << L"First name: "
			   << this->_first_name << L'\n';
	std::wcout << std::setw(max_key_width) << L"Last name: " << this->_last_name
			   << L'\n';
	std::wcout << std::setw(max_key_width) << L"Nickname: " << this->_nickname
			   << L'\n';
	std::wcout << std::setw(max_key_width) << L"Phone number: "
			   << this->_phone_number << L'\n';
	std::wcout << std::setw(max_key_width) << L"Darkest secret: "
			   << this->_darkest_secret << L'\n';
}

void Contact::print_header()
{
	Contact::print_delim_top();
	std::wcout << L"┝" << std::setw(Contact::display_width) << L"INDEX" << L"│"
			   << std::setw(Contact::display_width) << L"FIRST NAME" << L"│"
			   << std::setw(Contact::display_width) << L"LAST NAME" << L"│"
			   << std::setw(Contact::display_width) << L"NICKNAME" << L"│\n";
}

void Contact::print_delim_top()
{
	std::wcout << L"╭" << std::setfill(L'─')
			   << std::setw(Contact::display_width + 1) << L"┬"
			   << std::setw(Contact::display_width + 1) << L"┬"
			   << std::setw(Contact::display_width + 1) << L"┬"
			   << std::setw(Contact::display_width + 1) << L"╮" << L'\n'
			   << std::setfill(L' ');
}

void Contact::print_delim_middle()
{
	std::wcout << L"├" << std::setfill(L'─')
			   << std::setw(Contact::display_width + 1) << L"┼"
			   << std::setw(Contact::display_width + 1) << L"┼"
			   << std::setw(Contact::display_width + 1) << L"┼"
			   << std::setw(Contact::display_width + 1) << L"┤" << L'\n'
			   << std::setfill(L' ');
}

void Contact::print_delim_bottom()
{
	std::wcout << L"╰" << std::setfill(L'─')
			   << std::setw(Contact::display_width + 1) << L"┴"
			   << std::setw(Contact::display_width + 1) << L"┴"
			   << std::setw(Contact::display_width + 1) << L"┴"
			   << std::setw(Contact::display_width + 1) << L"╯" << L'\n'
			   << std::setfill(L' ');
}

std::wstring Contact::_get_printable_str(const std::wstring& str)
{
	std::wstring result;
	int width = 0;

	for (std::wstring::const_iterator it = str.begin(); it != str.end(); ++it) {
		int w = wcwidth(*it);
		if (w < 0) {
			continue;
		}
		if (width + w > Contact::display_width
			|| (width + w == Contact::display_width && it + 1 != str.end())) {
			result.push_back(L'.');
			width++;
			break;
		}
		result.push_back(*it);
		width += w;
	}

	while (width < Contact::display_width) {
		result.insert(0, L" ");
		width++;
	}
	return result;
}
