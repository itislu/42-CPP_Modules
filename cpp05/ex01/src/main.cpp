// NOLINTBEGIN(readability-magic-numbers)

#include "Bureaucrat.hpp"
#include "Form.hpp"
#include <iostream>

int main()
{
	const Bureaucrat asterix("Asterix", Bureaucrat::highest_grade);
	const Bureaucrat obelix("Obelix", Bureaucrat::lowest_grade);
	Form form("Passierschein A38", 19, 76);

	std::cout << form << "\n\n";
	obelix.signForm(form);
	std::cout << '\n' << form << "\n\n";
	asterix.signForm(form);
	std::cout << '\n' << form << '\n';
}

// NOLINTEND(readability-magic-numbers)
