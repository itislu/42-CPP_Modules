#include "ScalarConverter.hpp"
#include "utils/algorithm.hpp"
#include "utils/string.hpp"
#include <cctype>
#include <climits>
#include <cmath>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>

const char* const ScalarConverter::_impossible_msg = "impossible";
const char* const ScalarConverter::_non_displayable_msg = "Non displayable";

template <typename T>
std::string format_int(T nbr)
{
	if (std::isnan(nbr) || std::isinf(nbr) || nbr > INT_MAX || nbr < INT_MIN) {
		return "impossible";
	}
	int i = static_cast<int>(nbr);
	return utils::string::to_string(i);
}

template <typename To, typename From>
To convert(From nbr)
{
	if (std::isnan(nbr)) {
		if (!std::numeric_limits<To>::is_iec559) {

		}
	}
	else if (std::isinf(nbr)) {
		if (!std::numeric_limits<To>::is_iec559) {

		}
	}
	else if (nbr > std::numeric_limits<To>::max() || nbr < std::numeric_limits<To>::min()) {

	}
	return static_cast<To>(nbr);
}

void ScalarConverter::convert(const std::string& str)
{
	char c;
	int i;
	float f;
	double d;

	try {
		switch (const Type type = _detect_type(str)) {
		case Char:
			c = utils::string::from_string<char>(str);
			break;
		case Int:
			i = utils::string::from_string<int>(str);
			break;
		case Float:
			f = utils::string::from_string<float>(str);
			break;
		case Double:
			d = utils::string::from_string<double>(str);
			break;
		}
	}
	catch (declaration) {
	}

	const char c = _convert_char(str);
	const int i = _convert_int(str);
	// const float f = _convert_float(str);
	// const double d = _convert_double(str);

	std::cout << "  " << std::setw(8) << "char: " << c << '\n';
	std::cout << "  " << std::setw(8) << "int: " << i << '\n';
	// std::cout << "  " << std::setw(8) << "float: " << f << '\n';
	// std::cout << "  " << std::setw(8) << "double: " << d << '\n';
}

ScalarConverter::Type ScalarConverter::_detect_type(const std::string& str)
{
	if (str.empty() || (str.length() == 1 && !std::isdigit(str[0]))) {
		return Char;
	}

	const std::string nbrstr(
	    str.substr((str[0] == '-' || str[0] == '+') ? 1 : 0));

	// Check if str consists only of digits, except for sign at index 0
	if (nbrstr.find_first_not_of("0123456789") == std::string::npos) {
		return Int;
	}

	if ((nbrstr.find_first_not_of("0123456789.f") == std::string::npos
	     && utils::algorithm::count(nbrstr.begin(), nbrstr.end(), '.') <= 1
	     && utils::algorithm::count(nbrstr.begin(), nbrstr.end(), 'f') == 1)
	    || nbrstr == "nanf" || nbrstr == "inff") {
		return Float;
	}

	if ((nbrstr.find_first_not_of("0123456789.") == std::string::npos
	     && utils::algorithm::count(nbrstr.begin(), nbrstr.end(), '.') <= 1)
	    || nbrstr == "nan" || nbrstr == "inf") {
		return Double;
	}
}

char ScalarConverter::_convert_char(const std::string& str)
{
	if (str.length() != 1) {
		// throw
		return _impossible_msg;
	}
	return str;
}

int ScalarConverter::_convert_int(const std::string& str)
{
	std::stringstream ss(str);
	int i = 0;

	if (!(ss >> i)) {
		return _impossible_msg;
	}
	const std::string i_str = utils::string::to_string(i);
	if (i_str.length() != str.length()) {
		return _impossible_msg;
	}
	return i_str;
}

// float ScalarConverter::_convert_float(const std::string& str)
// {
// 	(void)str;
// 	return "not implemented";
// }

// double ScalarConverter::_convert_double(const std::string& str)
// {
// 	(void)str;
// 	return "not implemented";
// }

// template <typename T>
// std::string convert_nbr(const std::string& str)
// {
// 	std::stringstream ss(str);
// 	T nbr;

// 	if (!(ss >> nbr)) {
// 		std::cerr << "stringstream failed" << '\n';
// 		return "impossible";
// 	}
// 	const std::string nbr_str = utils::string::to_string(nbr);
// 	if (nbr_str.length() != str.length()) {
// 		std::cerr << "nbr_str(" << nbr_str.length() << "): \"" << nbr_str
// 		          << "\" vs " << "str(" << str.length() << "): \"" << str << '"'
// 		          << '\n';
// 		return "impossible";
// 	}
// 	return nbr_str;
// }
