#include "GradeException.hpp"
#include <stdexcept>
#include <string>

GradeException::GradeException(const std::string& error) :
    std::runtime_error(error)
{}
