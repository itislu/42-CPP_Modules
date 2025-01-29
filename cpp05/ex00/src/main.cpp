#include "Bureaucrat.hpp"
#include "GradeException.hpp"
#include <exception>
#include <iostream>

int main()
{
	try {
		Bureaucrat bureaucrat("George", Bureaucrat::highest_grade - 1);
		std::cout << bureaucrat << " constructed" << '\n';
		bureaucrat.demote();
		std::cout << bureaucrat << '\n';
	}
	catch (const std::exception& e) {
		std::cout << e.what() << '\n';
	}

	std::cout << '\n';

	try {
		Bureaucrat bureaucrat("George", Bureaucrat::lowest_grade + 1);
		std::cout << bureaucrat << " constructed" << '\n';
		bureaucrat.promote();
		std::cout << bureaucrat << '\n';
	}
	catch (const std::exception& e) {
		std::cout << e.what() << '\n';
	}

	std::cout << '\n';

	try {
		Bureaucrat bureaucrat("George", Bureaucrat::highest_grade);
		std::cout << bureaucrat << " constructed" << '\n';
		bureaucrat.promote();
		std::cout << bureaucrat << '\n';
	}
	catch (const std::exception& e) {
		std::cout << e.what() << '\n';
	}

	std::cout << '\n';

	try {
		Bureaucrat bureaucrat("George", Bureaucrat::lowest_grade);
		std::cout << bureaucrat << " constructed" << '\n';
		bureaucrat.demote();
		std::cout << bureaucrat << '\n';
	}
	catch (const std::exception& e) {
		std::cout << e.what() << '\n';
	}

	std::cout << '\n';

	try {
		Bureaucrat bureaucrat("George", Bureaucrat::lowest_grade + 1);
		std::cout << bureaucrat << " constructed" << '\n';
		bureaucrat.promote();
		std::cout << bureaucrat << '\n';
	}
	catch (const GradeException& e) {
		std::cout << e.what() << '\n';
	}

	std::cout << '\n';

	try {
		Bureaucrat bureaucrat("George", Bureaucrat::lowest_grade + 1);
		std::cout << bureaucrat << " constructed" << '\n';
		bureaucrat.promote();
		std::cout << bureaucrat << '\n';
	}
	catch (const Bureaucrat::GradeTooHighException& e) {
		std::cout << "SHOULD NOT GET HERE " << e.what() << '\n';
	}
	catch (const Bureaucrat::GradeTooLowException& e) {
		std::cout << e.what() << '\n';
	}
}
