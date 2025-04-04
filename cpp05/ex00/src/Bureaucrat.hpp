// NOLINTBEGIN(cppcoreguidelines-avoid-const-or-ref-data-members)

#pragma once

#include "Grade.hpp"
#include "GradeException/AGradeException.hpp"
#include "GradeException/GradeTooHighException.hpp"
#include "GradeException/GradeTooLowException.hpp"
#include <ostream>
#include <string>

class Bureaucrat {
public:
	class GradeTooHighException : public GradeException::GradeTooHighException {
	public:
		explicit GradeTooHighException(
		    const GradeException::AGradeException& e);
	};

	class GradeTooLowException : public GradeException::GradeTooLowException {
	public:
		explicit GradeTooLowException(const GradeException::AGradeException& e);
	};

	Bureaucrat(const std::string& name, unsigned int grade);
	Bureaucrat(const Bureaucrat& other);
	~Bureaucrat();

	Bureaucrat& operator=(Bureaucrat other) throw();
	void swap(Bureaucrat& other) throw();

	void promote();
	void demote();

	const std::string& getName() const;
	const Grade& getGrade() const;

private:
	Bureaucrat();

	const std::string _name;
	Grade _grade;
};

std::ostream& operator<<(std::ostream& os, const Bureaucrat& bureaucrat);

// NOLINTEND(cppcoreguidelines-avoid-const-or-ref-data-members)
