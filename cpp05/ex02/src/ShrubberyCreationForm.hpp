#pragma once

#include "AForm.hpp"
#include "Grade.hpp"
#include <string>

class ShrubberyCreationForm : public AForm {
public:
	static const Grade grade_to_sign;
	static const Grade grade_to_exec;

	ShrubberyCreationForm(const std::string& target);
	ShrubberyCreationForm(const ShrubberyCreationForm& other);
	~ShrubberyCreationForm();

	ShrubberyCreationForm& operator=(const ShrubberyCreationForm& other);

	void execute(Bureaucrat const& executor) const;

private:
	ShrubberyCreationForm();
};
