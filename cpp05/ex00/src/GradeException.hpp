// NOLINTBEGIN(cppcoreguidelines-special-member-functions)

#pragma once

#include <stdexcept>
#include <string>

class GradeException : public std::runtime_error {
public:
	GradeException(const std::string& error);
};

// NOLINTEND(cppcoreguidelines-special-member-functions)
