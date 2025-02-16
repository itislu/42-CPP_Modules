// NOLINTBEGIN(readability-magic-numbers)

#include "AForm.hpp"
#include "Bureaucrat.hpp"
#include "Grade.hpp"
#include "PresidentialPardonForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include <iostream>

int main()
{
	// {
	// 	const Bureaucrat asterix("Asterix", Grade::highest_grade);
	// 	RobotomyRequestForm r("Cleopatra");
	// 	asterix.signForm(r);

	// 	for (int i = 0; i < 100000; ++i) {
	// 		asterix.executeForm(r);
	// 		std::cerr << "Robotomy score: " << r.score() << '\n';
	// 	}
	// 	return 0;
	// }

	const Bureaucrat asterix("Asterix", Grade::highest_grade);
	const Bureaucrat obelix("Obelix", Grade::lowest_grade);
	ShrubberyCreationForm s("Caesar");
	RobotomyRequestForm r("Cleopatra");
	PresidentialPardonForm p("Brutus");

	std::cout << s << '\n';
	std::cout << r << '\n';
	std::cout << p << '\n';
	std::cout << '\n';
	obelix.signForm(s);
	obelix.signForm(r);
	obelix.signForm(p);
	std::cout << '\n';
	std::cout << s << '\n';
	std::cout << r << '\n';
	std::cout << p << '\n';
	std::cout << '\n';
	obelix.executeForm(s);
	obelix.executeForm(r);
	obelix.executeForm(p);
	asterix.executeForm(s);
	asterix.executeForm(r);
	asterix.executeForm(p);
	std::cout << '\n';
	std::cout << s << '\n';
	std::cout << r << '\n';
	std::cout << p << '\n';
	std::cout << '\n';
	asterix.signForm(s);
	asterix.signForm(r);
	asterix.signForm(p);
	std::cout << '\n';
	std::cout << s << '\n';
	std::cout << r << '\n';
	std::cout << p << '\n';
	std::cout << '\n';
	obelix.executeForm(s);
	obelix.executeForm(r);
	obelix.executeForm(p);
	// asterix.executeForm(s);
	// asterix.executeForm(r);
	// asterix.executeForm(p);

	// std::cout << "\n---------------- " << ++test << " ----------------" <<
	// '\n'; try { 	const unsigned int grade_to_sign = 42; 	const unsigned int
	// grade_to_exec = 43;

	// 	const Bureaucrat asterix("Asterix", 42);
	// 	const Bureaucrat obelix("Obelix", 43);
	// 	Form form("Passierschein A38", grade_to_sign, grade_to_exec);

	// 	std::cout << '\n' << form << "\n\n";
	// 	obelix.signForm(form);
	// 	std::cout << '\n' << form << "\n\n";
	// 	asterix.signForm(form);
	// 	std::cout << '\n' << form << '\n';
	// }
	// catch (const std::exception& e) {
	// 	std::cerr << utils::log::error(e.what()) << '\n';
	// }
}

// NOLINTEND(readability-magic-numbers)
