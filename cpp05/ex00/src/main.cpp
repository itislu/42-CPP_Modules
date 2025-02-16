// NOLINTBEGIN(readability-magic-numbers)

#include "Bureaucrat.hpp"
#include "Grade.hpp"
#include "GradeException/AGradeException.hpp"
#include "utils/log.hpp"
#include <exception>
#include <iostream>

int main()
{
	int test = 0;

	std::cout << "\n---------------- " << ++test << " ----------------" << '\n';
	try {
		Bureaucrat bureaucrat("George", 0);
		bureaucrat.demote();
	}
	catch (const std::exception& e) {
		std::cerr << utils::log::error(e.what()) << '\n';
	}

	std::cout << "\n---------------- " << ++test << " ----------------" << '\n';
	try {
		Bureaucrat bureaucrat("George", 151);
		bureaucrat.promote();
	}
	catch (const std::exception& e) {
		std::cerr << utils::log::error(e.what()) << '\n';
	}

	std::cout << "\n---------------- " << ++test << " ----------------" << '\n';
	try {
		Bureaucrat bureaucrat("George", Grade::highest_grade);
		bureaucrat.promote();
	}
	catch (const std::exception& e) {
		std::cerr << utils::log::error(e.what()) << '\n';
	}

	std::cout << "\n---------------- " << ++test << " ----------------" << '\n';
	try {
		Bureaucrat bureaucrat("George", Grade::lowest_grade);
		bureaucrat.demote();
	}
	catch (const std::exception& e) {
		std::cerr << utils::log::error(e.what()) << '\n';
	}

	std::cout << "\n---------------- " << ++test << " ----------------" << '\n';
	try {
		Bureaucrat bureaucrat("George", Grade::lowest_grade + 1);
		bureaucrat.promote();
	}
	catch (const GradeException::AGradeException& e) {
		std::cerr << utils::log::error(e.what()) << '\n';
	}

	std::cout << "\n---------------- " << ++test << " ----------------" << '\n';
	try {
		Bureaucrat bureaucrat("George", Grade::lowest_grade + 1);
		bureaucrat.promote();
	}
	catch (const Bureaucrat::GradeTooHighException& e) {
		std::cerr << "SHOULD NOT GET HERE - grade is too low, not too high!"
		          << '\n';
	}
	catch (const Bureaucrat::GradeTooLowException& e) {
		std::cerr << utils::log::error(e.what()) << '\n';
	}

	std::cout << '\n';
}

// NOLINTEND(readability-magic-numbers)
