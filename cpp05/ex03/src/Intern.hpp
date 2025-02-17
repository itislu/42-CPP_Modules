#pragma once

#include "AForm.hpp"
#include "utils/Exception.hpp"
#include <string>

class Intern {
public:
	class UnknownFormException : public utils::Exception {
	public:
		UnknownFormException(const std::string& form,
		                     const std::string& where = "");
	};

	static const std::string forms[];

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

	static std::string _known_forms[];
	static bool _is_init;

	static void _init_known_forms();

	Intern(const Intern& other);
	Intern& operator=(const Intern& other);

	Form _which_form(const std::string& input) const;
};
