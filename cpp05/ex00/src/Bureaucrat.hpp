// NOLINTBEGIN(cppcoreguidelines-avoid-const-or-ref-data-members)

#pragma once

#include "GradeException.hpp"
#include <ostream>
#include <string>

class Bureaucrat {
public:
	class GradeTooHighException : public GradeException {
	public:
		GradeTooHighException(const std::string& where,
		                      const std::string& name,
		                      unsigned int grade);
	};
	class GradeTooLowException : public GradeException {
	public:
		GradeTooLowException(const std::string& where,
		                     const std::string& name,
		                     unsigned int grade);
	};

	Bureaucrat(const std::string& name, unsigned int grade);
	Bureaucrat(const Bureaucrat& other);
	~Bureaucrat();

	Bureaucrat& operator=(Bureaucrat other);
	void swap(Bureaucrat& other);

	void promote();
	void demote();

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

// NOLINTEND(cppcoreguidelines-avoid-const-or-ref-data-members)
