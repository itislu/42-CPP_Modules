#include "Bureaucrat.hpp"
#include "GradeException.hpp"
#include "grade.hpp"
#include "utils.hpp"
#include <exception>
#include <iostream>
#include <string>

int main()
{
	int test = 1;

	std::cerr << "\n---------------- " << test++ << " ----------------" << '\n';

	try {
		Bureaucrat bureaucrat("George",
		                      grade::increment(Bureaucrat::highest_grade));
		std::cout << utils::log::ok(bureaucrat) << " constructed" << '\n';
		bureaucrat.demote();
		std::cout << utils::log::ok(bureaucrat) << '\n';
	}
	catch (const std::exception& e) {
		std::cerr << utils::log::error(e.what()) << '\n';
	}

	std::cerr << "\n---------------- " << test++ << " ----------------" << '\n';

	try {
		Bureaucrat bureaucrat("George",
		                      grade::decrement(Bureaucrat::lowest_grade));
		std::cout << utils::log::ok(bureaucrat) << " constructed" << '\n';
		bureaucrat.promote();
		std::cout << utils::log::ok(bureaucrat) << '\n';
	}
	catch (const std::exception& e) {
		std::cerr << utils::log::error(e.what()) << '\n';
	}

	std::cerr << "\n---------------- " << test++ << " ----------------" << '\n';

	try {
		Bureaucrat bureaucrat("George", Bureaucrat::highest_grade);
		std::cout << utils::log::ok(bureaucrat) << " constructed" << '\n';
		bureaucrat.promote();
		std::cout << utils::log::ok(bureaucrat) << '\n';
	}
	catch (const std::exception& e) {
		std::cerr << utils::log::error(e.what()) << '\n';
	}

	std::cerr << "\n---------------- " << test++ << " ----------------" << '\n';

	try {
		Bureaucrat bureaucrat("George", Bureaucrat::lowest_grade);
		std::cout << utils::log::ok(bureaucrat) << " constructed" << '\n';
		bureaucrat.demote();
		std::cout << utils::log::ok(bureaucrat) << '\n';
	}
	catch (const std::exception& e) {
		std::cerr << utils::log::error(e.what()) << '\n';
	}

	std::cerr << "\n---------------- " << test++ << " ----------------" << '\n';

	try {
		Bureaucrat bureaucrat("George",
		                      grade::decrement(Bureaucrat::lowest_grade));
		std::cout << utils::log::ok(bureaucrat) << " constructed" << '\n';
		bureaucrat.promote();
		std::cout << utils::log::ok(bureaucrat) << '\n';
	}
	catch (const GradeException& e) {
		std::cerr << utils::log::error(e.what()) << '\n';
	}

	std::cerr << "\n---------------- " << test++ << " ----------------" << '\n';

	try {
		Bureaucrat bureaucrat("George",
		                      grade::decrement(Bureaucrat::lowest_grade));
		std::cout << utils::log::ok(bureaucrat) << " constructed" << '\n';
		bureaucrat.promote();
		std::cout << utils::log::ok(bureaucrat) << '\n';
	}
	catch (const Bureaucrat::GradeTooHighException& e) {
		std::cerr << utils::log::error(std::string("SHOULD NOT GET HERE ")
		                               + e.what());
	}
	catch (const Bureaucrat::GradeTooLowException& e) {
		std::cerr << utils::log::error(e.what()) << '\n';
	}

	std::cerr << '\n';
}
