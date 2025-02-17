// NOLINTBEGIN(readability-magic-numbers)

#include "AForm.hpp"
#include "Intern.hpp"
#include "utils/log.hpp"
#include <cstddef>
#include <string>

int main()
{
	const Intern someRandomIntern;
	Intern::print_known_forms();

	AForm* form = NULL;
	form = someRandomIntern.makeForm("robotomy request", "Bender");
	delete form;
	form = someRandomIntern.makeForm("RobotomyRequestForm", "Bender");
	delete form;
	form = someRandomIntern.makeForm("shrubbery creation form", "Bender");
	delete form;
	form = someRandomIntern.makeForm("shrubbery creation", "Bender");
	delete form;
	form = someRandomIntern.makeForm("Shrubbery creation form", "Bender");
	delete form;
	form = someRandomIntern.makeForm("Presidential Pardon Form", "Bender");
	delete form;
	form = someRandomIntern.makeForm("", "Bender");
	delete form;
}

// NOLINTEND(readability-magic-numbers)
