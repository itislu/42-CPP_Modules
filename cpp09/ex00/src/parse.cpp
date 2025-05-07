#include "parse.hpp"
#include "Date.hpp"
#include "libftpp/string.hpp"
#include "libftpp/type_traits.hpp"
#include <ctime>
#include <ios>
#include <stdexcept>
#include <string>

template <typename To>
static To parse_field(const std::string& str, const std::string& field_name);

std::time_t parse_date(const std::string& str)
{
	return parse_field<std::time_t>(str, "date");
}

double parse_rate(const std::string& str)
{
	return parse_field<double>(str, "exchange rate");
}

float parse_amount(const std::string& str, float max_query_amount)
{
	const float amount = parse_field<float>(str, "query amount");
	if (amount < 0) {
		throw std::invalid_argument("Negative query amount");
	}
	if (amount > max_query_amount) {
		throw std::invalid_argument("Too large query amount");
	}
	return amount;
}

template <typename To>
static To parse_field(const std::string& str, const std::string& field_name)
try {
	if (str.empty()) {
		throw std::invalid_argument("Empty " + field_name + " field");
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
		throw std::invalid_argument("Excess characters in " + field_name
		                            + " field");
	}
	return result;
}
catch (const ft::FromStringRangeException& e) {
	throw std::out_of_range(e.what());
}
catch (const ft::FromStringInvalidException& e) {
	throw std::invalid_argument(e.what());
}
