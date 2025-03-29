#pragma once

#include <string>

class ScalarConverter {
public:
	static void convert(const std::string& str);

private:
	ScalarConverter();
	ScalarConverter(const ScalarConverter& other);
	~ScalarConverter();
	ScalarConverter& operator=(ScalarConverter other);
};
