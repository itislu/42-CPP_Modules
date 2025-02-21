#pragma once

#include "AForm.hpp"
#include <string>

class ShrubberyCreationForm : public AForm {
public:
	static const unsigned int grade_to_sign = 145;
	static const unsigned int grade_to_exec = 137;

	ShrubberyCreationForm(const std::string& target);
	ShrubberyCreationForm(const ShrubberyCreationForm& other);
	~ShrubberyCreationForm();

	ShrubberyCreationForm& operator=(ShrubberyCreationForm other) throw();

	void execute(Bureaucrat const& executor) const;

private:
	ShrubberyCreationForm();
};
