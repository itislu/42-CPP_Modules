#pragma once

#include "AForm.hpp"
#include "Grade.hpp"
#include <string>

class PresidentialPardonForm : public AForm {
public:
	static const Grade grade_to_sign;
	static const Grade grade_to_exec;

	PresidentialPardonForm(const std::string& target);
	PresidentialPardonForm(const PresidentialPardonForm& other);
	~PresidentialPardonForm();

	PresidentialPardonForm& operator=(const PresidentialPardonForm& other);

	void execute(Bureaucrat const& executor) const;

private:
	PresidentialPardonForm();
};
