#pragma once

#include "AGradeException.hpp"
#include <string>

namespace GradeException {

class GradeTooHighException : public AGradeException {
public:
	GradeTooHighException(unsigned int grade,
	                      unsigned int required,
	                      const std::string& where = "",
	                      const std::string& who = "");
	explicit GradeTooHighException(const AGradeException& other);
};

} // namespace GradeException
