#include "../../Expected.hpp"

namespace utils {

const char* BadExpectedAccess<void>::what() const throw()
{
	return "bad access to utils::Expected without expected value";
}

BadExpectedAccess<void>::BadExpectedAccess() throw() {}

BadExpectedAccess<void>::BadExpectedAccess(const BadExpectedAccess& /*unused*/)
{}

BadExpectedAccess<void>::~BadExpectedAccess() throw() {}

BadExpectedAccess<void>&
BadExpectedAccess<void>::operator=(const BadExpectedAccess& /*unused*/)
{
	return *this;
}

} // namespace utils
