// NOLINTBEGIN(cppcoreguidelines-pro-bounds-pointer-arithmetic)
// NOLINTBEGIN(cppcoreguidelines-pro-bounds-constant-array-index)
// NOLINTBEGIN(cppcoreguidelines-pro-bounds-array-to-pointer-decay)
// NOLINTBEGIN(misc-use-internal-linkage)

#include "ScalarConverter.hpp"
#include "libftpp/common.hpp"
#include "libftpp/string.hpp"
#include <iomanip>
#include <iostream>
#include <limits>
#include <string>

void test_basic_values();
void test_signs();
void test_zeros();
void test_lonely_periods();
void test_special_values();
void test_invalid_formats();
void test_min_max_values();
void test_hex_values();
void test_oct_values();
void test_scientific_notation();
template <typename T>
static void
test_array(T array[], unsigned int amount, const std::string& group_name = "");
static void print_seperator(const std::string& title);

int main(int argc, const char* argv[])
{
	if (argc > 1) {
		test_array(&argv[1], argc - 1);
		return 0;
	}

	print_seperator("DEFAULT TEST CASES");

	test_basic_values();
	test_signs();
	test_zeros();
	test_lonely_periods();
	test_special_values();
	test_invalid_formats();
	test_min_max_values();

	print_seperator("EXPERIMENTAL TEST CASES");

	test_hex_values();
	test_oct_values();
	test_scientific_notation();
}

void test_basic_values()
{
	const std::string basic_values[] = {
	    ft::to_string('\0'),
	    "0",
	    "0.0f",
	    "0.0",
	    " ",
	    "z",
	    "f",
	    "4",
	    "*",
	    "42",
	    "42.0f",
	    "42.F",
	    "42.0F",
	    "0.F",
	    "42.0",
	    "500.",
	    ".",
	    ",",
	    "126",
	    "100000000000000000000000000000000000000.0000000000000000000000000000000000000000000000000000000000000000000009f"};
	test_array(basic_values, ARRAY_SIZE(basic_values), "Basic Values");
}

void test_signs()
{
	const std::string signs[] = {
	    ft::to_string('\0'),
	    "+0",
	    "-0",
	    "+0.0f",
	    "-0.0f",
	    "+0.0",
	    "-0.0",
	    "+",
	    "-",
	    "+4",
	    "-4",
	    "+42",
	    "-42",
	    "+42.0f",
	    "-42.0f",
	    "+42.0",
	    "-42.0",
	    "+500.",
	    "-500.",
	    "+126",
	    "-126",
	    "+100000000000000000000000000000000000000.0000000000000000000000000000000000000000000000000000000000000000000009f",
	    "-100000000000000000000000000000000000000.0000000000000000000000000000000000000000000000000000000000000000000009f"};
	test_array(signs, ARRAY_SIZE(signs), "Plus / Minus Signs");
}

void test_zeros()
{
	const std::string zeros[] = {"0000",
	                             "0000.0000001f",
	                             "000.0",
	                             "000100",
	                             "000100.0",
	                             ".0000",
	                             ".66000000",
	                             "0000.000000f",
	                             "420.00000",
	                             "1000.0000000f",
	                             "100000000000.00000000000000f",
	                             "100000000000.00000000000000"};
	test_array(zeros, ARRAY_SIZE(zeros), "Leading / Trailing Zeros");
}

void test_lonely_periods()
{
	const std::string lonely_periods[] = {
	    ".5", "5.", "5.f", "000100.", ".000100", "+.09f", "-.09f"};
	test_array(lonely_periods, ARRAY_SIZE(lonely_periods), "Lonely Periods");
}

void test_special_values()
{
	const std::string special_values[] = {"nanf",
	                                      "nan",
	                                      "inff",
	                                      "inf",
	                                      "NANF",
	                                      "NAN",
	                                      "INFF",
	                                      "INF",
	                                      "NaNf",
	                                      "NaN",
	                                      "Inff",
	                                      "Inf"};
	test_array(special_values, ARRAY_SIZE(special_values), "Special Values");
}

void test_invalid_formats()
{
	const std::string invalid_formats[] = {
	    "",           "dd",       "ff",    ".f",    "..",     ".0.",
	    "0.0.",       "0.0.f",    "0.0.0", "0..0",  "..0",    "0..",
	    "42sometext", " 42",      "42 ",   "+ 42",  "4 2",    " 4 2 ",
	    "42+",        "42-",      "42.+",  "42.-",  "nanff",  "nanf.",
	    "nan.",       "infff",    "inff.", "inf.",  "inf.f",  "infinity",
	    "INFINITY",   "Infinity", "+ ",    "- ",    "+z",     "-z",
	    "+f",         "-f",       "+.",    "-.",    "+.f",    "-.f",
	    "42f",        "+42f",     "-42f",  "42.ff", "42.0ff", "0.ff",
	    "42.g",       "42.0g",    "0.g",   "++42",  "+-42",   "--42"};
	test_array(invalid_formats, ARRAY_SIZE(invalid_formats), "Invalid Formats");
}

void test_min_max_values()
{
	const std::string min_max[] = {
	    ft::to_string(std::numeric_limits<char>::max()),
	    ft::to_string(static_cast<int>(std::numeric_limits<char>::max()) + 1),
	    ft::to_string(std::numeric_limits<char>::min()),
	    ft::to_string(static_cast<int>(std::numeric_limits<char>::min()) - 1),
	    ft::to_string(std::numeric_limits<int>::max()),
	    ft::to_string(static_cast<long>(std::numeric_limits<int>::max()) + 1),
	    ft::to_string(std::numeric_limits<int>::min()),
	    ft::to_string(static_cast<long>(std::numeric_limits<int>::min()) - 1),
	    ft::to_string(std::numeric_limits<unsigned int>::max()),
	    ft::to_string(
	        static_cast<long>(std::numeric_limits<unsigned int>::max()) + 1),
	    ft::to_string(std::numeric_limits<long>::max()),
	    ft::to_string(std::numeric_limits<long>::min()),
	    ft::to_string(std::numeric_limits<unsigned long>::max()),
	    ft::to_string(std::numeric_limits<float>::max(), std::ios::fixed) + 'f',
	    ft::to_string(-std::numeric_limits<float>::max(), std::ios::fixed)
	        + 'f',
	    ft::to_string(std::numeric_limits<float>::max(), std::ios::fixed),
	    ft::to_string(-std::numeric_limits<float>::max(), std::ios::fixed),
	    ft::to_string(std::numeric_limits<double>::max(), std::ios::fixed),
	    ft::to_string(-std::numeric_limits<double>::max(), std::ios::fixed),
	    ft::to_string(std::numeric_limits<double>::max(), std::ios::fixed)
	        + 'f',
	    ft::to_string(-std::numeric_limits<double>::max(), std::ios::fixed)
	        + 'f',
	    ft::to_string(std::numeric_limits<long double>::max(), std::ios::fixed),
	    ft::to_string(-std::numeric_limits<long double>::max(),
	                  std::ios::fixed),
	    ft::to_string(std::numeric_limits<long double>::max(), std::ios::fixed)
	        + 'f',
	    ft::to_string(-std::numeric_limits<long double>::max(), std::ios::fixed)
	        + 'f'};
	test_array(min_max, ARRAY_SIZE(min_max), "Min/Max Values");
}

void test_hex_values()
{
	const std::string hex_values[] = {
	    "0x100", "0X100", "0x100f", "0X100f", "0x100.", "0X100.", "0x000100"};
	test_array(hex_values, ARRAY_SIZE(hex_values), "Hexadecimal Format");
}

void test_oct_values()
{
	const std::string oct_values[] = {"0100", "00100", "000100"};
	test_array(oct_values, ARRAY_SIZE(oct_values), "Octal Format");
}

void test_scientific_notation()
{
	const std::string scientific_notation[] = {"1.000000e-02",
	                                           "1e-05",
	                                           "1.e-05",
	                                           "1.0e-05",
	                                           "1.00e-05",
	                                           "1.000e-05",
	                                           "1.0000e-05",
	                                           "1.00000e-05",
	                                           "1.000000e-02f",
	                                           "1e-05f",
	                                           "1.e-05f",
	                                           "1.0e-05f",
	                                           "1.000000E-02f",
	                                           "1E-05f"};
	test_array(scientific_notation,
	           ARRAY_SIZE(scientific_notation),
	           "Scientific Notation");
}

template <typename T>
static void
test_array(T array[], unsigned int amount, const std::string& group_name)
{
	if (!group_name.empty()) {
		print_seperator(group_name);
	}

	for (unsigned int i = 0; i < amount; ++i) {
		std::cout.fill('0');
		std::cout << '\n'
		          << "Test " << std::setw(2) << i + 1 << ": \"" << array[i]
		          << "\"" << '\n';
		std::cout.fill(' ');
		ScalarConverter::convert(array[i]);
	}
	std::cout << '\n';
}

static void print_seperator(const std::string& title)
{
	const unsigned int width = 60;
	const unsigned int padding = 2;

	const unsigned int available = width - title.length() - padding;
	const unsigned int left = available / 2;
	const unsigned int right = available - left;

	std::cout << "\n\n"
	          << BOLD(std::string(left, '=') + ' ' + title + ' '
	                  + std::string(right, '='))
	          << '\n';
}

// NOLINTEND(misc-use-internal-linkage)
// NOLINTEND(cppcoreguidelines-pro-bounds-array-to-pointer-decay)
// NOLINTEND(cppcoreguidelines-pro-bounds-constant-array-index)
// NOLINTEND(cppcoreguidelines-pro-bounds-pointer-arithmetic)
