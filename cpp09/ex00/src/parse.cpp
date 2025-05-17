#include "parse.hpp"
#include "Date.hpp"
#include "libftpp/Exception.hpp"
#include "libftpp/string.hpp"
#include "libftpp/type_traits.hpp"
#include <cmath>
#include <ctime>
#include <ios>
#include <string>

template <typename To>
static To parse_field(const std::string& str, const std::string& field_name);
static bool is_too_large(const std::string& str, float amount, float max);

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
	return parse_field<double>(str, "exchange rate");
}
catch (ft::Exception& e) {
	e.set_who("Rate");
	throw;
}

float parse_amount(const std::string& str, float max_query_amount)
try {
	const float amount = parse_field<float>(str, "query amount");
	if (std::signbit(amount) != 0) {
		throw ft::Exception("negative query amount");
	}
	if (is_too_large(str, amount, max_query_amount)) {
		throw ft::Exception("too large query amount");
	}
	return amount;
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

static bool is_too_large(const std::string& str, float amount, float max)
{
	if (amount < max) {
		return false;
	}
	if (amount > max) {
		return true;
	}
	const std::string::size_type pos = str.find('.');
	return pos != std::string::npos
	       && str.find_first_not_of('0', pos + 1) != std::string::npos;
}
