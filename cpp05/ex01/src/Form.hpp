// NOLINTBEGIN(cppcoreguidelines-avoid-const-or-ref-data-members)

#pragma once

#include "GradeException.hpp"
#include <ostream>
#include <string>

class Bureaucrat;

class Form {
public:
	class GradeTooHighException : public GradeException {
	public:
		GradeTooHighException(const std::string& error);
	};
	class GradeTooLowException : public GradeException {
	public:
		GradeTooLowException(const std::string& error);
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
	unsigned int grade_to_sign() const;
	unsigned int grade_to_exec() const;
	bool is_signed() const;

private:
	Form();

	const std::string _name;
	const unsigned int _grade_to_sign;
	const unsigned int _grade_to_exec;
	bool _is_signed;
};

std::ostream& operator<<(std::ostream& os, const Form& form);

// NOLINTEND(cppcoreguidelines-avoid-const-or-ref-data-members)
