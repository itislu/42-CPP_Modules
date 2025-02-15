#include "Bureaucrat.hpp"
#include "GradeException.hpp"
#include "grade.hpp"
#include "utils.hpp"
#include <iostream>
#include <string>

Bureaucrat::GradeTooHighException::GradeTooHighException(
    const std::string& where,
    const std::string& name,
    unsigned int grade) :
    GradeException(where + ": bureaucrat " + name + ": grade too high: "
                   + utils::to_string(grade) + ", highest allowed grade: "
                   + utils::to_string(highest_grade))
{}

Bureaucrat::GradeTooLowException::GradeTooLowException(const std::string& where,
                                                       const std::string& name,
                                                       unsigned int grade) :
    GradeException(where + ": bureaucrat " + name + ": grade too low: "
                   + utils::to_string(grade) + ", lowest allowed grade: "
                   + utils::to_string(lowest_grade))
{}

Bureaucrat::Bureaucrat(const std::string& name, unsigned int grade) :
    _name(name), _grade(grade)
{
	std::cerr << utils::log::info("Constructing bureaucrat " + _name) << '\n';
	if (grade::is_higher(_grade, highest_grade)) {
		throw GradeTooHighException(WHERE, _name, _grade);
	}
	if (grade::is_lower(_grade, lowest_grade)) {
		throw GradeTooLowException(WHERE, _name, _grade);
	}
	std::cerr << utils::log::ok(*this) << " constructed" << '\n';
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

void Bureaucrat::swap(Bureaucrat& other) { utils::swap(_grade, other._grade); }

void Bureaucrat::promote()
{
	const unsigned int promoted_grade = grade::increment(_grade);

	std::cerr << utils::log::info("Promoting ") << *this << '\n';
	if (grade::is_higher(promoted_grade, highest_grade)) {
		throw GradeTooHighException(WHERE, _name, promoted_grade);
	}
	_grade = promoted_grade;
	std::cerr << utils::log::ok(*this) << " promoted" << '\n';
}

void Bureaucrat::demote()
{
	const unsigned int demoted_grade = grade::decrement(_grade);

	std::cerr << utils::log::info("Demoting ") << *this << '\n';
	if (grade::is_lower(demoted_grade, lowest_grade)) {
		throw GradeTooLowException(WHERE, _name, demoted_grade);
	}
	_grade = demoted_grade;
	std::cerr << utils::log::ok(*this) << " demoted" << '\n';
}

const std::string& Bureaucrat::getName() const { return _name; }

unsigned int Bureaucrat::getGrade() const { return _grade; }

std::ostream& operator<<(std::ostream& os, const Bureaucrat& bureaucrat)
{
	os << bureaucrat.getName() << ", bureaucrat grade "
	   << bureaucrat.getGrade();
	return os;
}
