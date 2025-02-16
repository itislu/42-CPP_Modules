#include "PresidentialPardonForm.hpp"
#include "AForm.hpp"
#include "Bureaucrat.hpp"
#include "Grade.hpp"
#include <iostream>
#include <string>

const Grade PresidentialPardonForm::grade_to_sign(25);
const Grade PresidentialPardonForm::grade_to_exec(5);

PresidentialPardonForm::PresidentialPardonForm(const std::string& target)
    : AForm("PresidentialPardonForm",
            grade_to_sign.get(),
            grade_to_exec.get(),
            target)
{}

PresidentialPardonForm::PresidentialPardonForm(
    const PresidentialPardonForm& other)
    : AForm(other)
{}

PresidentialPardonForm::~PresidentialPardonForm() {}

PresidentialPardonForm&
PresidentialPardonForm::operator=(const PresidentialPardonForm& other)
{
	AForm::operator=(other);
	return *this;
}

void PresidentialPardonForm::execute(Bureaucrat const& executor) const
{
	AForm::execute(executor);
	std::cout << target() << " has been pardoned by Zaphod Beeblebrox" << '\n';
}
