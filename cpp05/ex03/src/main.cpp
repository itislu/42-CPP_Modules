// NOLINTBEGIN(readability-magic-numbers)

#include "AForm.hpp"
#include "Bureaucrat.hpp"
#include "Intern.hpp"
#include "utils/log.hpp"
#include <exception>
#include <iostream>
#include <string>

int main()
{
	int test = 0;
	const Intern someRandomIntern;

	std::cout << "\n---------------- " << ++test << " ----------------" << '\n';
	Intern::print_known_forms();

	std::cout << "\n---------------- " << ++test << " ----------------" << '\n';
	try {
		AForm* form = someRandomIntern.makeForm("robotomy request", "Bender");
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
	}
	catch (const std::exception& e) {
		std::cerr << utils::log::error(e.what()) << '\n';
	}

	std::cout << "\n---------------- " << ++test << " ----------------" << '\n';
	try {
		AForm* form = someRandomIntern.makeForm("42 privacy policy", "Elidjah");
		delete form;
	}
	catch (const std::exception& e) {
		std::cerr << utils::log::error(e.what()) << '\n';
	}
	try {
		AForm* form = someRandomIntern.makeForm("form", "Bender");
		delete form;
	}
	catch (const std::exception& e) {
		std::cerr << utils::log::error(e.what()) << '\n';
	}
	try {
		AForm* form = someRandomIntern.makeForm("", "Bender");
		delete form;
	}
	catch (const std::exception& e) {
		std::cerr << utils::log::error(e.what()) << '\n';
	}
	try {
		AForm* form =
		    someRandomIntern.makeForm("robotomy request for", "Bender");
		delete form;
	}
	catch (const std::exception& e) {
		std::cerr << utils::log::error(e.what()) << '\n';
	}

	std::cout << "\n---------------- " << ++test << " ----------------" << '\n';
	try {
		const Bureaucrat marta("Marta", 42);
		AForm* form = someRandomIntern.makeForm("robotomy-request", "Felix");
		marta.signForm(*form);
		marta.executeForm(*form);
		delete form;
	}
	catch (const std::exception& e) {
		std::cerr << utils::log::error(e.what()) << '\n';
	}

	std::cout << '\n';
}

// NOLINTEND(readability-magic-numbers)
