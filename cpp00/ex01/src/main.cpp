#include "PhoneBook.hpp"
#include <iostream>
#include <string>

int main(void)
{
	PhoneBook phonebook;
	std::wstring input;

	while (true) {
		std::cout << "Input a command [ADD, SEARCH, EXIT]: ";
		if (!std::getline(std::wcin, input)) {
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
			std::cout << "Unknown command." << "\n";
		}
		std::cout << std::endl;
	}
}
