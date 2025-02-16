#include "GradeTooHighException.hpp"
#include "AGradeException.hpp"
#include "utils.hpp"
#include <string>

namespace GradeException {

GradeTooHighException::GradeTooHighException(unsigned int grade,
                                             unsigned int required,
                                             const std::string& where,
                                             const std::string& who)
    : AGradeException(static_cast<long>(grade) - required,
                      "grade too high: " + utils::to_string(grade)
                          + ", highest allowed grade: "
                          + utils::to_string(required),
                      where,
                      who)
{}

GradeTooHighException::GradeTooHighException(const AGradeException& other)
    : AGradeException(other.delta(), other.msg(), other.where(), other.who())
{}

} // namespace GradeException
