#include "AGradeException.hpp"
#include "utils.hpp"
#include <string>

namespace GradeException {

AGradeException::AGradeException(long delta,
                                 const std::string& msg,
                                 const std::string& where,
                                 const std::string& who)
    : _delta(delta),
      _msg(msg),
      _where(where),
      _who(who)
{
	_update_full_msg();
}

AGradeException::~AGradeException() throw() {}

const char* AGradeException::what() const throw() { return _full_msg.c_str(); }

AGradeException& AGradeException::set_where(const std::string& where)
{
	_where = where;
	_update_full_msg();
	return *this;
}

AGradeException& AGradeException::set_who(const std::string& who)
{
	_who = who;
	_update_full_msg();
	return *this;
}

bool AGradeException::is_too_high() const { return _delta < 0; }

bool AGradeException::is_too_low() const { return _delta > 0; }

long AGradeException::delta() const { return _delta; }

const std::string& AGradeException::msg() const { return _msg; }

const std::string& AGradeException::where() const { return _where; }

const std::string& AGradeException::who() const { return _who; }

void AGradeException::_update_full_msg()
{
	_full_msg = (_where.empty() ? "" : GRAY(_where + ": "))
	            + (_who.empty() ? "" : _who + ": ") + _msg;
}

} // namespace GradeException
