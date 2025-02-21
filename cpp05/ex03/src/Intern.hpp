#pragma once

#include "AForm.hpp"
#include "utils/Exception.hpp"
#include <string>

class Intern {
public:
	class UnknownFormException : public utils::Exception {
	public:
		explicit UnknownFormException(const std::string& where = "");
	};

	static const char* forms[];

	static void print_known_forms();

	Intern();
	~Intern();

	AForm* makeForm(const std::string& form, const std::string& target) const;

private:
	enum Form {
		PresidentialPardonForm,
		RobotomyRequestForm,
		ShrubberyCreationForm,
		Unknown
	};

	static void _init_known_forms();
	static std::string& _known_forms(Form form);

	static bool _is_init;

	Intern(const Intern& other);
	Intern& operator=(Intern other);

	Form _which_form(const std::string& input) const;
};
