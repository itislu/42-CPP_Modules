// NOLINTBEGIN(readability-magic-numbers)

#include "Bureaucrat.hpp"
#include "Form.hpp"
#include "Grade.hpp"
#include "utils.hpp"
#include <exception>
#include <iostream>

int main()
{
	int test = 0;

	std::cout << "\n---------------- " << ++test << " ----------------" << '\n';
	try {
		const Form form("grade_to_sign too high", Grade::highest_grade - 1, 76);
		std::cout << form << '\n';
	}
	catch (const std::exception& e) {
		std::cerr << utils::log::error(e.what()) << '\n';
	}

	try {
		const Form form("grade_to_exec too high", 19, Grade::highest_grade - 1);
		std::cout << form << '\n';
	}
	catch (const std::exception& e) {
		std::cerr << utils::log::error(e.what()) << '\n';
	}

	try {
		const Form form("grade_to_sign too low", Grade::lowest_grade + 1, 76);
		std::cout << form << '\n';
	}
	catch (const std::exception& e) {
		std::cerr << utils::log::error(e.what()) << '\n';
	}

	try {
		const Form form("grade_to_exec too low", 19, Grade::lowest_grade + 1);
		std::cout << form << '\n';
	}
	catch (const std::exception& e) {
		std::cerr << utils::log::error(e.what()) << '\n';
	}

	std::cout << "\n---------------- " << ++test << " ----------------" << '\n';
	try {
		const unsigned int grade_to_sign = 19;
		const unsigned int grade_to_exec = 76;

		const Bureaucrat asterix("Asterix", Grade::highest_grade);
		const Bureaucrat obelix("Obelix", Grade::lowest_grade);
		Form form("Passierschein A38", grade_to_sign, grade_to_exec);

		std::cout << '\n' << form << "\n\n";
		obelix.signForm(form);
		std::cout << '\n' << form << "\n\n";
		asterix.signForm(form);
		std::cout << '\n' << form << '\n';
	}
	catch (const std::exception& e) {
		std::cerr << utils::log::error(e.what()) << '\n';
	}

	std::cout << "\n---------------- " << ++test << " ----------------" << '\n';
	try {
		const unsigned int grade_to_sign = 42;
		const unsigned int grade_to_exec = 43;

		const Bureaucrat asterix("Asterix", 42);
		const Bureaucrat obelix("Obelix", 43);
		Form form("Passierschein A38", grade_to_sign, grade_to_exec);

		std::cout << '\n' << form << "\n\n";
		obelix.signForm(form);
		std::cout << '\n' << form << "\n\n";
		asterix.signForm(form);
		std::cout << '\n' << form << '\n';
	}
	catch (const std::exception& e) {
		std::cerr << utils::log::error(e.what()) << '\n';
	}

	std::cout << "\n---------------- " << ++test << " ----------------" << '\n';
	try {
		Bureaucrat bureaucrat("George", Grade::lowest_grade + 1);
		bureaucrat.promote();
	}
	catch (const Form::GradeTooLowException& e) {
		std::cerr
		    << "SHOULD NOT GET HERE - Bureaucrat exception is thrown, not Form!"
		    << '\n';
	}
	catch (const Bureaucrat::GradeTooLowException& e) {
		std::cerr << utils::log::error(e.what()) << '\n';
	}

	std::cout << '\n';
}

// NOLINTEND(readability-magic-numbers)
