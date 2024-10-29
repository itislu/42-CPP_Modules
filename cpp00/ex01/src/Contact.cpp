#include "Contact.hpp"
#include "utils.hpp"
#include <cstdio>
#include <iomanip>
#include <iostream>

static std::string get_printable_str(std::string &str);

bool Contact::prompt_to_fill(void)
{
	if (!prompt("First name", this->first_name)
		|| !prompt("Last name", this->last_name)
		|| !prompt("Nickname", this->nickname)
		|| !prompt("Phone number", this->phone_number)
		|| !prompt("Darkest secret", this->darkest_secret)) {
		return false;
	}
	return true;
}

void Contact::print(int index)
{
	std::cout << "|" << std::setw(10) << index << "|" << std::setw(10)
			  << get_printable_str(this->first_name) << "|" << std::setw(10)
			  << get_printable_str(this->last_name) << "|" << std::setw(10)
			  << get_printable_str(this->nickname) << "|\n";
}

static std::string get_printable_str(std::string &str)
{
	if (str.length() > 10) {
		return str.substr(0, 9) + ".";
	}
	else {
		return str;
	}
}

void Contact::print_full(void)
{
	std::cout << "First name: " << this->first_name << "\n";
	std::cout << "Last name: " << this->last_name << "\n";
	std::cout << "Nickname: " << this->nickname << "\n";
	std::cout << "Phone number: " << this->phone_number << "\n";
	std::cout << "Darkest secret: " << this->darkest_secret << "\n";
}

void Contact::print_header(void)
{
	Contact::print_delim();
	std::cout << "|" << std::setw(10) << "INDEX"
			  << "|" << std::setw(10) << "FIRST NAME"
			  << "|" << std::setw(10) << "LAST NAME"
			  << "|" << std::setw(10) << "NICKNAME"
			  << "|\n";
	Contact::print_delim();
}

void Contact::print_delim(void)
{
	std::cout << "+" << std::setfill('-') << std::setw(11) << "+"
			  << std::setw(11) << "+" << std::setw(11) << "+" << std::setw(11)
			  << "+" << "\n"
			  << std::setfill(' ');
}
