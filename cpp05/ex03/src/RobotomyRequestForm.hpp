#pragma once

#include "AForm.hpp"
#include <string>

class RobotomyRequestForm : public AForm {
public:
	static const unsigned int grade_to_sign = 72;
	static const unsigned int grade_to_exec = 45;

	explicit RobotomyRequestForm(const std::string& target);
	RobotomyRequestForm(const RobotomyRequestForm& other);
	~RobotomyRequestForm();

	RobotomyRequestForm& operator=(RobotomyRequestForm other) throw();

	void execute(Bureaucrat const& executor) const;

	int score() const;

private:
	RobotomyRequestForm();

	mutable int _score;
};
