#include "Form.hpp"
#include "Bureaucrat.hpp"
#include "Grade.hpp"
#include "GradeException/AGradeException.hpp"
#include "GradeException/GradeTooHighException.hpp"
#include "GradeException/GradeTooLowException.hpp"
#include "utils/common.hpp"
#include "utils/log.hpp"
#include <iostream>
#include <string>

Form::GradeTooHighException::GradeTooHighException(
    const GradeException::AGradeException& e)
    : GradeException::GradeTooHighException(e)
{}

Form::GradeTooLowException::GradeTooLowException(
    const GradeException::AGradeException& e)
    : GradeException::GradeTooLowException(e)
{}

Form::Form(const std::string& name,
           unsigned int grade_to_sign,
           unsigned int grade_to_exec)
try
    : _name(name),
      _grade_to_sign(grade_to_sign),
      _grade_to_exec(grade_to_exec),
      _is_signed(false) //
{
	std::cerr << utils::log::ok(*this) << " constructed" << '\n';
}
catch (GradeException::AGradeException& e) {
	e.set_where(WHERE).set_who(name);
	if (e.is_too_high()) {
		throw Form::GradeTooHighException(e);
	}
	if (e.is_too_low()) {
		throw Form::GradeTooLowException(e);
	}
	throw;
}

Form::Form(const Form& other)
    : _name(other._name),
      _grade_to_sign(other._grade_to_sign),
      _grade_to_exec(other._grade_to_exec),
      _is_signed(false)
{}

Form::~Form() {}

Form& Form::operator=(Form other) throw()
{
	swap(other);
	return *this;
}

void Form::swap(Form& other) throw()
{
	utils::swap(_is_signed, other._is_signed);
}

void Form::beSigned(const Bureaucrat& bureaucrat)
{
	try {
		bureaucrat.getGrade().test(_grade_to_sign);
	}
	catch (GradeException::GradeTooLowException& e) {
		e.set_where(WHERE).set_who(_name);
		throw Form::GradeTooLowException(e);
	}
	_is_signed = true;
}

const std::string& Form::name() const { return _name; }

const Grade& Form::grade_to_sign() const { return _grade_to_sign; }

const Grade& Form::grade_to_exec() const { return _grade_to_exec; }

bool Form::is_signed() const { return _is_signed; }

std::ostream& operator<<(std::ostream& os, const Form& form)
{
	os << "Form " << form.name() << ", "
	   << (form.is_signed() ? "signed" : "not signed")
	   << ", grade to sign: " << form.grade_to_sign()
	   << ", grade to execute: " << form.grade_to_exec();
	return os;
}
