#ifndef WHERE_HPP
#define WHERE_HPP

#include <cstddef>
#include <string>

#define WHERE(msg) where(__FILE__, __LINE__, (msg))

std::string where(const char* file, size_t line, const std::string& msg);

#endif
