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

	AForm* r = NULL;
	r = someRandomIntern.makeForm("robotomy request", "Bender");
	delete r;
	r = someRandomIntern.makeForm("RobotomyRequestForm", "Bender");
	delete r;
	r = someRandomIntern.makeForm("", "Bender");
	delete r;
}

// NOLINTEND(readability-magic-numbers)
