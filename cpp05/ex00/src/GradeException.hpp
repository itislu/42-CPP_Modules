// NOLINTBEGIN(cppcoreguidelines-special-member-functions)

#ifndef GRADEEXCEPTION_HPP
#define GRADEEXCEPTION_HPP

#include <exception>
#include <string>

class GradeException : public std::exception {
public:
	GradeException(const std::string& error);
	virtual ~GradeException() throw();

	const char* what() const throw();

private:
	std::string _error;
};

#endif

// NOLINTEND(cppcoreguidelines-special-member-functions)
