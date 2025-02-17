#pragma once

#include "AForm.hpp"
#include <string>

class PresidentialPardonForm : public AForm {
public:
	static const unsigned int grade_to_sign = 25;
	static const unsigned int grade_to_exec = 5;

	PresidentialPardonForm(const std::string& target);
	PresidentialPardonForm(const PresidentialPardonForm& other);
	~PresidentialPardonForm();

	PresidentialPardonForm& operator=(const PresidentialPardonForm& other);

	void execute(Bureaucrat const& executor) const;

private:
	PresidentialPardonForm();
};
