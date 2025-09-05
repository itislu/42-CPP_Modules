#include "Date.hpp"
#include "libftpp/Exception.hpp"
#include "libftpp/string.hpp"
#include <cstddef>
#include <ctime>
#include <ios>
#include <limits>
#include <stdexcept>
#include <string>

static bool parse_date(const std::string& str,
                       std::tm& tm,
                       std::string::size_type* endpos_out);
static std::string::size_type
parse_year(const std::string& str, std::tm& tm, std::string::size_type& endpos);
static std::string::size_type parse_month(const std::string& str,
                                          std::tm& tm,
                                          std::string::size_type& endpos);
static std::string::size_type
parse_day(const std::string& str, std::tm& tm, std::string::size_type& endpos);

std::time_t Date::serialize(const std::string& str,
                            std::string::size_type* endpos_out)
{
	std::tm tm = {};
	if (!parse_date(str, tm, endpos_out)) {
		throw ft::Exception("invalid date format: \"" + str + "\"", "Date");
	}

	const int year = tm.tm_year;
	const int month = tm.tm_mon;
	const int day = tm.tm_mday;

	// std::mktime() modifies `tm` to make it a valid date.
	const std::time_t time = std::mktime(&tm);
	if (time == -1 || tm.tm_year != year || tm.tm_mon != month
	    || tm.tm_mday != day) {
		throw ft::Exception("impossible date: " + str, "Date");
	}
	return time;
}

static bool parse_date(const std::string& str,
                       std::tm& tm,
                       std::string::size_type* endpos_out)
{
	// NOLINTNEXTLINE: Let endpos always be a valid reference.
	std::string::size_type _, &endpos = (endpos_out ? *endpos_out : _) = 0;
	std::string not_parsed(str);
	std::string::size_type pos = 0;

	try {
		endpos += parse_year(not_parsed, tm, pos);
		not_parsed.erase(0, pos);
		endpos += parse_month(not_parsed, tm, pos);
		not_parsed.erase(0, pos);
		endpos += parse_day(not_parsed, tm, pos);
		return true;
	}
	catch (const ft::Exception&) {
		endpos += pos;
		return false;
	}
	catch (const std::out_of_range&) {
		endpos += pos;
		return false;
	}
}

static std::string::size_type
parse_year(const std::string& str, std::tm& tm, std::string::size_type& pos)
{
	const int epoch = 1900;
	const int year = ft::from_string<int>(str, std::ios::dec, &pos);

	if (year < std::numeric_limits<int>::min() + epoch || str.at(pos) != '-') {
		throw ft::Exception("invalid year");
	}
	++pos;
	tm.tm_year = year - epoch;
	return pos;
}

static std::string::size_type
parse_month(const std::string& str, std::tm& tm, std::string::size_type& pos)
{
	const int month = ft::from_string<int>(str, std::ios::dec, &pos);

	if (pos > 2 || str.at(pos) != '-') {
		throw ft::Exception("invalid month");
	}
	++pos;
	tm.tm_mon = month - 1;
	return pos;
}

static std::string::size_type
parse_day(const std::string& str, std::tm& tm, std::string::size_type& pos)
{
	const int day = ft::from_string<int>(str, std::ios::dec, &pos);

	if (pos > 2) {
		throw ft::Exception("invalid day");
	}
	tm.tm_mday = day;
	return pos;
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
