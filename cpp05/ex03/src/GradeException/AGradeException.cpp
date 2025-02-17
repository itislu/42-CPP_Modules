#include "AGradeException.hpp"
#include "utils/Exception.hpp"
#include <string>

namespace GradeException {

AGradeException::AGradeException(long delta,
                                 const std::string& msg,
                                 const std::string& where,
                                 const std::string& who)
    : utils::Exception(msg, where, who),
      _delta(delta)
{}

AGradeException::~AGradeException() throw() {}

bool AGradeException::is_too_high() const { return _delta < 0; }

bool AGradeException::is_too_low() const { return _delta > 0; }

long AGradeException::delta() const { return _delta; }

} // namespace GradeException
