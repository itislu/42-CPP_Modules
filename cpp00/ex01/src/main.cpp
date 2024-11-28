#include "PhoneBook.hpp"
#include <clocale>
#include <iostream>
#include <string>

int main()
{
	PhoneBook phonebook;
	// Valgrind bug: https://bugs.kde.org/show_bug.cgi?id=397083
	std::wstring input(L"Reserving some space for you, Valgrind");

	setlocale(LC_CTYPE, "");
	while (std::wcin.good()) {
		std::wcout << L"Input a command [ADD, SEARCH, EXIT]: ";
		std::getline(std::wcin, input);
		if (input == L"ADD") {
			phonebook.add();
		}
		else if (input == L"SEARCH") {
			phonebook.search();
		}
		else if (input == L"EXIT") {
			break;
		}
		else if (std::wcin.good()) {
			std::wcout << L"Unknown command.\n";
		}
		std::wcout << '\n';
	}
}
