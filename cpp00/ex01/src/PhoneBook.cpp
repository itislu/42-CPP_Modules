#include "PhoneBook.hpp"
#include "utils.hpp"
#include <iomanip>
#include <iostream>
#include <sstream>

PhoneBook::PhoneBook() : _contact_count(0), _index_new_contact(0)
{
	std::cout << "constructor\n";
}

PhoneBook::~PhoneBook()
{
	std::cout << "destructor\n";
}

void PhoneBook::add(void)
{
	Contact &contact = this->_contacts[this->_index_new_contact];

	if (!contact.prompt_to_fill()) {
		std::cout << "Aborting adding this contact." << std::endl;
	}
	else {
		this->_contact_count = std::min(this->_contact_count + 1, MAX_CONTACTS);
		this->_index_new_contact =
			(this->_index_new_contact + 1) % MAX_CONTACTS;
		std::cout << "Successfully added a new contact." << std::endl;
	}
}

void PhoneBook::search(void)
{
	if (this->_contact_count == 0) {
		std::cout << "The phonebook does not have any contacts yet.\n";
		return;
	}
	this->_print_contacts();

	std::string input;
	int index;
	while (true) {
		if (!prompt("Index of contact", input)) {
			std::cout << "Aborting this search." << std::endl;
			return;
		}
		std::istringstream iss(input);
		if (!str_isdigit(input) || !(iss >> index)) {
			std::cout << "Please enter a number.\n";
		}
		else if (index >= this->_contact_count) {
			std::cout << "Index out of range. There are only "
					  << this->_contact_count << " contacts so far!\n";
		}
		else {
			break;
		}
	}
	this->_index(index).print_full();
}

void PhoneBook::_print_contacts(void)
{
	Contact::print_header();

	for (int i = 0; i < this->_contact_count; ++i) {
		this->_index(i).print(i);
		Contact::print_delim();
	}
}

Contact &PhoneBook::_index(int i)
{
	int index = (i + this->_index_new_contact) % this->_contact_count;
	return this->_contacts[index];
}
