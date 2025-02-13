#include "Bureaucrat.hpp"
#include "GradeException.hpp"
#include "grade.hpp"
#include "utils.hpp"
#include <cstring>
#include <ostream>
#include <string>

Bureaucrat::GradeTooHighException::GradeTooHighException(
    const std::string& error) :
    GradeException(error)
{}

Bureaucrat::GradeTooLowException::GradeTooLowException(
    const std::string& error) :
    GradeException(error)
{}

Bureaucrat::Bureaucrat(const std::string& name, unsigned int grade) :
    _name(name), _grade(grade)
{
	if (grade::is_higher(_grade, highest_grade)) {
		throw GradeTooHighException(
		    WHERE("constructing Bureaucrat with too high grade"));
	}
	if (grade::is_lower(_grade, lowest_grade)) {
		throw GradeTooLowException(
		    WHERE("constructing Bureaucrat with too low grade"));
	}
}

Bureaucrat::Bureaucrat(const Bureaucrat& other) :
    _name(other._name), _grade(other._grade)
{}

Bureaucrat::~Bureaucrat() {}

Bureaucrat& Bureaucrat::operator=(Bureaucrat other)
{
	swap(other);
	return *this;
}

void Bureaucrat::promote()
{
	const unsigned int promoted_grade = grade::increment(_grade);

	if (grade::is_higher(promoted_grade, highest_grade)) {
		throw GradeTooHighException(WHERE("promoting highest possible grade"));
	}
	_grade = promoted_grade;
}

void Bureaucrat::demote()
{
	const unsigned int demoted_grade = grade::decrement(_grade);

	if (grade::is_lower(demoted_grade, lowest_grade)) {
		throw GradeTooLowException(WHERE("demoting lowest possible grade"));
	}
	_grade = demoted_grade;
}

void Bureaucrat::swap(Bureaucrat& other) { utils::swap(_grade, other._grade); }

const std::string& Bureaucrat::getName() const { return _name; }

unsigned int Bureaucrat::getGrade() const { return _grade; }

std::ostream& operator<<(std::ostream& os, const Bureaucrat& bureaucrat)
{
	os << bureaucrat.getName() << ", bureaucrat grade "
	   << bureaucrat.getGrade();
	return os;
}
