#include "PmergeMe.hpp"
#include "libftpp/format.hpp"
#include "libftpp/utility.hpp"
#include "sort.hpp"
#include "test_types/ExpensiveComparison.hpp"
#include "test_types/ExpensiveCopy.hpp"
#include "utils.hpp"
#include <exception>
#include <iostream>
#include <list>
#include <string>
#include <vector>

template <typename C, typename T, typename Sorter>
static void compare_before_after_sort(const std::vector<T>& input,
                                      Sorter sorter);
template <typename TestType, typename T>
static void test_containers_and_sorters(const std::vector<T>& input);
template <typename C, typename T, typename Sorter>
static void pmerge_me_sort(const std::vector<T>& input, Sorter sorter);
template <typename T>
static void test_expensive_comparison(const std::vector<T>& input);
template <typename T>
static void test_expensive_copy(const std::vector<T>& input);
static void test_string(int argc, char* argv[]);

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
		compare_before_after_sort<std::vector<InputType> >(
		    input, MergeInsertionSorter<>());
	}

	test_containers_and_sorters<InputType>(input);

	if (more_types) {
		test_expensive_comparison(input);
		test_expensive_copy(input);
		test_string(argc, argv);
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

template <typename C, typename T, typename Sorter>
static void compare_before_after_sort(const std::vector<T>& input,
                                      Sorter sorter)
{
	C container(input.begin(), input.end());
	std::cout
	    << "------------------------------------------------------------\n";
	print_container(container, BOLD("Before: "));
	std::cout
	    << "------------------------------------------------------------\n";
	sorter(container);
	print_container(container, BOLD("After:  "));
	std::cout
	    << "------------------------------------------------------------\n";
}

template <typename TestType, typename T>
static void test_containers_and_sorters(const std::vector<T>& input)
{
	pmerge_me_sort<std::vector<TestType> >(input, MergeInsertionSorter<>());
	pmerge_me_sort<std::list<TestType> >(input, MergeInsertionSorter<>());
	pmerge_me_sort<std::list<TestType> >(input, MergeInsertionListSorter<>());
	pmerge_me_sort<std::vector<TestType> >(input, StandardSorter<>());
	pmerge_me_sort<std::list<TestType> >(input, StandardListSorter<>());
}

template <typename C, typename T, typename Sorter>
static void pmerge_me_sort(const std::vector<T>& input, Sorter sorter)
{
	C container(input.begin(), input.end());
	PmergeMe::sort_logged(container, sorter, Sorter::name());
}

template <typename T>
static void test_expensive_comparison(const std::vector<T>& input)
{
	print_seperator("ExpensiveComparison");
	std::cout << GRAY(
	    "At around 1500 extra operations per comparison, merge_insertion_sort "
	    "starts to become faster than std::sort.")
	          << '\n';
	const unsigned long dummy_ops = 1500;
	test_containers_and_sorters<ExpensiveComparison<T, dummy_ops> >(input);
}

template <typename T>
static void test_expensive_copy(const std::vector<T>& input)
{
	print_seperator("ExpensiveCopy");
	std::cout << GRAY(
	    "Just making the value type non-POD makes vector slower than list in "
	    "merge_insertion_sort.")
	          << '\n';
	const unsigned long dummy_ops = 0;
	test_containers_and_sorters<ExpensiveCopy<T, dummy_ops> >(input);
}

static void test_string(int argc, char* argv[])
{
	print_seperator("std::string");
	std::cout << GRAY(
	    "The large amount of expensive copies in merge_insertion_sort far "
	    "outweighs the savings of fewer comparisons than std::sort.")
	          << '\n';
	test_containers_and_sorters<std::string>(
	    parse_args<std::string>(argc, argv));
}
