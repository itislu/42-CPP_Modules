#include "PhoneBook.hpp"
#include <iostream>
#include <string>

int main(void)
{
	PhoneBook phonebook;
	std::string input;

	while (true) {
		std::cout << "Input a command: ";
		if (!std::getline(std::cin, input)) {
			break;
		}
		if (input == "ADD") {
			phonebook.add();
		}
		else if (input == "SEARCH") {
			phonebook.search();
		}
		else if (input == "EXIT") {
			break;
		}
		else {
			std::cout << "Unknown command." << "\n";
		}
		std::cout << std::endl;
	}
}
