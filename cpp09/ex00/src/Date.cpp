#include "Date.hpp"
#include "libftpp/Exception.hpp"
#include "libftpp/string.hpp"
#include <cctype>
#include <cstddef>
#include <ctime>
#include <ios>
#include <limits>
#include <stdexcept>
#include <string>

static bool parse_date(const std::string& str,
                       std::tm* tm,
                       std::string::size_type* endpos_out);

std::time_t Date::serialize(const std::string& str,
                            std::string::size_type* endpos_out)
{
	std::tm tm = {};
	if (!parse_date(str, &tm, endpos_out)) {
		throw ft::Exception("invalid date format: \"" + str + "\"", "Date");
	}

	const int year = tm.tm_year;
	const int month = tm.tm_mon;
	const int day = tm.tm_mday;

	// std::mktime() modifies tm to make it a valid date
	const std::time_t time = std::mktime(&tm);
	if (time == -1 || tm.tm_year != year || tm.tm_mon != month
	    || tm.tm_mday != day) {
		throw ft::Exception("impossible date: " + str, "Date");
	}
	return time;
}

static bool parse_date(const std::string& str,
                       std::tm* tm,
                       std::string::size_type* endpos_out)
{
	// NOLINTNEXTLINE: Let endpos always be a valid reference
	std::string::size_type _, &endpos = (endpos_out ? *endpos_out : _) = 0;
	std::string::size_type pos = 0;

	try {
		const int epoch = 1900;
		std::string str_part(str);

		// endpos needs to always be up-to-date for outparam
		// NOLINTBEGIN(bugprone-inc-dec-in-conditions)
		const int year = ft::from_string<int>(str, std::ios::dec, &endpos);
		if (year < std::numeric_limits<int>::min() + epoch
		    || str.at(endpos) != '-' || !(bool)std::isdigit(str.at(++endpos))) {
			return false;
		}

		const int month = ft::from_string<int>(
		    str_part.erase(0, endpos), std::ios::dec, &pos);
		endpos += pos;
		if (str.at(endpos) != '-' || !(bool)std::isdigit(str.at(++endpos))) {
			return false;
		}
		// NOLINTEND(bugprone-inc-dec-in-conditions)

		const int day =
		    ft::from_string<int>(str_part.erase(0, ++pos), std::ios::dec, &pos);
		endpos += pos;

		tm->tm_year = year - epoch;
		tm->tm_mon = month - 1;
		tm->tm_mday = day;
		return true;
	}
	catch (const ft::FromStringException&) {
		// EMPTY: Shared error handling
	}
	catch (const std::out_of_range&) {
		// EMPTY: Shared error handling
	}
	endpos += pos;
	return false;
}

std::string Date::str(std::time_t time, const char* format)
{
	const std::tm* const tm_ptr = std::localtime(&time);
	if (tm_ptr == NULL) {
		throw ft::Exception("value too large for std::localtime", "Date");
	}

	char buffer[128];
	if (std::strftime(static_cast<char*>(buffer), 128, format, tm_ptr) == 0) {
		throw ft::Exception("string would exceed buffer size of 128 chars",
		                    "Date");
	}
	return static_cast<char*>(buffer);
}
