#include "RobotomyRequestForm.hpp"
#include "AForm.hpp"
#include "Bureaucrat.hpp"
#include "utils/utils.hpp"
#include <cstddef>
#include <iostream>
#include <string>

RobotomyRequestForm::RobotomyRequestForm(const std::string& target)
    : AForm("RobotomyRequestForm", grade_to_sign, grade_to_exec, target)
{}

RobotomyRequestForm::RobotomyRequestForm(const RobotomyRequestForm& other)
    : AForm(other)
{}

RobotomyRequestForm::~RobotomyRequestForm() {}

RobotomyRequestForm&
RobotomyRequestForm::operator=(const RobotomyRequestForm& other)
{
	AForm::operator=(other);
	return *this;
}

// NOLINTBEGIN(cppcoreguidelines-pro-type-reinterpret-cast)
void RobotomyRequestForm::execute(Bureaucrat const& executor) const
{
	static int successes = 0;

	AForm::execute(executor);
	std::cout << "* DRILLING NOISES *" << '\n';

	size_t random = 0;
	utils::rand(&random, sizeof(random));

	if (random % 2 == 0) {
		std::cout << target() << " has been robotomized successfully" << '\n';
		++successes;
	}
	else {
		std::cout << target() << "'s robotomy failed" << '\n';
		--successes;
	}

	std::cerr << "successes: " << successes << '\n';
}
// NOLINTEND(cppcoreguidelines-pro-type-reinterpret-cast)
