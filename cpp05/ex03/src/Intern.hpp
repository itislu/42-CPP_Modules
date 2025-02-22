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
	enum FormType {
		PresidentialPardonForm,
		RobotomyRequestForm,
		ShrubberyCreationForm,
		Unknown
	};

	static AForm* _makePresidentialPardonForm(const std::string& target);
	static AForm* _makeRobotomyRequestForm(const std::string& target);
	static AForm* _makeShrubberyCreationForm(const std::string& target);
	static bool _iter_form_types(FormType& it);
	static void _init_known_forms();
	static std::string& _known_forms(FormType form);
	static FormType _which_form(const std::string& input);

	static AForm* (*const _factory[])(const std::string&);
	static bool _is_init;

	Intern(const Intern& other);
	Intern& operator=(Intern other);
};
