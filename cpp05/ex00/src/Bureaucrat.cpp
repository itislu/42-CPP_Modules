#include "Bureaucrat.hpp"
#include "GradeException.hpp"
#include "where.hpp"
#include <cstring>
#include <ostream>
#include <string>

Bureaucrat::GradeTooHighException::GradeTooHighException(
    const std::string& error) :
    GradeException(error)
{
}

Bureaucrat::GradeTooLowException::GradeTooLowException(
    const std::string& error) :
    GradeException(error)
{
}

Bureaucrat::Bureaucrat(const Bureaucrat& other) :
    _name(other._name), _grade(other._grade)
{
}

Bureaucrat::Bureaucrat(const std::string& name, unsigned int grade) :
    _name(name), _grade(grade)
{
	if (_grade < highest_grade) {
		throw GradeTooHighException(
		    WHERE("constructing Bureaucrat with too high grade"));
	}
	if (_grade > lowest_grade) {
		throw GradeTooLowException(
		    WHERE("constructing Bureaucrat with too low grade"));
	}
}

Bureaucrat::~Bureaucrat() {}

Bureaucrat& Bureaucrat::operator=(Bureaucrat other)
{
	swap(other);
	return *this;
}

void Bureaucrat::promote()
{
	if (_grade - 1 < highest_grade) {
		throw GradeTooHighException(WHERE("promoting highest possible grade"));
	}
	--_grade;
}

void Bureaucrat::demote()
{
	if (_grade + 1 > lowest_grade) {
		throw GradeTooLowException(WHERE("demoting lowest possible grade"));
	}
	++_grade;
}

void Bureaucrat::swap(Bureaucrat& other)
{
	const unsigned int tmp = _grade;
	_grade = other._grade;
	other._grade = tmp;
}

const std::string& Bureaucrat::getName() const
{
	return _name;
}

unsigned int Bureaucrat::getGrade() const
{
	return _grade;
}

std::ostream& operator<<(std::ostream& os, const Bureaucrat& bureaucrat)
{
	os << bureaucrat.getName() << ", bureaucrat grade "
	   << bureaucrat.getGrade();
	return os;
}
