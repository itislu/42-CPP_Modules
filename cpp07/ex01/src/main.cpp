// NOLINTBEGIN(readability-magic-numbers)

#include "iter.hpp"
#include "libftpp/Array.hpp"
#include "libftpp/format.hpp"
#include "libftpp/random.hpp"
#include <cctype>
#include <cstddef>
#include <exception>
#include <iostream>
#include <string>

static void test_array_known_bound();
static void test_array_unknown_bound();
static void test_dynamic_array();
static void test_complex_types();
static void print_seperator(const std::string& title);

int main()
try {
	test_array_known_bound();
	test_array_unknown_bound();
	test_dynamic_array();
	test_complex_types();
}
catch (const std::exception& e) {
	std::cerr << ft::log::error(BOLD("Exception: ") + e.what()) << '\n';
	return 1;
}

template <typename Integral>
static void init(Integral& value)
{
	static Integral count = 0;
	value = count++;
}

template <>
void init<char>(char& value)
{
	static char alpha = 'a';
	value = alpha++;
	if (alpha > 'z') {
		alpha = 'a';
	}
}

template <>
void init<std::string>(std::string& value)
{
	std::string tmp(5, '.');
	tmp[ft::urandom<unsigned>() % tmp.size()] = 'O';
	value = tmp;
}

template <typename T>
static void print(const T& value)
{
	std::cout << value << " ";
}

template <typename Integral>
static void modify(Integral& value)
{
	value += 100;
}

template <>
void modify<char>(char& value)
{
	value = static_cast<char>(std::toupper(value));
}

template <typename Integral>
static bool modify(Integral& value)
{
	value += 100;
	std::cout << "Successfully modified" << '\n';
	return true;
}

template <>
bool modify<std::string>(std::string& value)
{
	const std::string::size_type pos = value.find('O');
	if (pos == std::string::npos) {
		std::cout << "'O' not found" << '\n';
		return false;
	}
	value[pos] = 'X';
	std::cout << "Successfully replaced 'O' with 'X'" << '\n';
	return true;
}

static void test_array_known_bound()
{
	{
		print_seperator("Array of known bound");

		const std::size_t size = 10;
		int array[size];

		iter(array, size, init<int>);
		iter(array, size, print<int>), std::cout << '\n';
		iter<bool>(array, size, modify<int>);
		iter(array, size, print<int>), std::cout << '\n';
	}
	{
		print_seperator("Array of known bound smaller than size argument");

		const std::size_t size = 10;
		int array[size];

		iter(array, size * 2, init<int>);
		iter(array, size * 2, print<int>), std::cout << '\n';
		iter<bool>(array, size * 2, modify<int>);
		iter(array, size * 2, print<int>), std::cout << '\n';
	}
	{
		print_seperator("Array of known bound larger than size argument");

		const std::size_t size = 10;
		int array[size];

		iter(array, size / 2, init<int>);
		iter(array, size / 2, print<int>), std::cout << '\n';
		iter<bool>(array, size / 2, modify<int>);
		iter(array, size / 2, print<int>), std::cout << '\n';
	}
	{
		print_seperator("Array of known bound of std::string");

		const std::size_t size = 10;
		std::string array[size];

		iter(array, size, init<std::string>);
		iter(array, size, print<std::string>), std::cout << '\n';
		iter<bool>(array, size, modify<std::string>);
		iter(array, size, print<std::string>), std::cout << '\n';
	}
	{
		print_seperator("Const array of known bound");

		const std::size_t size = 10;
		const int array[size] = {1, 2, 3};

		iter(array, size, print<int>), std::cout << '\n';
	}
	{
		print_seperator("Volatile array of known bound");

		const std::size_t size = 10;
		volatile int array[size];

		iter(array, size, init<volatile int>);
		iter(array, size, print<volatile int>), std::cout << '\n';
		iter<void>(array, size, modify<volatile int>);
		iter(array, size, print<volatile int>), std::cout << '\n';
	}
	{
		print_seperator("Const volatile array of known bound");

		const std::size_t size = 3;
		const volatile int array[size] = {1, 2, 3};

		iter(array, size, print<volatile int>), std::cout << '\n';
	}
}

const size_t unknown_bound_size = 5;
int unknown_bound[unknown_bound_size] = {};                   // NOLINT
const int const_unknown_bound[unknown_bound_size] = {};       // NOLINT
volatile int volatile_unknown_bound[unknown_bound_size] = {}; // NOLINT
const volatile int cv_unknown_bound[unknown_bound_size] = {}; // NOLINT

static void test_array_unknown_bound()
{
	{
		print_seperator("Array of unknown bound");

		extern int unknown_bound[]; // NOLINT

		iter(unknown_bound, unknown_bound_size, init<int>);
		iter(unknown_bound, unknown_bound_size, print<int>), std::cout << '\n';
		iter<void>(unknown_bound, unknown_bound_size, modify<int>);
		iter(unknown_bound, unknown_bound_size, print<int>), std::cout << '\n';
	}
	{
		print_seperator("Const array of unknown bound");

		extern const int const_unknown_bound[]; // NOLINT

		iter(const_unknown_bound, unknown_bound_size, print<int>),
		    std::cout << '\n';
	}
	{
		print_seperator("Volatile array of unknown bound");

		extern volatile int volatile_unknown_bound[]; // NOLINT

		iter(volatile_unknown_bound, unknown_bound_size, init<volatile int>);
		iter(volatile_unknown_bound, unknown_bound_size, print<volatile int>),
		    std::cout << '\n';
		iter<void>(
		    volatile_unknown_bound, unknown_bound_size, modify<volatile int>);
		iter(volatile_unknown_bound, unknown_bound_size, print<volatile int>),
		    std::cout << '\n';
	}
	{
		print_seperator("Const volatile array of unknown bound");

		extern const volatile int cv_unknown_bound[]; // NOLINT

		iter(cv_unknown_bound, unknown_bound_size, print<volatile int>),
		    std::cout << '\n';
	}
}

static void test_dynamic_array()
{
	{
		print_seperator("Dynamic array");

		const std::size_t size = 10;
		int* array = new int[size];

		iter(array, size, init<int>);
		iter(array, size, print<int>), std::cout << '\n';
		iter<void>(array, size, modify<int>);
		iter(array, size, print<int>), std::cout << '\n';

		delete[] array;
	}
	{
		print_seperator("Dynamic array pointer to const");

		const std::size_t size = 10;
		int* array = new int[size];
		const int* const_array = array;

		iter(array, size, init<int>);
		iter(const_array, size, print<int>), std::cout << '\n';
		iter<void>(array, size, modify<int>);
		iter(const_array, size, print<int>), std::cout << '\n';

		delete[] array;
	}
	{
		print_seperator("Dynamic array const pointer");

		const std::size_t size = 10;
		int* const array = new int[size];

		iter(array, size, init<int>);
		iter(array, size, print<int>), std::cout << '\n';
		iter<void>(array, size, modify<int>);
		iter(array, size, print<int>), std::cout << '\n';

		delete[] array;
	}
	{
		print_seperator("Dynamic array pointer to volatile");

		const std::size_t size = 10;
		volatile int* array = new int[size];

		iter(array, size, init<volatile int>);
		iter(array, size, print<volatile int>), std::cout << '\n';
		iter<void>(array, size, modify<volatile int>);
		iter(array, size, print<volatile int>), std::cout << '\n';

		delete[] array;
	}
	{
		print_seperator("NULL pointer");

		int* array = NULL;

		iter(array, 0, init<int>);
		iter(array, 1, print<int>);
		iter<void>(array, 2, modify<int>);
		iter(array, 3, print<int>);
	}
}

static void test_complex_types()
{
	{
		print_seperator("std::string");

		const std::size_t size = 10;
		std::string array(size, 'a');

		iter(array, size, init<char>);
		iter(array, size, print<char>), std::cout << '\n';
		iter<void>(array, size, modify<char>);
		iter(array, size, print<char>), std::cout << '\n';
	}
	{
		print_seperator("ft::Array");

		const std::size_t size = 10;
		ft::Array<char, size> array = {};

		iter(array, size, init<char>);
		iter(array, size, print<char>), std::cout << '\n';
		iter<void>(array, size, modify<char>);
		iter(array, size, print<char>), std::cout << '\n';
	}
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
	          << "\n\n";
}

// NOLINTEND(readability-magic-numbers)
