#pragma once

#include <string>

class ScalarConverter {
public:
	static void convert(const std::string& str);

private:
	enum Type {
		Char,
		Int,
		Float,
		Double
	};

	static Type _detect_type(const std::string& str);

	// static char _convert_char(const std::string& str);
	// static int _convert_int(const std::string& str);
	// // static float _convert_float(const std::string& str);
	// // static double _convert_double(const std::string& str);
	// static bool _is_char(const std::string& str);
	// static bool _is_int(const std::string& str);
	// static bool _is_float(const std::string& str);
	// static bool _is_double(const std::string& str);

	static const char* const _impossible_msg;
	static const char* const _non_displayable_msg;

	ScalarConverter();
	ScalarConverter(const ScalarConverter& other);
	~ScalarConverter();
	ScalarConverter& operator=(ScalarConverter other);
};
