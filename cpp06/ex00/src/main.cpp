// NOLINTBEGIN(cppcoreguidelines-pro-bounds-pointer-arithmetic)
// NOLINTBEGIN(cppcoreguidelines-pro-bounds-constant-array-index)

#include "ScalarConverter.hpp"
#include "utils/common.hpp"
#include "utils/log.hpp"
#include <iomanip>
#include <iostream>

static void test_array(unsigned int amount, const char* array[]);

int main(int argc, const char* argv[])
{
	const char* tests[] = {"0", "nan", "42.0f", "42f", "42.0"};

	if (argc == 1) {
		std::cerr << utils::log::info("Using default test cases.") << '\n';
		test_array(ARRAY_SIZE(tests), tests);
	}
	else {
		test_array(argc - 1, &argv[1]);
	}
}

static void test_array(unsigned int amount, const char* array[])
{
	for (unsigned int i = 0; i < amount; ++i) {
		std::cout.fill('0');
		std::cout << '\n'
		          << "Test " << std::setw(2) << i << ": '" << array[i] << "'"
		          << '\n';
		std::cout.fill(' ');
		ScalarConverter::convert(array[i]);
	}
	std::cout << '\n';
}

// NOLINTEND(cppcoreguidelines-pro-bounds-constant-array-index)
// NOLINTEND(cppcoreguidelines-pro-bounds-pointer-arithmetic)
