#include "Data.hpp"
#include <ostream>

std::ostream& operator<<(std::ostream& os, const Data& data)
{
	os << "std::string: " << data.s << ", void*: " << data.p
	   << ", double: " << data.d << ", int: " << data.i;
	return os;
}
