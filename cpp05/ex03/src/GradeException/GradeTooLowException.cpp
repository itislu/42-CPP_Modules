#include "GradeTooLowException.hpp"
#include "AGradeException.hpp"
#include "utils/string.hpp"
#include <string>

namespace GradeException {

GradeTooLowException::GradeTooLowException(unsigned int grade,
                                           unsigned int required,
                                           const std::string& where,
                                           const std::string& who)
    : AGradeException(static_cast<long>(grade) - required,
                      "grade too low: " + utils::string::to_string(grade)
                          + ", lowest allowed grade: "
                          + utils::string::to_string(required),
                      where,
                      who)
{}

GradeTooLowException::GradeTooLowException(const AGradeException& other)
    : AGradeException(other.delta(), other.msg(), other.where(), other.who())
{}

} // namespace GradeException
