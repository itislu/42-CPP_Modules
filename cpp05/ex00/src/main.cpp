#include "Bureaucrat.hpp"
#include "GradeException.hpp"
#include "grade.hpp"
#include "utils.hpp"
#include <exception>
#include <iostream>
#include <string>

int main()
{
	int test = 0;

	std::cout << "\n---------------- " << ++test << " ----------------" << '\n';
	try {
		Bureaucrat bureaucrat("George",
		                      grade::increment(Bureaucrat::highest_grade));
		bureaucrat.demote();
	}
	catch (const std::exception& e) {
		std::cerr << utils::log::error(e.what()) << '\n';
	}

	std::cout << "\n---------------- " << ++test << " ----------------" << '\n';
	try {
		Bureaucrat bureaucrat("George",
		                      grade::decrement(Bureaucrat::lowest_grade));
		bureaucrat.promote();
	}
	catch (const std::exception& e) {
		std::cerr << utils::log::error(e.what()) << '\n';
	}

	std::cout << "\n---------------- " << ++test << " ----------------" << '\n';
	try {
		Bureaucrat bureaucrat("George", Bureaucrat::highest_grade);
		bureaucrat.promote();
	}
	catch (const std::exception& e) {
		std::cerr << utils::log::error(e.what()) << '\n';
	}

	std::cout << "\n---------------- " << ++test << " ----------------" << '\n';
	try {
		Bureaucrat bureaucrat("George", Bureaucrat::lowest_grade);
		bureaucrat.demote();
	}
	catch (const std::exception& e) {
		std::cerr << utils::log::error(e.what()) << '\n';
	}

	std::cout << "\n---------------- " << ++test << " ----------------" << '\n';
	try {
		Bureaucrat bureaucrat("George",
		                      grade::decrement(Bureaucrat::lowest_grade));
		bureaucrat.promote();
	}
	catch (const GradeException& e) {
		std::cerr << utils::log::error(e.what()) << '\n';
	}

	std::cout << "\n---------------- " << ++test << " ----------------" << '\n';
	try {
		Bureaucrat bureaucrat("George",
		                      grade::decrement(Bureaucrat::lowest_grade));
		bureaucrat.promote();
	}
	catch (const Bureaucrat::GradeTooHighException& e) {
		std::cerr << "SHOULD NOT GET HERE" << '\n';
	}
	catch (const Bureaucrat::GradeTooLowException& e) {
		std::cerr << utils::log::error(e.what()) << '\n';
	}

	std::cout << '\n';
}
