#include "Grade.hpp"
#include "GradeException/GradeTooHighException.hpp"
#include "GradeException/GradeTooLowException.hpp"
#include "utils/utils.hpp"
#include <ostream>

Grade::Grade(unsigned int grade)
    : _raw(grade)
{
	if (*this < lowest_grade) {
		throw GradeException::GradeTooLowException(_raw, lowest_grade);
	}
	if (*this > highest_grade) {
		throw GradeException::GradeTooHighException(_raw, highest_grade);
	}
}

Grade::Grade(const Grade& other)
    : _raw(other._raw)
{}

Grade::~Grade() {}

Grade& Grade::operator=(Grade other)
{
	swap(other);
	return *this;
}

void Grade::swap(Grade& other) { utils::swap(_raw, other._raw); }

Grade& Grade::operator++()
{
	--_raw;
	if (*this > highest_grade) {
		throw GradeException::GradeTooHighException(_raw, highest_grade);
	}
	return *this;
}

Grade& Grade::operator--()
{
	++_raw;
	if (*this < lowest_grade) {
		throw GradeException::GradeTooLowException(_raw, lowest_grade);
	}
	return *this;
}

Grade Grade::operator++(int)
{
	const Grade prev(*this);
	++*this;
	return prev;
}

Grade Grade::operator--(int)
{
	const Grade prev(*this);
	--*this;
	return prev;
}

bool Grade::operator>(const Grade& other) const { return _raw < other._raw; }

bool Grade::operator<(const Grade& other) const { return _raw > other._raw; }

bool Grade::operator>(unsigned int other) const { return _raw < other; }

bool Grade::operator<(unsigned int other) const { return _raw > other; }

void Grade::test(const Grade& min) const
{
	if (*this < min) {
		throw GradeException::GradeTooLowException(_raw, min._raw);
	}
}

unsigned int Grade::get() const { return _raw; }

std::ostream& operator<<(std::ostream& os, const Grade& grade)
{
	os << grade.get();
	return os;
}
