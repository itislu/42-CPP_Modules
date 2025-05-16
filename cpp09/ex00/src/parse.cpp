#include "parse.hpp"
#include "Date.hpp"
#include "libftpp/Exception.hpp"
#include "libftpp/string.hpp"
#include "libftpp/type_traits.hpp"
#include <ctime>
#include <ios>
#include <string>

template <typename To>
static To parse_field(const std::string& str, const std::string& field_name);

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
	if (amount < 0) {
		throw ft::Exception("Negative query amount");
	}
	if (amount > max_query_amount) {
		throw ft::Exception("Too large query amount");
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
		throw ft::Exception("Excess characters in " + field_name + " field");
	}
	return result;
}
