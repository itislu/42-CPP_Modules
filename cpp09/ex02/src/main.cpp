#include "PmergeMe.hpp"
#include "libftpp/format.hpp"
#include "libftpp/utility.hpp"
#include "merge_insertion_sort.hpp"
#include "test_types/ExpensiveComparison.hpp"
#include "test_types/ExpensiveCopy.hpp"
#include "utils.hpp"
#include <algorithm>
#include <deque>
#include <exception>
#include <iostream>
#include <list>
#include <string>
#include <vector>

template <typename TestType, typename T>
static void test_all(PmergeMe& pmerge_me, const std::vector<T>& input);
template <typename C, typename T, typename Sorter>
static void
pmerge_me_sort(PmergeMe& pmerge_me, const std::vector<T>& input, Sorter sorter);
template <typename C, typename T, typename Sorter>
static void print_before_after_sort(const std::vector<T>& input, Sorter sorter);

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

// NOLINTBEGIN(readability-magic-numbers)
int main(int argc, char* argv[])
try {
	typedef unsigned InputType;

	init_user_locale();

	bool more_types = false;
	bool no_before_after = false;
	const std::vector<InputType> input =
	    parse_args<InputType>(argc, argv, &more_types, &no_before_after);

	print_seperator(ft::demangle(typeid(InputType).name()));

	if (!no_before_after) {
		print_before_after_sort<std::vector<InputType> >(
		    input, MergeInsertionSorter());
	}

	PmergeMe pmerge_me;
	test_all<InputType>(pmerge_me, input);

	if (more_types) {
		print_seperator("std::string");
		test_all<std::string>(pmerge_me, parse_args<std::string>(argc, argv));

		print_seperator("ExpensiveComparison");
		test_all<ExpensiveComparison<InputType, 1000> >(pmerge_me, input);

		print_seperator("ExpensiveCopy");
		test_all<ExpensiveCopy<InputType, 0> >(pmerge_me, input);
	}

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
// NOLINTEND(readability-magic-numbers)

template <typename TestType, typename T>
static void test_all(PmergeMe& pmerge_me, const std::vector<T>& input)
{
	pmerge_me_sort<std::vector<TestType> >(
	    pmerge_me, input, MergeInsertionSorter());
	pmerge_me_sort<std::deque<TestType> >(
	    pmerge_me, input, MergeInsertionSorter());
	pmerge_me_sort<std::list<TestType> >(
	    pmerge_me, input, MergeInsertionSorter());
	pmerge_me_sort<std::list<TestType> >(
	    pmerge_me, input, MergeInsertionListSorter());
	pmerge_me_sort<std::vector<TestType> >(pmerge_me, input, StandardSorter());
	pmerge_me_sort<std::deque<TestType> >(pmerge_me, input, StandardSorter());
	pmerge_me_sort<std::list<TestType> >(
	    pmerge_me, input, StandardListSorter());
}

template <typename C, typename T, typename Sorter>
static void
pmerge_me_sort(PmergeMe& pmerge_me, const std::vector<T>& input, Sorter sorter)
{
	C container(input.begin(), input.end());
	pmerge_me.sort_logged(container, sorter, Sorter::name());
}

template <typename C, typename T, typename Sorter>
static void print_before_after_sort(const std::vector<T>& input, Sorter sorter)
{
	C container(input.begin(), input.end());
	print_container(container, "Before: ");
	sorter(container);
	print_container(container, "After:  ");
}
