// NOLINTBEGIN(cppcoreguidelines-special-member-functions)

#ifndef GRADEEXCEPTION_HPP
#define GRADEEXCEPTION_HPP

#include <stdexcept>
#include <string>

class GradeException : public std::runtime_error {
public:
	GradeException(const std::string& error);
};

#endif

// NOLINTEND(cppcoreguidelines-special-member-functions)
