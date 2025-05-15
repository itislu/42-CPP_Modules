#include "easyfind.hpp"
#include "libftpp/format.hpp"
#include "libftpp/numeric.hpp"
#include "libftpp/random.hpp"
#include "libftpp/string.hpp"
#include "libftpp/type_traits.hpp"
#include <algorithm>
#include <cstdlib>
#include <deque>
#include <exception>
#include <iostream>
#include <iterator>
#include <list>
#include <string>
#include <vector>

#ifndef DEFAULT_CONTAINER_SIZE
#	define DEFAULT_CONTAINER_SIZE 64
#endif

template <typename C>
static void test_find_shuffled(std::size_t size);
template <typename C>
static void find_shuffled(std::size_t size, std::size_t target_amount);
template <typename C>
static void print_container(const C& container);
static void print_seperator(const std::string& title);

// NOLINTBEGIN(cppcoreguidelines-pro-bounds-pointer-arithmetic)
int main(int argc, char* argv[])
try {
	if (argc > 2) {
		std::cerr << "Usage: " << argv[0]
		          << " [container_size=" << DEFAULT_CONTAINER_SIZE << "]"
		          << '\n';
		return 1;
	}

	const std::size_t size = argc == 2 ? ft::from_string<std::size_t>(argv[1])
	                                   : DEFAULT_CONTAINER_SIZE;

	print_seperator("Vector of char");
	test_find_shuffled<std::vector<char> >(size);

	print_seperator("Deque of int");
	test_find_shuffled<std::deque<int> >(size);

	print_seperator("List of char");
	test_find_shuffled<std::list<char> >(size);
}
catch (const std::exception& e) {
	std::cerr << ft::log::error(BOLD("Exception: ") + e.what()) << '\n';
	return 2;
}
// NOLINTEND(cppcoreguidelines-pro-bounds-pointer-arithmetic)

template <typename C>
static void test_find_shuffled(std::size_t size)
{
	find_shuffled<C>(size, 1);
	find_shuffled<C>(size, 2);
	find_shuffled<C>(size, size / 4);
	find_shuffled<C>(size, ft::sub_sat<std::size_t>(size, 1));
	find_shuffled<C>(size, size);
	find_shuffled<C>(size, 0);
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

	typedef typename C::value_type Elem;
	const Elem dflt = ft::is_same<Elem, char>::value ? '.' : 0;
	const Elem target = ft::is_same<Elem, char>::value ? 'O' : 1;
	const Elem found = ft::is_same<Elem, char>::value ? 'X' : 2;

	C container;
	{
		// Shuffle
		std::vector<Elem> vec(size - target_amount, dflt);
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
	std::copy(container.begin(),
	          container.end(),
	          std::ostream_iterator<typename C::value_type>(std::cout));
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
