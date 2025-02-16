// NOLINTBEGIN(cppcoreguidelines-avoid-const-or-ref-data-members)

#pragma once

#include "Form.hpp"
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
		GradeTooHighException(const GradeException::AGradeException& e);
	};
	class GradeTooLowException : public GradeException::GradeTooLowException {
	public:
		GradeTooLowException(const GradeException::AGradeException& e);
	};

	Bureaucrat(const std::string& name, unsigned int grade);
	Bureaucrat(const Bureaucrat& other);
	~Bureaucrat();

	Bureaucrat& operator=(Bureaucrat other);
	void swap(Bureaucrat& other);

	void signForm(Form& form) const;
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
