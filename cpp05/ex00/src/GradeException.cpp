#include "GradeException.hpp"
#include <string>

GradeException::GradeException(const std::string& error) : _error(error) {}

GradeException::~GradeException() throw() {}

const char* GradeException::what() const throw()
{
	return _error.c_str();
}
