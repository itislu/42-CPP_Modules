// NOLINTBEGIN(cppcoreguidelines-avoid-const-or-ref-data-members)

#ifndef BUREAUCRAT_HPP
#define BUREAUCRAT_HPP

#include "GradeException.hpp"
#include <ostream>
#include <string>

class Bureaucrat {
public:
	class GradeTooHighException : public GradeException {
	public:
		GradeTooHighException(const std::string& error);
	};
	class GradeTooLowException : public GradeException {
	public:
		GradeTooLowException(const std::string& error);
	};

	Bureaucrat(const Bureaucrat& other);
	Bureaucrat(const std::string& name, unsigned int grade);
	~Bureaucrat();

	Bureaucrat& operator=(Bureaucrat other);

	void promote();
	void demote();
	void swap(Bureaucrat& other);
	const std::string& getName() const;
	unsigned int getGrade() const;

	static const unsigned int highest_grade = 1;
	static const unsigned int lowest_grade = 150;

private:
	Bureaucrat();

	const std::string _name;
	unsigned int _grade;
};

std::ostream& operator<<(std::ostream& os, const Bureaucrat& bureaucrat);

#endif

// NOLINTEND(cppcoreguidelines-avoid-const-or-ref-data-members)
