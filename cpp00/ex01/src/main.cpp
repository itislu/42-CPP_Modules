#include "PhoneBook.hpp"
#include <iostream>
#include <string>

int main(void)
{
	PhoneBook phonebook;
	std::wstring input;

	setlocale(LC_CTYPE, "");
	while (true) {
		std::wcout << L"Input a command [ADD, SEARCH, EXIT]: ";
		if (!std::getline(std::wcin, input)) {
			std::wcout << std::endl;
			break;
		}
		if (input == L"ADD") {
			phonebook.add();
		}
		else if (input == L"SEARCH") {
			phonebook.search();
		}
		else if (input == L"EXIT") {
			break;
		}
		else {
			std::wcout << L"Unknown command.\n";
		}
		std::wcout << std::endl;
	}
}
