// NOLINTBEGIN(readability-magic-numbers)

#include "AForm.hpp"
#include "Bureaucrat.hpp"
#include "Grade.hpp"
#include "PresidentialPardonForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include "utils/log.hpp"
#include "utils/string.hpp"
#include <cstddef>
#include <exception>
#include <iostream>
#include <streambuf>
#include <string>

int main()
{
	int test = 0;

	std::cout << "\n---------------- " << ++test << " ----------------" << '\n';
	try {
		const Bureaucrat asterix("Asterix", Grade::highest_grade);
		const Bureaucrat obelix("Obelix", Grade::lowest_grade);
		ShrubberyCreationForm s("Caesar");
		RobotomyRequestForm r("Cleopatra");
		PresidentialPardonForm p("Brutus");

		std::cout << '\n';
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
		asterix.executeForm(s);
		asterix.executeForm(r);
		asterix.executeForm(p);
	}
	catch (const std::exception& e) {
		std::cerr << utils::log::warn(std::string("SHOULD NOT GET HERE - ")
		                              + e.what())
		          << '\n';
	}

	std::cout << "\n---------------- " << ++test << " ----------------" << '\n';
	try {
		const int repeats = 1000000;
		const Bureaucrat asterix("Asterix", Grade::highest_grade);
		RobotomyRequestForm r("Cleopatra");
		asterix.signForm(r);

		std::cerr << utils::log::info(std::string("Running robotomy ")
		                              + utils::string::to_string(repeats)
		                              + " times...")
		          << '\n';

		std::streambuf* og_cout = std::cout.rdbuf();
		std::streambuf* og_cerr = std::cerr.rdbuf();
		std::cout.rdbuf(NULL);
		std::cerr.rdbuf(NULL);

		try {
			for (int i = 0; i < repeats; ++i) {
				asterix.executeForm(r);
			}
		}
		catch (...) {
			std::cout.rdbuf(og_cout);
			std::cerr.rdbuf(og_cerr);
			throw;
		}

		std::cout.rdbuf(og_cout);
		std::cerr.rdbuf(og_cerr);

		std::cerr << utils::log::info("Robotomy score: "
		                              + utils::string::to_string(r.score()))
		          << '\n';
	}
	catch (const std::exception& e) {
		std::cerr << utils::log::warn(std::string("SHOULD NOT GET HERE - ")
		                              + e.what())
		          << '\n';
	}

	std::cout << '\n';
}

// NOLINTEND(readability-magic-numbers)
