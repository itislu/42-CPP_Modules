// NOLINTBEGIN(cppcoreguidelines-pro-bounds-pointer-arithmetic)
// NOLINTBEGIN(readability-magic-numbers)

#include "Array.hpp"
#include "libftpp/format.hpp"
#include <cstddef>
#include <cstdlib>
#include <ctime>
#include <exception>
#include <iostream>
#include <string>

extern void ft_array();
static int test_provided();
static void test_zero_sized();
static void test_assignment();
static void test_const_array();
extern void print_seperator(const std::string& title);

int main(int argc, char* argv[])
try {
	if (argc == 1) {
		test_provided();
		test_zero_sized();
		test_assignment();
		test_const_array();
	}
	else if (argc == 2 && argv[1] == std::string("ft")) {
		ft_array();
	}
	else {
		std::cerr << "Usage: " << argv[0] << " [ft]" << '\n';
		return 1;
	}
}
catch (const std::exception& e) {
	std::cerr << ft::log::error(BOLD("Exception: ") + e.what()) << '\n';
	return 2;
}

// clang-format off
// NOLINTBEGIN
#define MAX_VAL 750
static int test_provided()
{
	print_seperator("Provided Test Cases");

    Array<int> numbers(MAX_VAL);
    int* mirror = new int[MAX_VAL];
    srand(time(NULL));
    for (int i = 0; i < MAX_VAL; i++)
    {
        const int value = rand();
        numbers[i] = value;
        mirror[i] = value;
    }
    //SCOPE
    {
        Array<int> tmp = numbers;
        Array<int> test(tmp);
    }

    for (int i = 0; i < MAX_VAL; i++)
    {
        if (mirror[i] != numbers[i])
        {
            std::cerr << "didn't save the same value!!" << std::endl;
            return 1;
        }
    }
    try
    {
        numbers[-2] = 0;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    try
    {
        numbers[MAX_VAL] = 0;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }

    for (int i = 0; i < MAX_VAL; i++)
    {
        numbers[i] = rand();
    }
    delete [] mirror;//
    return 0;
}
// NOLINTEND
// clang-format on

static void test_zero_sized()
{
	print_seperator("Zero-sized Array");

	Array<std::string> array(0);

	std::cout << ft::log::info(BOLD("Print array[0]:")) << '\n';
	try {
		std::cout << ft::log::ok(array[0]) << '\n';
	}
	catch (const std::exception& e) {
		std::cerr << ft::log::error(e.what()) << '\n';
	}

	std::cout << '\n' << ft::log::info(BOLD("Assign to array[0]:")) << '\n';
	try {
		array[0] = "";
		std::cout << ft::log::ok("Assignment successful") << '\n';
	}
	catch (const std::exception& e) {
		std::cerr << ft::log::error(e.what()) << '\n';
	}

	std::cout << '\n' << ft::log::info(BOLD("Size of array[0]:")) << '\n';
	std::cout << ft::log::ok(array.size()) << '\n';
}

static void test_assignment()
{
	print_seperator("Array Assignment");

	Array<char> array1;
	Array<char> array2(3);
	array2[0] = 'a', array2[1] = 'b', array2[2] = 'c';

	std::cout << ft::log::info(BOLD("Before assignment")) << '\n';
	std::cout << '\n' << BOLD("array1:") << '\n' << array1;
	std::cout << '\n' << BOLD("array2:") << '\n' << array2;

	array1 = array2;

	std::cout << '\n' << ft::log::info(BOLD("After assignment")) << '\n';
	std::cout << '\n' << BOLD("array1:") << '\n' << array1;
	std::cout << '\n' << BOLD("array2:") << '\n' << array2;
}

static void test_const_array()
{
	print_seperator("Const Array");

	Array<float> array(1);
	array[0] = 42.42;

	const Array<float> const_array_empty(1);
	const Array<float> const_array_copy(array);

	std::cout << BOLD("array:") << '\n' << array;
	std::cout << '\n'
	          << BOLD("const_array_empty:") << '\n'
	          << const_array_empty;
	std::cout << '\n' << BOLD("const_array_copy:") << '\n' << const_array_copy;
}

extern void print_seperator(const std::string& title)
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
// NOLINTEND(cppcoreguidelines-pro-bounds-pointer-arithmetic)
