#include "Bureaucrat.hpp"
#include "Form.hpp"
#include "Grade.hpp"
#include "GradeException.hpp"
#include "utils.hpp"
#include <iostream>
#include <string>

Bureaucrat::GradeTooHighException::GradeTooHighException(
    const GradeException::AGradeException& e)
    : GradeException::GradeTooHighException(e)
{}

Bureaucrat::GradeTooLowException::GradeTooLowException(
    const GradeException::AGradeException& e)
    : GradeException::GradeTooLowException(e)
{}

Bureaucrat::Bureaucrat(const std::string& name, unsigned int grade)
try
    : _name(name),
      _grade(grade) //
{
	std::cerr << utils::log::ok(*this) << " constructed" << '\n';
}
catch (GradeException::AGradeException& e) {
	e.set_where(WHERE).set_who(name);
	if (e.is_too_high()) {
		throw Bureaucrat::GradeTooHighException(e);
	}
	if (e.is_too_low()) {
		throw Bureaucrat::GradeTooLowException(e);
	}
	throw;
}

Bureaucrat::Bureaucrat(const Bureaucrat& other)
    : _name(other._name),
      _grade(other._grade)
{}

Bureaucrat::~Bureaucrat() {}

Bureaucrat& Bureaucrat::operator=(Bureaucrat other)
{
	swap(other);
	return *this;
}

void Bureaucrat::swap(Bureaucrat& other) { utils::swap(_grade, other._grade); }

void Bureaucrat::signForm(Form& form) const
{
	try {
		form.beSigned(*this);
		std::cerr << utils::log::ok(_name + " signed " + form.name()) << '\n';
	}
	catch (const GradeException::AGradeException& e) {
		std::cerr << utils::log::error(_name + " cannot sign form "
		                               + form.name())
		          << utils::log::line(e.what()) << '\n';
	}
}

void Bureaucrat::promote()
{
	std::cerr << utils::log::info("Promoting ") << *this << '\n';
	try {
		++_grade;
	}
	catch (GradeException::GradeTooHighException& e) {
		e.set_where(WHERE).set_who(_name);
		throw Bureaucrat::GradeTooHighException(e);
	}
	std::cerr << utils::log::ok(*this) << " promoted" << '\n';
}

void Bureaucrat::demote()
{
	std::cerr << utils::log::info("Demoting ") << *this << '\n';
	try {
		--_grade;
	}
	catch (GradeException::GradeTooLowException& e) {
		e.set_where(WHERE).set_who(_name);
		throw Bureaucrat::GradeTooLowException(e);
	}
	std::cerr << utils::log::ok(*this) << " demoted" << '\n';
}

const std::string& Bureaucrat::getName() const { return _name; }

const Grade& Bureaucrat::getGrade() const { return _grade; }

std::ostream& operator<<(std::ostream& os, const Bureaucrat& bureaucrat)
{
	os << bureaucrat.getName() << ", bureaucrat grade "
	   << bureaucrat.getGrade();
	return os;
}
