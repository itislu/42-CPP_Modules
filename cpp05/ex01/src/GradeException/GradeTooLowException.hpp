#pragma once

#include "AGradeException.hpp"
#include <string>

namespace GradeException {

class GradeTooLowException : public AGradeException {
public:
	GradeTooLowException(unsigned int grade,
	                     unsigned int required,
	                     const std::string& where = "",
	                     const std::string& who = "");
	GradeTooLowException(const AGradeException& other);
};

} // namespace GradeException
