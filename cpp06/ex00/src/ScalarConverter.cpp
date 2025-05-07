// NOLINTBEGIN(cppcoreguidelines-pro-bounds-constant-array-index)
// NOLINTBEGIN(readability-implicit-bool-conversion)

#include "ScalarConverter.hpp"
#include "libftpp/Expected.hpp"
#include "libftpp/Optional.hpp"
#include "libftpp/algorithm.hpp"
#include "libftpp/format.hpp"
#include "libftpp/numeric.hpp"
#include "libftpp/string.hpp"
#include <cctype>
#include <iomanip>
#include <iostream>
#include <limits>
#include <new>
#include <sstream>
#include <string>

enum Type {
	Char,
	Int,
	Float,
	Double
};

static const char* const impossible_msg = "impossible";
static const char* const non_displayable_msg = "Non displayable";

static ft::Optional<Type> detect_type(const std::string& str);
static ft::Optional<Type> detect_type_experimental(const std::string& str);
template <typename To, typename From>
static ft::Expected<To, std::string> do_convert(From from);
static void display(const ft::Expected<char, std::string>& c);
static void display(const ft::Expected<int, std::string>& i);
static void display(const ft::Expected<float, std::string>& f);
static void display(const ft::Expected<double, std::string>& d);
template <typename Fp>
static std::string format_floating_point(Fp fp);
static std::string format_floating_point(float f);

void ScalarConverter::convert(const std::string& str)
{
	const std::string type_strings[] = {"char", "int", "float", "double"};

	const ft::Optional<Type> type = detect_type(str);
	if (!type.has_value()) {
		std::cerr << ft::log::error(
		    "Neither char, int, float nor double detected.")
		          << '\n';
		return;
	}

	ft::Expected<char, std::string> c;
	ft::Expected<int, std::string> i;
	ft::Expected<float, std::string> f;
	ft::Expected<double, std::string> d;
	try {
		switch (*type) {
		case Char:
			c = ft::from_string<char>(str);
			i = do_convert<int>(*c);
			f = do_convert<float>(*c);
			d = do_convert<double>(*c);
			break;
		case Int:
			i = ft::from_string<int>(str);
			c = do_convert<char>(*i);
			f = do_convert<float>(*i);
			d = do_convert<double>(*i);
			break;
		case Float:
			f = ft::from_string<float>(str);
			c = do_convert<char>(*f);
			i = do_convert<int>(*f);
			d = do_convert<double>(*f);
			break;
		case Double:
			d = ft::from_string<double>(str);
			c = do_convert<char>(*d);
			i = do_convert<int>(*d);
			f = do_convert<float>(*d);
			break;
		}
	}
	catch (const ft::FromStringRangeException& e) {
		std::cerr << ft::log::error(
		    type_strings[*type]
		    + " detected, but argument would exceed the type's range")
		          << '\n';
		return;
	}

	std::cerr << ft::log::info("Detected type: " + type_strings[*type]) << '\n';
	display(c);
	display(i);
	display(f);
	display(d);
}

static ft::Optional<Type> detect_type(const std::string& str)
{
	if (str.empty()) {
		return ft::nullopt;
	}

	// Single character, except digits
	if (str.length() == 1 && !std::isdigit(str[0])) {
		return Char;
	}

	// Skip sign at index 0 and make lowercase
	std::string nbrstr(str.substr((str[0] == '-' || str[0] == '+') ? 1 : 0));
	ft::transform(nbrstr.begin(), nbrstr.end(), nbrstr.begin(), tolower);

	// Digits only
	if (nbrstr.find_first_not_of("0123456789") == std::string::npos) {
		return Int;
	}

	// Allowed: 1.0f, .0f, 1.f
	// Not allowed: .f, 1f
	if ((ft::ends_with(nbrstr, 'f')
	     && nbrstr.find_first_of("0123456789") != std::string::npos
	     && nbrstr.find_first_not_of("0123456789.f") == std::string::npos
	     && ft::count(nbrstr.begin(), nbrstr.end(), '.') == 1
	     && ft::count(nbrstr.begin(), nbrstr.end(), 'f') == 1)
	    || nbrstr == "nanf" || nbrstr == "inff") {
		return Float;
	}

	// Allowed: 1.0, .0, 1.
	if ((nbrstr.find_first_of("0123456789") != std::string::npos
	     && nbrstr.find_first_not_of("0123456789.") == std::string::npos
	     && ft::count(nbrstr.begin(), nbrstr.end(), '.') == 1)
	    || nbrstr == "nan" || nbrstr == "inf") {
		return Double;
	}

	return detect_type_experimental(str);
}

/**
 * Detection of other bases and scientific notation.
 * Not perfect:
 * - Cannot deal with leading zeros.
 * - Hexadecimal floating-points are not supported.
 * - Scientific notation needs to have a period.
 */
static ft::Optional<Type> detect_type_experimental(const std::string& str)
{
	std::string str_lower(str);
	ft::transform(
	    str_lower.begin(), str_lower.end(), str_lower.begin(), tolower);

	// int in hexadecimal or octal notation
	const ft::Optional<int> maybe_int = ft::from_string<int>(str, std::nothrow);
	if (maybe_int) {
		if (ft::to_string(*maybe_int, std::ios::hex | std::ios::showbase)
		        == str_lower
		    || ft::to_string(*maybe_int, std::ios::oct | std::ios::showbase)
		           == str_lower) {
			return Int;
		}
	}

	// float in scientific notation
	const ft::Optional<float> maybe_float =
	    ft::from_string<float>(str, std::nothrow);
	if (maybe_float) {
		if (ft::to_string(*maybe_float, std::ios::showpoint) + 'f' == str_lower
		    || ft::to_string(*maybe_float,
		                     std::ios::showpoint | std::ios::scientific)
		               + 'f'
		           == str_lower) {
			return Float;
		}
	}

	// double in scientific notation
	const ft::Optional<double> maybe_double =
	    ft::from_string<double>(str, std::nothrow);
	if (maybe_double) {
		if (ft::to_string(*maybe_double, std::ios::showpoint) == str_lower
		    || ft::to_string(*maybe_double,
		                     std::ios::showpoint | std::ios::scientific)
		           == str_lower) {
			return Double;
		}
	}

	return ft::nullopt;
}

template <typename To, typename From>
static ft::Expected<To, std::string> do_convert(From from)
{
	try {
		return ft::numeric_cast<To>(from);
	}
	catch (const ft::NumericCastException&) {
		return ft::Unexpected<std::string>(impossible_msg);
	}
}

static void display(const ft::Expected<char, std::string>& c)
{
	std::cout << "  " << std::setw(8) << "char: ";
	if (!c) {
		std::cout << c.error();
	}
	else if (std::isprint(*c)) {
		std::cout << *c;
	}
	else {
		std::cout << non_displayable_msg;
	}
	std::cout << '\n';
}

static void display(const ft::Expected<int, std::string>& i)
{
	std::cout << "  " << std::setw(8) << "int: ";
	if (!i) {
		std::cout << i.error();
	}
	else {
		std::cout << *i;
	}
	std::cout << '\n';
}

static void display(const ft::Expected<float, std::string>& f)
{
	std::cout << "  " << std::setw(8) << "float: ";
	if (!f) {
		std::cout << f.error();
	}
	else {
		std::cout << format_floating_point(*f);
	}
	std::cout << '\n';
}

static void display(const ft::Expected<double, std::string>& d)
{
	std::cout << "  " << std::setw(8) << "double: ";
	if (!d) {
		std::cout << d.error();
	}
	else {
		std::cout << format_floating_point(*d);
	}
	std::cout << '\n';
}

template <typename Fp>
static std::string format_floating_point(Fp fp)
{
	std::stringstream ss;
	ss << std::setprecision(std::numeric_limits<Fp>::digits10) << std::showpoint
	   << std::fixed << fp;
	std::string str(ss.str());

	/* Trim trailing 0s */

	// No need to trim
	if (*str.rbegin() != '0') {
		return str;
	}
	// Keep at least one 0 after decimal point
	const std::string::size_type first_zero = str.find_last_not_of('0');
	str = str.substr(
	    0, (str[first_zero] == '.' ? first_zero + 1 : first_zero) + 1);
	return str;
}

static std::string format_floating_point(float f)
{
	return format_floating_point<float>(f) + 'f';
}

// NOLINTEND(readability-implicit-bool-conversion)
// NOLINTEND(cppcoreguidelines-pro-bounds-constant-array-index)
