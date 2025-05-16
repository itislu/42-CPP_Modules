#include "Date.hpp"
#include "libftpp/Exception.hpp"
#include <cstddef>
#include <ctime>
#include <string>
#include <time.h>

const char* const Date::default_format = "%Y-%m-%d";

/**
 * Strategy:
 *   1. Parse into `std::tm` using `strptime()`.
 *   2. Use `std::mktime()` to validate and serialize date to `std::time_t`.
 */
std::time_t Date::serialize(const std::string& str,
                            std::string::size_type* endpos_out,
                            const char* format)
{
	std::tm tm = {};
	const char* endptr = strptime(str.c_str(), format, &tm);
	if (endptr == NULL) {
		throw ft::Exception("Invalid date format: \"" + str + "\"", "Date");
	}

	const int year = tm.tm_year;
	const int month = tm.tm_mon;
	const int day = tm.tm_mday;

	// std::mktime() modifies tm to make it a valid date
	const std::time_t time = std::mktime(&tm);
	if (time == -1 || tm.tm_year != year || tm.tm_mon != month
	    || tm.tm_mday != day) {
		throw ft::Exception("Impossible date: " + str, "Date");
	}

	if (endpos_out) {
		*endpos_out = endptr - str.c_str();
	}
	return time;
}

std::string Date::str(std::time_t time, const char* format)
{
	const std::tm* const tm_ptr = std::localtime(&time);
	if (tm_ptr == NULL) {
		throw ft::Exception("Value too large for std::localtime", "Date");
	}

	char buffer[128];
	if (std::strftime(static_cast<char*>(buffer), 128, format, tm_ptr) == 0) {
		throw ft::Exception("String would exceed buffer size of 128 chars",
		                    "Date");
	}
	return static_cast<char*>(buffer);
}
