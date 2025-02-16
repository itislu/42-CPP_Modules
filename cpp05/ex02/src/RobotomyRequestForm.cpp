#include "RobotomyRequestForm.hpp"
#include "AForm.hpp"
#include "Bureaucrat.hpp"
#include <cstddef>
#include <fstream>
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

void RobotomyRequestForm::execute(Bureaucrat const& executor) const
{
	static int successes = 0;

	std::ifstream file;
	size_t random = 0;
	char* ptr = reinterpret_cast<char*>(&random);

	AForm::execute(executor);
	std::cout << "* DRILLING NOISES *" << '\n';
	file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	file.open("/dev/urandom");
	file.read(ptr, sizeof(random));
	file.close();
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
