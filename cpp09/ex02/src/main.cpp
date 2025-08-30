#include "PmergeMe.hpp"
#include "libftpp/format.hpp"
#include "libftpp/string.hpp"
#include "merge_insertion_sort.hpp"
#include <algorithm>
#include <deque>
#include <exception>
#include <iostream>
#include <iterator>
#include <list>
#include <locale>
#include <string>
#include <vector>

enum Error {
	UNEXPECTED = -1,
	OK = 0,
	NO_ARGS = 1,
	PARSE_ERROR = 2
};

static void init_user_locale();
static void reset_locale();
template <typename T>
static std::vector<T> parse_args(int argc, char* argv[], bool& quiet);
template <typename C, typename T, typename Sorter>
static void print_before_after_sort(const std::vector<T>& input, Sorter sorter);
template <typename C>
static void print_container(const C& container, const std::string& prefix);
template <typename C, typename T, typename Sorter>
static void
pmerge_me_sort(PmergeMe& pmerge_me, const std::vector<T>& input, Sorter sorter);

struct MergeInsertionSorter {
	static std::string name() { return "merge_insertion_sort()"; }

	template <typename C>
	void operator()(C& container)
	{
		merge_insertion_sort(container);
	}
};

struct MergeInsertionListSorter {
	static std::string name() { return "merge_insertion_sort_list()"; }

	template <typename T>
	void operator()(std::list<T>& lst)
	{
		merge_insertion_sort_list(lst);
	}
};

struct StandardSorter {
	static std::string name() { return "std::sort()"; }

	template <typename C>
	void operator()(C& container)
	{
		std::sort(container.begin(), container.end());
	}
};

struct StandardListSorter {
	static std::string name() { return "std::list::sort()"; }

	template <typename T>
	void operator()(std::list<T>& lst)
	{
		lst.sort();
	}
};

int main(int argc, char* argv[])
try {
	typedef unsigned InputType;

	init_user_locale();

	bool quiet = false;
	const std::vector<InputType> input =
	    parse_args<InputType>(argc, argv, quiet);

	if (!quiet) {
		print_before_after_sort<std::vector<InputType> >(
		    input, MergeInsertionSorter());
	}

	PmergeMe pmerge_me;
	pmerge_me_sort<std::vector<InputType> >(
	    pmerge_me, input, MergeInsertionSorter());
	pmerge_me_sort<std::deque<InputType> >(
	    pmerge_me, input, MergeInsertionSorter());
	pmerge_me_sort<std::list<InputType> >(
	    pmerge_me, input, MergeInsertionSorter());
	pmerge_me_sort<std::list<InputType> >(
	    pmerge_me, input, MergeInsertionListSorter());
	pmerge_me_sort<std::vector<InputType> >(pmerge_me, input, StandardSorter());
	pmerge_me_sort<std::deque<InputType> >(pmerge_me, input, StandardSorter());
	pmerge_me_sort<std::list<InputType> >(
	    pmerge_me, input, StandardListSorter());

	reset_locale();
	return OK;
}
catch (Error e) {
	reset_locale();
	return e;
}
catch (const std::exception& e) {
	std::cerr << ft::log::error(BOLD("Unexpected exception: ") + e.what())
	          << '\n';
	reset_locale();
	return UNEXPECTED;
}

/**
 * Use the user-preferred locale for better formatting of large numbers.
 * On failure, keep the standard locale.
 */
static void init_user_locale()
{
	try {
		std::locale::global(std::locale(""));
	}
	catch (const std::exception& e) {
		std::cerr << ft::log::info("Cannot change locale: ") << e.what()
		          << '\n';
	}
}

/**
 * Avoids "still reachable" valgrind warnings for sake of the subject...
 */
static void reset_locale() { std::locale::global(std::locale::classic()); }

// NOLINTBEGIN(cppcoreguidelines-pro-bounds-pointer-arithmetic): argv
template <typename T>
static std::vector<T> parse_args(int argc, char* argv[], bool& quiet)
{
	int start_idx = 1;

	if (argc > 1
	    && (std::string(argv[1]) == "-n"
	        || std::string(argv[1]) == "--no-before-after")) {
		quiet = true;
		start_idx = 2;
	}
	if (start_idx == argc) {
		std::cerr << "Usage: " << argv[0]
		          << " [-n|--no-before-after] [positive_number] [...]\n";
		throw NO_ARGS; // NOLINT: Exit code.
	}

	std::vector<T> input;
	input.reserve(argc - start_idx);
	try {
		std::transform(argv + start_idx,
		               argv + argc,
		               std::back_inserter(input),
		               ft::FromString<T>());
	}
	catch (const ft::FromStringException& e) {
		std::cerr << ft::log::error(e.what()) << '\n';
		throw PARSE_ERROR; // NOLINT: Exit code.
	}
	return input;
}
// NOLINTEND(cppcoreguidelines-pro-bounds-pointer-arithmetic)

template <typename C, typename T, typename Sorter>
static void print_before_after_sort(const std::vector<T>& input, Sorter sorter)
{
	C container(input.begin(), input.end());
	print_container(container, "Before: ");
	sorter(container);
	print_container(container, "After:  ");
}

template <typename C>
static void print_container(const C& container, const std::string& prefix)
{
	std::cout << prefix;
	std::copy(container.begin(),
	          container.end(),
	          std::ostream_iterator<typename C::value_type>(std::cout, " "));
	std::cout << '\n';
}

template <typename C, typename T, typename Sorter>
static void
pmerge_me_sort(PmergeMe& pmerge_me, const std::vector<T>& input, Sorter sorter)
{
	C container(input.begin(), input.end());
	pmerge_me.sort_logged(container, sorter, Sorter::name());
}
