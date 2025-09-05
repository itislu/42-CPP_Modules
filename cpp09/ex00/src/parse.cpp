#include "parse.hpp"
#include "Date.hpp"
#include "libftpp/Exception.hpp"
#include "libftpp/string.hpp"
#include "libftpp/type_traits.hpp"
#include <algorithm>
#include <cmath>
#include <ctime>
#include <ios>
#include <string>

template <typename To>
static To parse_field(const std::string& str, const std::string& field_name);
template <typename T>
static bool is_within_limit(const std::string& value_str, T value, T limit);

std::time_t parse_date(const std::string& str)
try {
	return parse_field<std::time_t>(str, "date");
}
catch (ft::Exception& e) {
	e.set_who("Date");
	throw;
}

double parse_rate(const std::string& str)
try {
	const double rate = parse_field<double>(str, "exchange rate");

	if (std::signbit(rate) != 0 && !is_within_limit(str, rate, 0.)) {
		throw ft::Exception("negative exchange rate");
	}
	return std::abs(rate);
}
catch (ft::Exception& e) {
	e.set_who("Rate");
	throw;
}

float parse_amount(const std::string& str, float max_query_amount)
try {
	const float amount = parse_field<float>(str, "query amount");

	// Signed zeros are equal to 0: https://en.wikipedia.org/wiki/Signed_zero
	if (std::signbit(amount) != 0 && !is_within_limit(str, amount, 0.F)) {
		throw ft::Exception("negative query amount");
	}
	if (!is_within_limit(str, amount, max_query_amount)) {
		throw ft::Exception("too large query amount");
	}
	return std::abs(amount);
}
catch (ft::Exception& e) {
	e.set_who("Amount");
	throw;
}

template <typename To>
static To parse_field(const std::string& str, const std::string& field_name)
{
	if (str.empty()) {
		throw ft::Exception("Empty " + field_name + " field");
	}
	To result;
	std::string::size_type endpos = 0;

	if (ft::is_same<To, std::time_t>::value) {
		result = Date::serialize(str, &endpos);
	}
	else {
		result = ft::from_string<To>(str, std::ios::fixed, &endpos);
	}
	if (endpos != str.length()) {
		throw ft::Exception("excess characters in " + field_name + " field");
	}
	return result;
}

/**
 * Returns true if |value| <= |limit|. Uses `value_str` to break ties caused by
 * rounding.
 */
template <typename T>
static bool is_within_limit(const std::string& value_str, T value, T limit)
{
	const T value_abs = std::abs(value);
	const T limit_abs = std::abs(limit);
	if (value_abs < limit_abs) {
		return true;
	}
	if (value_abs > limit_abs) {
		return false;
	}
	// Numerically equal, but potentially rounded from string conversion.

	typedef std::string::size_type size_type;
	const std::string limit_str = ft::to_string(limit, std::ios::fixed);

	// Skip sign and leading zeros.
	const size_type limit_start =
	    std::min(limit_str.find_first_not_of("0+-"), limit_str.length());
	const size_type value_start =
	    std::min(value_str.find_first_not_of("0+-"), value_str.length());

	// If no dot, dot would be at end.
	const size_type limit_dot =
	    std::min(limit_str.find('.', limit_start), limit_str.length());
	const size_type value_dot =
	    std::min(value_str.find('.', value_start), value_str.length());

	// Compare length after leading zeros until dot: if less than limit_str,
	// value is not larger.
	if (value_dot - value_start < limit_dot - limit_start) {
		return true;
	}

	// After sign and zeros, if value_str <= limit_str, value is not larger.
	// '.' compares as less than any digit.
	if (value_start < value_str.length() && limit_start < limit_str.length()
	    && value_str.compare(
	           value_start, std::string::npos, limit_str, limit_start)
	           <= 0) {
		return true;
	}

	// The part of value_str that is longer than limit_str must only be 0s.
	const size_type value_extra =
	    value_dot + std::min(limit_str.length() - limit_dot, size_type(1));
	return value_str.find_first_not_of('0', value_extra) == std::string::npos;
}
