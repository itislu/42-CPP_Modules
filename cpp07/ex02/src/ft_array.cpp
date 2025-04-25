#include "libftpp/Array.hpp"
#include "libftpp/Optional.hpp"
#include "libftpp/algorithm.hpp"
#include "libftpp/format.hpp"
#include "libftpp/string.hpp"
#include <cctype>
#include <cstddef>
#include <exception>
#include <iostream>
#include <string>

extern void print_seperator(const std::string& title);
static void test_aggregate_initialization();
static void test_iterators();
static void test_fill();
static void test_comparison();
static void test_to_array();
static void test_access();
static void test_zero_sized();
template <typename T, std::size_t N>
static void print_array(const ft::Array<T, N>& array,
                        const ft::Optional<std::string>& title = ft::nullopt);

extern void ft_array()
{
	test_aggregate_initialization();
	test_iterators();
	test_fill();
	test_comparison();
	test_to_array();
	test_access();
	test_zero_sized();
}

static void test_aggregate_initialization()
{
	print_seperator("Aggregate Initialization");

	const ft::Array<int, 3> dflt = {};
	print_array(dflt, "default");
	std::cout << '\n';

	const ft::Array<int, 3> matching = {1, 2, 3};
	print_array(matching, "matching");
	std::cout << '\n';

	const ft::Array<int, 5> larger = {1, 2, 3};
	print_array(larger, "larger");
}

static void test_iterators()
{
	print_seperator("Iterators");

	ft::Array<char, 3> array = {'a', 'b', 'c'};

	print_array(array, "Before transform"), std::cout << '\n';
	ft::transform(array.begin(), array.end(), array.begin(), toupper);
	print_array(array, "After transform");
	std::cout << '\n';

	std::cout << BOLD("Reverse:") << '\n';
	for (ft::Array<char, 3>::reverse_iterator it = array.rbegin();
	     it != array.rend();
	     ++it) {
		std::cout << *it << '\n';
	}
}

static void test_fill()
{
	print_seperator("Fill");

	ft::Array<std::string, 3> array = {};

	print_array(array, "Before fill"), std::cout << '\n';
	array.fill("filled");
	print_array(array, "After fill");
}

static void test_comparison()
{
	print_seperator("Comparison");
	std::cout.setf(std::ios::boolalpha);

	const ft::Array<std::string, 3> array1 = {"abc", "abc", "abc"};

	std::cout << BOLD("Copy:") << '\n';
	ft::Array<std::string, 3> array2 = array1;
	std::cout << (array1 == array2 ? "Equal" : "Not equal") << '\n';

	std::cout << '\n' << BOLD("Modified:") << '\n';
	array2[1] = "aac";
	std::cout << (array1 == array2 ? "Equal" : "Not equal") << '\n';

	std::cout << '\n';
	print_array(array1, "array1");
	std::cout << '\n';
	print_array(array2, "array2");

	std::cout << '\n' << BOLD("Less:") << '\n';
	if (array1 < array2) {
		std::cout << "array1";
	}
	else if (array2 < array1) {
		std::cout << "array2";
	}
	else {
		std::cout << "Equal";
	}
	std::cout << '\n';

	std::cout.unsetf(std::ios::boolalpha);
}

static void test_to_array()
{
	print_seperator("to_array()");

	int c_array[4] = {1, 2, 3, 4};
	const ft::Array<int, 4> int_array = ft::to_array(c_array);
	print_array(int_array, "From C-array"), std::cout << '\n';

	const ft::Array<char, 4> char_array = ft::to_array("abc");
	print_array(char_array, "From string literal"), std::cout << '\n';

	std::cout << BOLD("On \"abcde\" literal:") << '\n';
	std::cout << "index 3: " << ft::to_array("abcde").at(3) << '\n';
	std::cout << "size: " << ft::to_array("abcde").size() << '\n';
}

static void test_access()
{
	print_seperator("Access");

	ft::Array<unsigned, 3> array = {0, 1, 2};

	std::cout << BOLD("operator[]:") << '\n';
	std::cout << ft::log::ok(array[2]) << '\n';
	// array[10]; // unchecked

	std::cout << '\n' << BOLD("at():") << '\n';
	try {
		std::cout << ft::log::ok(array.at(2)) << '\n';
		array.at(10);
	}
	catch (const std::exception& e) {
		std::cerr << ft::log::error(e.what()) << '\n';
	}

	std::cout << '\n' << BOLD("ft::get<>():") << '\n';
	std::cout << ft::log::ok(ft::get<2>(array)) << '\n';
	// ft::get<10>(array); // compile-time check
}

static void test_zero_sized()
{
	print_seperator("Zero-sized");
	std::cout.setf(std::ios::boolalpha);

	ft::Array<int, 0> array = {};
	print_array(array, "zero-sized");

	std::cout << '\n' << BOLD("size:") << '\n';
	std::cout << array.size() << '\n';

	std::cout << '\n' << BOLD("empty:") << '\n';
	std::cout << array.empty() << '\n';

	std::cout << '\n' << BOLD("begin() == end():") << '\n';
	std::cout << (array.begin() == array.end()) << '\n';

	std::cout << '\n' << BOLD("at(0):") << '\n';
	try {
		std::cout << ft::log::ok(array.at(0)) << '\n';
	}
	catch (const std::exception& e) {
		std::cerr << ft::log::error(e.what()) << '\n';
	}

	// array[0]; // does not compile
	// array.front(); // does not compile
	// array.back(); // does not compile

	std::cout << '\n' << BOLD("data:") << '\n';
	std::cout << ft::to_string(array.data()) << '\n';

	std::cout << '\n' << BOLD("fill:") << '\n';
	array.fill(42);
	std::cout << "Does nothing" << '\n';

	std::cout.unsetf(std::ios::boolalpha);
}

template <typename T, std::size_t N>
static void print_array(const ft::Array<T, N>& array,
                        const ft::Optional<std::string>& title)
{
	if (title) {
		std::cout << BOLD(*title + ":") << '\n';
	}
	if (array.empty()) {
		std::cout << "empty array" << '\n';
		return;
	}
	for (unsigned int i = 0; i < array.size(); ++i) {
		std::cout << i << ": " << array.at(i) << '\n';
	}
}
