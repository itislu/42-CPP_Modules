// NOLINTBEGIN(cppcoreguidelines-avoid-const-or-ref-data-members)

#pragma once

#include "Grade.hpp"
#include "GradeException.hpp"
#include <ostream>
#include <string>

class Bureaucrat;

class Form {
public:
	class GradeTooHighException : public GradeException::GradeTooHighException {
	public:
		GradeTooHighException(const GradeException::AGradeException& e);
	};
	class GradeTooLowException : public GradeException::GradeTooLowException {
	public:
		GradeTooLowException(const GradeException::AGradeException& e);
	};

	Form(const std::string& name,
	     unsigned int grade_to_sign,
	     unsigned int grade_to_exec);
	Form(const Form& other);
	~Form();

	Form& operator=(Form other);
	void swap(Form& other);

	void beSigned(const Bureaucrat& bureaucrat);

	const std::string& name() const;
	const Grade& grade_to_sign() const;
	const Grade& grade_to_exec() const;
	bool is_signed() const;

private:
	Form();

	const std::string _name;
	const Grade _grade_to_sign;
	const Grade _grade_to_exec;
	bool _is_signed;
};

std::ostream& operator<<(std::ostream& os, const Form& form);

// NOLINTEND(cppcoreguidelines-avoid-const-or-ref-data-members)
