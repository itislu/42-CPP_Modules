// NOLINTBEGIN(cppcoreguidelines-avoid-const-or-ref-data-members)

#pragma once

#include "Grade.hpp"
#include "GradeException/AGradeException.hpp"
#include "GradeException/GradeTooHighException.hpp"
#include "GradeException/GradeTooLowException.hpp"
#include "utils/Exception.hpp"
#include <cstddef>
#include <ostream>
#include <string>

class Bureaucrat;

class AForm {
public:
	class GradeTooHighException : public GradeException::GradeTooHighException {
	public:
		GradeTooHighException(const GradeException::AGradeException& e);
	};

	class GradeTooLowException : public GradeException::GradeTooLowException {
	public:
		GradeTooLowException(const GradeException::AGradeException& e);
	};

	class FormNotSignedException : public utils::Exception {
	public:
		FormNotSignedException(const std::string& where = "",
		                       const std::string& who = "");
	};

	virtual ~AForm();

	void beSigned(const Bureaucrat& bureaucrat);
	virtual void execute(Bureaucrat const& executor) const = 0;
	void swap(AForm& other) throw();

	const std::string& name() const;
	const Grade& grade_to_sign() const;
	const Grade& grade_to_exec() const;
	const std::string& target() const;
	bool is_signed() const;
	size_t executions() const;

protected:
	AForm(const std::string& name,
	      unsigned int grade_to_sign,
	      unsigned int grade_to_exec,
	      const std::string& target);
	AForm(const AForm& other);

	AForm& operator=(const AForm& other);

private:
	AForm();

	const std::string _name;
	const Grade _grade_to_sign;
	const Grade _grade_to_exec;
	std::string _target;
	bool _is_signed;
	mutable size_t _executions;
};

std::ostream& operator<<(std::ostream& os, const AForm& form);

// NOLINTEND(cppcoreguidelines-avoid-const-or-ref-data-members)
