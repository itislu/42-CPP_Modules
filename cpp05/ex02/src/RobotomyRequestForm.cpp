#include "RobotomyRequestForm.hpp"
#include "AForm.hpp"
#include "Bureaucrat.hpp"
#include "utils/utils.hpp"
#include <cstddef>
#include <iostream>
#include <string>

RobotomyRequestForm::RobotomyRequestForm(const std::string& target)
    : AForm("RobotomyRequestForm", grade_to_sign, grade_to_exec, target),
      _score(0)
{}

RobotomyRequestForm::RobotomyRequestForm(const RobotomyRequestForm& other)
    : AForm(other),
      _score(other._score)
{}

RobotomyRequestForm::~RobotomyRequestForm() {}

RobotomyRequestForm&
RobotomyRequestForm::operator=(const RobotomyRequestForm& other)
{
	AForm::operator=(other);
	utils::swap(_score, other._score);
	return *this;
}

// NOLINTBEGIN(cppcoreguidelines-pro-type-reinterpret-cast)
void RobotomyRequestForm::execute(Bureaucrat const& executor) const
{
	AForm::execute(executor);
	std::cout << "* DRILLING NOISES *" << '\n';

	size_t random = 0;
	utils::rand(&random, sizeof(random));

	if (random % 2 == 0) {
		std::cout << target() << " has been robotomized successfully" << '\n';
		++_score;
	}
	else {
		std::cout << target() << "'s robotomy failed" << '\n';
		--_score;
	}
}
// NOLINTEND(cppcoreguidelines-pro-type-reinterpret-cast)

int RobotomyRequestForm::score() const { return _score; }
