#include "easyfind.hpp"
#include "libftpp/format.hpp"
#include "libftpp/functional.hpp"
#include "libftpp/random.hpp"
#include "libftpp/string.hpp"
#include <algorithm>
#include <cstdlib>
#include <deque>
#include <iostream>
#include <iterator>
#include <list>
#include <string>
#include <vector>

template <typename C>
static void test_find_shuffled();
template <typename C>
static void find_shuffled(std::size_t size, std::size_t target_amount);
template <typename C>
static void print_container(const C& container);
static void print_seperator(const std::string& title);

int main()
{
	print_seperator("Vector");
	test_find_shuffled<std::vector<char> >();

	print_seperator("Deque");
	test_find_shuffled<std::deque<char> >();

	print_seperator("List");
	test_find_shuffled<std::list<char> >();
}

template <typename C>
static void test_find_shuffled()
{
	find_shuffled<C>(64, 1);
	find_shuffled<C>(64, 2);
	find_shuffled<C>(64, 16);
	find_shuffled<C>(64, 63);
	find_shuffled<C>(64, 64);
	find_shuffled<C>(64, 0);
	find_shuffled<C>(0, 0);
}

template <typename C>
static void find_shuffled(std::size_t size, std::size_t target_amount)
{
	std::cout << BOLD("Size: " + ft::to_string(size)
	                  + ", Targets: " + ft::to_string(target_amount))
	          << '\n';
	if (size < target_amount) {
		std::cerr << ft::log::error("Invalid arguments to find_shuffled()")
		          << "\n\n";
		return;
	}

	const char dflt = '.';
	const char target = 'O';
	const char found = 'X';

	C container;
	{
		// Shuffle
		std::vector<typename C::value_type> vec(size - target_amount, dflt);
		vec.insert(vec.end(), target_amount, target);
		std::srand(ft::urandom<unsigned int>());
		std::random_shuffle(vec.begin(), vec.end());
		container.assign(vec.begin(), vec.end());
	}

	print_container(container);
	const typename C::iterator hit = easyfind(container, target);
	if (hit == container.end()) {
		std::cerr << ft::log::error("Nothing found") << '\n';
	}
	else {
		std::cerr << ft::log::ok(
		    "Found at position "
		    + ft::to_string(std::distance(container.begin(), hit)))
		          << '\n';
		*hit = found;
	}
	print_container(container);
	std::cout << '\n';
}

template <typename C>
static void print_container(const C& container)
{
	std::for_each(container.begin(),
	              container.end(),
	              ft::functional::Print<typename C::value_type>());
	std::cout << '\n';
}

static void print_seperator(const std::string& title)
{
	const unsigned int width = 60;
	const unsigned int padding = 2;

	const unsigned int available = width - title.length() - padding;
	const unsigned int left = available / 2;
	const unsigned int right = available - left;

	std::cout << "\n"
	          << BOLD(std::string(left, '=') + ' ' + title + ' '
	                  + std::string(right, '='))
	          << "\n\n";
}
