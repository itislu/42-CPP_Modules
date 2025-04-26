// NOLINTBEGIN(readability-magic-numbers)

#include "iter.hpp"
#include <cctype>
#include <cstddef>
#include <iostream>
#include <string>
#include <typeinfo>

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

template <typename T>
static void print(T& value)
{
	std::cout << value << " ";
}

// template <typename T>
// static void print(const volatile T& value)
// {
// 	std::cout << value << " ";
// }

// template <typename Integral>
// static void modify(Integral& value)
// {
// 	value += 100;
// }

template <typename Integral>
static bool modify(Integral& value)
{
	value += 100;
	std::cout << "Successfully modified" << '\n';
	return true;
}

template <>
bool modify<char>(char& value) { value = std::toupper(value); return true; }

template <typename T, std::size_t N>
void test(T (&array)[N])
{
	(void)array[0];
}

// TODO Check CPP version and conditionally choose which one to compile
// template <typename T>
// void test(T (&array)[])
// {
// 	(void)array[0];
// }

template <typename T>
void test(T& array)
{
	std::cout << typeid(array).name() << '\n';
	(void)array[0];
}

int g[2] = {};

int main()
{
	{
		const std::size_t size = 10;
		const /* volatile */ int array[size] = {};
		
		test(array);
		
		extern int g[];
		test(g);
	}
	{
		const std::size_t size = 10;
		int array[size];

		// NOLINTBEGIN(cppcoreguidelines-pro-bounds-array-to-pointer-decay)
		iter(array, size, toupper);
		iter(array, size, init<int>);
		iter(array, size, print<int>), std::cout << '\n';
		iter(array, size, modify<int>);
		iter(array, size, print<int>), std::cout << '\n';
		// NOLINTEND(cppcoreguidelines-pro-bounds-array-to-pointer-decay)
	}
	{
		const std::size_t size = 10;
		int* array = new int[size];

		iter(array, size, init<int>);
		iter(array, size, print<int>), std::cout << '\n';
		iter(array, size, modify<int>);
		iter(array, size, print<int>), std::cout << '\n';

		delete[] array;
	}
	{
		const std::size_t size = 10;
		std::string array(size, 'a');

		iter(array, size, init<char>);
		iter(array, size, print<char>), std::cout << '\n';
		iter(array, size, modify<char>);
		iter(array, size, print<char>), std::cout << '\n';
	}
}

// NOLINTEND(readability-magic-numbers)
