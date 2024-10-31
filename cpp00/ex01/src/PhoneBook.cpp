#include "PhoneBook.hpp"
#include "utils.hpp"
#include <iomanip>
#include <iostream>
#include <sstream>

const int PhoneBook::MAX_CONTACTS;

PhoneBook::PhoneBook(void) : _contact_count(0), _index_new_contact(0) {}

PhoneBook::~PhoneBook(void) {}

void PhoneBook::add(void)
{
	Contact &contact = this->_contacts[this->_index_new_contact];

	if (!contact.prompt_to_fill()) {
		std::wcout << L"Aborting adding this contact.\n";
	}
	else {
		this->_contact_count =
			std::min(this->_contact_count + 1, PhoneBook::MAX_CONTACTS);
		this->_index_new_contact =
			(this->_index_new_contact + 1) % PhoneBook::MAX_CONTACTS;
		std::wcout << L"Successfully added a new contact.\n";
	}
}

void PhoneBook::search(void)
{
	if (this->_contact_count == 0) {
		std::wcout << L"The phonebook does not have any contacts yet.\n";
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
		Contact::print_delim_middle();
		this->_index(i).print(i);
	}
	Contact::print_delim_bottom();
}

bool PhoneBook::_prompt_index(int &index)
{
	std::wstring input;

	while (true) {
		if (!prompt(L"Index of contact", input)) {
			std::wcout << L"Aborting this search.\n";
			return false;
		}
		std::wistringstream iss(input);
		if (!str_isdigit(input) || !(iss >> index)) {
			std::wcout << L"Please enter a number." << std::endl;
		}
		else if (index >= this->_contact_count) {
			if (this->_contact_count == 1) {
				std::wcout << L"Index out of range. There is only "
						   << this->_contact_count << L" contact so far!"
						   << std::endl;
			}
			else {
				std::wcout << L"Index out of range. There are only "
						   << this->_contact_count << L" contacts so far!"
						   << std::endl;
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
