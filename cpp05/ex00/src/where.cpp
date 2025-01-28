// NOLINTBEGIN(misc-use-internal-linkage)

#include <cstddef>
#include <sstream>
#include <string>

std::string where(const char* file, size_t line, const std::string& msg)
{
	std::ostringstream os;
	os << file << ":" << line;
	if (!msg.empty()) {
		os << ": " << msg;
	}
	return os.str();
}

// NOLINTEND(misc-use-internal-linkage)
