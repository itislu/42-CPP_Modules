#include "AForm.hpp"
#include "Bureaucrat.hpp"
#include "Grade.hpp"
#include "GradeException.hpp"
#include "utils.hpp"
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

AForm::AForm(const std::string& name,
             unsigned int grade_to_sign,
             unsigned int grade_to_exec,
             const std::string& target)
try
    : _name(name),
      _grade_to_sign(grade_to_sign),
      _grade_to_exec(grade_to_exec),
      _target(target),
      _is_signed(false) //
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
      _is_signed(false)
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
		// Subject: "Otherwise, throw an appropriate exception."
		// throw GradeTooLowException("not signed"); // TODO GradeTooLowException??
	}
	try {
		executor.getGrade().test(_grade_to_exec);
	}
	catch (GradeException::GradeTooLowException& e) {
		e.set_where(WHERE).set_who(_name);
		throw AForm::GradeTooLowException(e);
	}
}

void AForm::swap(AForm& other)
{
	utils::swap(_target, other._target);
	utils::swap(_is_signed, other._is_signed);
}

const std::string& AForm::name() const { return _name; }

const Grade& AForm::grade_to_sign() const { return _grade_to_sign; }

const Grade& AForm::grade_to_exec() const { return _grade_to_exec; }

const std::string& AForm::target() const { return _target; }

bool AForm::is_signed() const { return _is_signed; }

std::ostream& operator<<(std::ostream& os, const AForm& form)
{
	os << "Form " << form.name() << ", "
	   << (form.is_signed() ? "signed" : "not signed")
	   << ", grade to sign: " << form.grade_to_sign()
	   << ", grade to execute: " << form.grade_to_exec();
	return os;
}
