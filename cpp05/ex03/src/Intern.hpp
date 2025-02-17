#pragma once

#include "AForm.hpp"
#include <string>

class Intern {
public:
	static const std::string forms[];

	static AForm* makeForm(const std::string& form, const std::string& target);
	static void print_known_forms();

	Intern();
	~Intern();

private:
	static std::string _known_forms;

	Intern(const Intern& other);
	Intern& operator=(const Intern& other);

	static bool _is_known_form(const std::string& input);
	static void _init_known_forms();
};
