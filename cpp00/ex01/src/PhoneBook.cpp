// NOLINTBEGIN(cppcoreguidelines-pro-bounds-constant-array-index)

#include "PhoneBook.hpp"
#include "Contact.hpp"
#include "utils.hpp"
#include <iostream>
#include <sstream>
#include <string>

const int PhoneBook::max_contacts;

PhoneBook::PhoneBook() : _contact_count(0), _index_new_contact(0) {}

void PhoneBook::add()
{
	Contact& contact = this->_contacts[this->_index_new_contact];

	if (!contact.prompt_to_fill()) {
		std::wcout << L"Aborting adding this contact.\n";
		return;
	}
	this->_contact_count = this->_contact_count + 1 < PhoneBook::max_contacts
							   ? this->_contact_count + 1
							   : PhoneBook::max_contacts;
	this->_index_new_contact =
		(this->_index_new_contact + 1) % PhoneBook::max_contacts;
	std::wcout << L"Successfully added a new contact.\n";
}

void PhoneBook::search()
{
	if (this->_contact_count == 0) {
		std::wcout << L"The phonebook does not have any contacts yet.\n";
		return;
	}
	this->_print_contacts();

	int index = 0;
	if (!this->_prompt_index(index)) {
		std::wcout << L"Aborting this search.\n";
		return;
	}
	this->_index(index).print_full();
}

void PhoneBook::_print_contacts()
{
	Contact::print_header();

	for (int i = 0; i < this->_contact_count; ++i) {
		Contact::print_delim_middle();
		this->_index(i).print_preview(i);
	}
	Contact::print_delim_bottom();
}

bool PhoneBook::_prompt_index(int& index) const
{
	std::wstring input;

	while (true) {
		if (!prompt(L"Index of contact", input)) {
			return false;
		}
		std::wistringstream iss(input);
		if (!str_isdigit(input) || !(iss >> index)) {
			std::wcout << L"Please enter a number." << '\n';
		}
		else if (index >= this->_contact_count) {
			if (this->_contact_count == 1) {
				std::wcout << L"Index out of range. There is only "
						   << this->_contact_count << L" contact so far!"
						   << '\n';
			}
			else {
				std::wcout << L"Index out of range. There are only "
						   << this->_contact_count << L" contacts so far!"
						   << '\n';
			}
		}
		else {
			return true;
		}
	}
}

Contact& PhoneBook::_index(int i)
{
	const int index = (i + this->_index_new_contact) % this->_contact_count;
	return this->_contacts[index];
}

// NOLINTEND(cppcoreguidelines-pro-bounds-constant-array-index)
