#include "GradeException.hpp"
#include "utils.hpp"
#include <string>

namespace GradeException {

AGradeException::~AGradeException() throw() {}

AGradeException::AGradeException(bool is_too_low,
                                 const std::string& msg,
                                 const std::string& who,
                                 const std::string& where)
    : _is_too_low(is_too_low), _msg(msg), _who(who), _where(where)
{
	_update_full_msg();
}

const char* AGradeException::what() const throw() { return _full_msg.c_str(); }

AGradeException& AGradeException::set_who(const std::string& who)
{
	_who = who;
	_update_full_msg();
	return *this;
}

AGradeException& AGradeException::set_where(const std::string& where)
{
	_where = where;
	_update_full_msg();
	return *this;
}

bool AGradeException::is_too_high() const { return !_is_too_low; }

bool AGradeException::is_too_low() const { return _is_too_low; }

const std::string& AGradeException::msg() const { return _msg; }

const std::string& AGradeException::who() const { return _who; }

const std::string& AGradeException::where() const { return _where; }

void AGradeException::_update_full_msg()
{
	_full_msg = (_where.empty() ? "" : GRAY(_where + ": "))
	            + (_who.empty() ? "" : _who + ": ") + _msg;
}

GradeTooHighException::GradeTooHighException(unsigned int grade,
                                             unsigned int required,
                                             const std::string& who,
                                             const std::string& where)
    : AGradeException(false,
                      "grade too high: " + utils::to_string(grade)
                          + ", highest allowed grade: "
                          + utils::to_string(required),
                      who,
                      where)
{}

GradeTooHighException::GradeTooHighException(const AGradeException& other)
    : AGradeException(other.is_too_low(),
                      other.msg(),
                      other.who(),
                      other.where())
{}

GradeTooLowException::GradeTooLowException(unsigned int grade,
                                           unsigned int required,
                                           const std::string& who,
                                           const std::string& where)
    : AGradeException(true,
                      "grade too low: " + utils::to_string(grade)
                          + ", lowest allowed grade: "
                          + utils::to_string(required),
                      who,
                      where)
{}

GradeTooLowException::GradeTooLowException(const AGradeException& other)
    : AGradeException(other.is_too_low(),
                      other.msg(),
                      other.who(),
                      other.where())
{}

} // namespace GradeException
