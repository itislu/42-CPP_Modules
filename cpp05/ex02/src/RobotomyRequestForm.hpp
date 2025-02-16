#pragma once

#include "AForm.hpp"
#include <string>

class RobotomyRequestForm : public AForm {
public:
	static const unsigned int grade_to_sign = 72;
	static const unsigned int grade_to_exec = 45;

	RobotomyRequestForm(const std::string& target);
	RobotomyRequestForm(const RobotomyRequestForm& other);
	~RobotomyRequestForm();

	RobotomyRequestForm& operator=(const RobotomyRequestForm& other);

	void execute(Bureaucrat const& executor) const;

private:
	RobotomyRequestForm();
};
