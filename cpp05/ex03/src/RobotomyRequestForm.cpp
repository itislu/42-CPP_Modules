#include "RobotomyRequestForm.hpp"
#include "AForm.hpp"
#include "Bureaucrat.hpp"
#include "utils/common.hpp"
#include <cstdlib>
#include <iostream>
#include <string>

RobotomyRequestForm::RobotomyRequestForm(const std::string& target)
    : AForm("RobotomyRequestForm", grade_to_sign, grade_to_exec, target),
      _score(0)
{
	unsigned int seed = 0;
	utils::rand(&seed, sizeof(seed));
	srand(seed);
}

RobotomyRequestForm::RobotomyRequestForm(const RobotomyRequestForm& other)
    : AForm(other),
      _score(other._score)
{}

RobotomyRequestForm::~RobotomyRequestForm() {}

RobotomyRequestForm&
RobotomyRequestForm::operator=(RobotomyRequestForm other) throw()
{
	swap(other);
	utils::swap(_score, other._score);
	return *this;
}

void RobotomyRequestForm::execute(Bureaucrat const& executor) const
{
	AForm::execute(executor);
	std::cout << "* DRILLING NOISES *" << '\n';

	if (rand() % 2 == 0) {
		std::cout << target() << " has been robotomized successfully" << '\n';
		++_score;
	}
	else {
		std::cout << target() << "'s robotomy failed" << '\n';
		--_score;
	}
}

int RobotomyRequestForm::score() const { return _score; }
