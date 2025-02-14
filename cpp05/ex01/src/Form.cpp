#include "Form.hpp"
#include "Bureaucrat.hpp"
#include "GradeException.hpp"
#include "grade.hpp"
#include "utils.hpp"
#include <ostream>
#include <string>

Form::GradeTooHighException::GradeTooHighException(unsigned int grade,
                                                   unsigned int required) :
    GradeException("grade too high: " + utils::to_string(grade)
                   + ", required: " + utils::to_string(required))
{}

Form::GradeTooLowException::GradeTooLowException(unsigned int grade,
                                                 unsigned int required) :
    GradeException("grade too low: " + utils::to_string(grade)
                   + ", required: " + utils::to_string(required))
{}

Form::Form(const std::string& name,
           unsigned int grade_to_sign,
           unsigned int grade_to_exec) :
    _name(name),
    _grade_to_sign(grade_to_sign),
    _grade_to_exec(grade_to_exec),
    _is_signed(false)
{}

Form::Form(const Form& other) :
    _name(other._name),
    _grade_to_sign(other._grade_to_sign),
    _grade_to_exec(other._grade_to_exec),
    _is_signed(false)
{}

Form::~Form() {}

Form& Form::operator=(Form other)
{
	Form::swap(other);
	return *this;
}

void Form::swap(Form& other) { utils::swap(_is_signed, other._is_signed); }

void Form::beSigned(const Bureaucrat& bureaucrat)
{
	if (grade::is_lower(bureaucrat.getGrade(), _grade_to_sign)) {
		throw GradeTooLowException(bureaucrat.getGrade(), _grade_to_sign);
	}
	_is_signed = true;
}

const std::string& Form::name() const { return _name; }

unsigned int Form::grade_to_sign() const { return _grade_to_sign; }

unsigned int Form::grade_to_exec() const { return _grade_to_exec; }

bool Form::is_signed() const { return _is_signed; }

std::ostream& operator<<(std::ostream& os, const Form& form)
{
	os << "Form " << form.name() << ", "
	   << (form.is_signed() ? "signed" : "not signed")
	   << ", grade to sign: " << form.grade_to_sign()
	   << ", grade to execute: " << form.grade_to_exec();
	return os;
}
