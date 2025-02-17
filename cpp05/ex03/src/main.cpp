// NOLINTBEGIN(readability-magic-numbers)

#include "AForm.hpp"
#include "Intern.hpp"
#include "utils/log.hpp"
#include <string>

int main()
{
	Intern someRandomIntern;
	AForm* rrf;
	rrf = someRandomIntern.makeForm("robotomy request", "Bender");
	rrf = someRandomIntern.makeForm("RobotomyRequestForm", "Bender");
	(void)rrf;

	Intern::print_known_forms();
}

// NOLINTEND(readability-magic-numbers)
