#include "AForm.hpp"
#include "Bureaucrat.hpp"
#include "Grade.hpp"
#include "GradeException/AGradeException.hpp"
#include "GradeException/GradeTooHighException.hpp"
#include "GradeException/GradeTooLowException.hpp"
#include "utils/Exception.hpp"
#include "utils/common.hpp"
#include "utils/log.hpp"
#include <cstddef>
#include <iostream>
#include <string>

AForm::GradeTooHighException::GradeTooHighException(
    const GradeException::AGradeException& e)
    : GradeException::GradeTooHighException(e)
{}

AForm::GradeTooLowException::GradeTooLowException(
    const GradeException::AGradeException& e)
    : GradeException::GradeTooLowException(e)
{}

AForm::FormNotSignedException::FormNotSignedException(const std::string& where,
                                                      const std::string& who)
    : utils::Exception("Form not signed", where, who)
{}

AForm::AForm(const std::string& name,
             unsigned int grade_to_sign,
             unsigned int grade_to_exec,
             const std::string& target)
try
    : _name(name),
      _grade_to_sign(grade_to_sign),
      _grade_to_exec(grade_to_exec),
      _target(target),
      _is_signed(false),
      _executions() //
{
	std::cerr << utils::log::ok(*this) << " constructed" << '\n';
}
catch (GradeException::AGradeException& e) {
	e.set_where(WHERE).set_who(name);
	if (e.is_too_high()) {
		throw AForm::GradeTooHighException(e);
	}
	if (e.is_too_low()) {
		throw AForm::GradeTooLowException(e);
	}
	throw;
}

AForm::AForm(const AForm& other)
    : _name(other._name),
      _grade_to_sign(other._grade_to_sign),
      _grade_to_exec(other._grade_to_exec),
      _target(other._target),
      _is_signed(false),
      _executions(other._executions)
{}

AForm::~AForm() {}

AForm& AForm::operator=(const AForm& other)
{
	if (this != &other) {
		_target = other._target;
		_is_signed = other._is_signed;
	}
	return *this;
}

void AForm::beSigned(const Bureaucrat& bureaucrat)
{
	try {
		bureaucrat.getGrade().test(_grade_to_sign);
	}
	catch (GradeException::GradeTooLowException& e) {
		e.set_where(WHERE).set_who(_name);
		throw AForm::GradeTooLowException(e);
	}
	_is_signed = true;
}

void AForm::execute(Bureaucrat const& executor) const
{
	if (!_is_signed) {
		throw FormNotSignedException(WHERE, _name);
	}
	try {
		executor.getGrade().test(_grade_to_exec);
	}
	catch (GradeException::GradeTooLowException& e) {
		e.set_where(WHERE).set_who(_name);
		throw AForm::GradeTooLowException(e);
	}
	++_executions;
}

void AForm::swap(AForm& other) throw()
{
	_target.swap(other._target);
	utils::swap(_is_signed, other._is_signed);
	utils::swap(_executions, other._executions);
}

const std::string& AForm::name() const { return _name; }

const Grade& AForm::grade_to_sign() const { return _grade_to_sign; }

const Grade& AForm::grade_to_exec() const { return _grade_to_exec; }

const std::string& AForm::target() const { return _target; }

bool AForm::is_signed() const { return _is_signed; }

size_t AForm::executions() const { return _executions; }

std::ostream& operator<<(std::ostream& os, const AForm& form)
{
	os << "Form " << form.name() << ", "
	   << (form.is_signed() ? "signed" : "not signed")
	   << ", grade to sign: " << form.grade_to_sign()
	   << ", grade to execute: " << form.grade_to_exec();
	return os;
}
