#include "PhoneBook.hpp"
#include "utils.hpp"
#include <iomanip>
#include <iostream>
#include <sstream>

const int PhoneBook::MAX_CONTACTS;

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
		this->_contact_count =
			std::min(this->_contact_count + 1, PhoneBook::MAX_CONTACTS);
		this->_index_new_contact =
			(this->_index_new_contact + 1) % PhoneBook::MAX_CONTACTS;
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

	int index;
	if (!this->_prompt_index(index)) {
		return;
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

bool PhoneBook::_prompt_index(int &index)
{
	std::string input;

	while (true) {
		if (!prompt("Index of contact", input)) {
			std::cout << "Aborting this search." << std::endl;
			return false;
		}
		std::istringstream iss(input);
		if (!str_isdigit(input) || !(iss >> index)) {
			std::cout << "Please enter a number.\n";
		}
		else if (index >= this->_contact_count) {
			if (this->_contact_count == 1) {
				std::cout << "Index out of range. There is only "
						  << this->_contact_count << " contact so far!\n";
			}
			else {
				std::cout << "Index out of range. There are only "
						  << this->_contact_count << " contacts so far!\n";
			}
		}
		else {
			return true;
		}
	}
}

Contact &PhoneBook::_index(int i)
{
	int index = (i + this->_index_new_contact) % this->_contact_count;
	return this->_contacts[index];
}
