#pragma once

#include "AForm.hpp"
#include "Grade.hpp"
#include <string>

class RobotomyRequestForm : public AForm {
public:
	static const Grade grade_to_sign;
	static const Grade grade_to_exec;

	RobotomyRequestForm(const std::string& target);
	RobotomyRequestForm(const RobotomyRequestForm& other);
	~RobotomyRequestForm();

	RobotomyRequestForm& operator=(const RobotomyRequestForm& other);

	void execute(Bureaucrat const& executor) const;

private:
	RobotomyRequestForm();
};
