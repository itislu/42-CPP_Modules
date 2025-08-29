#include "GroupIterator.hpp"
#include "MergeInsertionList.hpp"
#include "PmergeMe.hpp"
#include "libftpp/Expected.hpp"
#include "libftpp/format.hpp"
#include "libftpp/string.hpp"
#include "libftpp/utility.hpp"
#include "merge_insertion_sort.hpp"
#include "test_types/OperationCounter.hpp"
#include <algorithm>
#include <ctime>
#include <deque>
#include <exception>
#include <iostream>
#include <iterator>
#include <list>
#include <locale>
#include <memory>
#include <string>
#include <vector>

/*
Get next index

Goal:
Use pure logic, not Jacobstahl formula.
Only consider how many items are already sorted.

Logic:
The number of sorted items is the search space. We want to maximize the search
space for the minimum currently possible binary insertion comparison count.
cur_comps = floor(log2(search_size)) + 1
max_search_size = pow(2, cur_comps) - 1

We can increase the current search space to the max search space with the same
amount of comparisons.
skip = max_search_size - search_size

We can add 1 to the index bc the item's search space is automatically decreased
by its pair.
prev_max_index = search_size / 2
next_index = prev_max_index + skip + 1

Data:
- Sorted amount / search space
- Index when to make next request
  OR: Target search space (size until request next index)
*/

/*
Insertion:

Don't need to label and track pairs at all:
"if you insert at the end of the current search range, you can check that, and
now just decrease the search range by 1 until the next jacobstahl jump"
*/

/*
T could be made a pointer to the actual element if heavy type.
merge_insertion(vector<T>)
{
    vector<pair<T, T> > = pair_up(vector<T>)
    sort_pairs(vector<pair<T, T> >)
    merge_insertion(vector<pair<T, T> >)
    vector<T>.clear()
    binary_insertion(vector<pair<T, T> >, vector<T>)
}
*/

enum Error {
	UNEXPECTED = -1,
	OK = 0,
	NO_ARGS = 1,
	PARSE_ERROR = 2
};

// typedef OperationCounter<unsigned long> CompType; // TODO change
typedef unsigned CompType;

struct MergeInsertionSorter {
	static std::string name() { return "merge_insertion_sort()"; }

	template <typename C>
	void operator()(C& container)
	{
		merge_insertion_sort(container);
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

template <typename C, typename T, typename Sorter>
static void
pmerge_me_sort(PmergeMe& pmerge_me, const std::vector<T>& input, Sorter sorter)
{
	C container(input.begin(), input.end());
	pmerge_me.sort_logged(container, sorter, Sorter::name());
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
static void print_before_after_sort(const std::vector<T>& input, Sorter sorter)
{
	C container(input.begin(), input.end());
	print_container(container, "Before: ");
	sorter(container);
	print_container(container, "After:  ");
}

// NOLINTBEGIN(cppcoreguidelines-pro-bounds-pointer-arithmetic)
// TODO Maybe change back to just throwing Error bc it's more concise.
static ft::Expected<std::vector<CompType>, Error>
parse_args(int argc, char* argv[], bool& quiet)
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
		return ft::Unexpected<Error>(NO_ARGS);
	}

	ft::Expected<std::vector<CompType>, Error> input;
	input->reserve(argc - start_idx);
	try {
		std::transform(argv + start_idx,
		               argv + argc,
		               std::back_inserter(*input),
		               ft::FromString<CompType>());
	}
	catch (const ft::FromStringException& e) {
		std::cerr << ft::log::error(e.what()) << '\n';
		return ft::Unexpected<Error>(PARSE_ERROR);
	}
	return input;
}
// NOLINTEND(cppcoreguidelines-pro-bounds-pointer-arithmetic)

const std::clock_t clocks_per_usec = CLOCKS_PER_SEC / 1000000;

template <typename Sort>
void sort(std::list<CompType> lst, Sort sort_f)
{
	// std::cout << "Before: ";
	// std::copy(
	//     lst.begin(), lst.end(), std::ostream_iterator<CompType>(std::cout,
	//     " "));
	// std::cout << '\n';

	const std::clock_t start = std::clock();
	sort_f(lst);
	const std::clock_t end = std::clock();

	// std::cout << "After:  ";
	// std::copy(
	//     lst.begin(), lst.end(), std::ostream_iterator<CompType>(std::cout,
	//     " "));
	// std::cout << '\n';

	std::cout << "Time: " << (end - start) / clocks_per_usec << "us\n";
}

void test_group_iterator(std::vector<CompType> vec)
{
	typedef std::vector<CompType>::iterator VecIt;
	// typedef std::list<CompType>::iterator LstIt;

	for (GroupIterator<VecIt> it(vec.begin(), 4),
	     end = GroupIterator<VecIt>::end(vec.begin(), vec.end(), 4);
	     it != end;
	     ++it) {
		std::cout << *it << ' ';
	}
	std::cout << '\n';

	// std::list<CompType> lst(vec.begin(), vec.end());
	// for (GroupIterator<LstIt> it = GroupIterator<LstIt>::begin(lst, 4),
	//                           end = GroupIterator<LstIt>::end(lst, 4);
	//      it != end;
	//      ++it) {
	// 	std::cout << *it << ' ';
	// }
	// std::cout << '\n';
}

/*
PMergeMe manages the timing, delegates the sorting to sth else.

Once everything done, compare FJ with std::sort, once with integers, and once
with a type that takes long to compare.
Use composition: OperationCounter<ExpensiveComparison<ExpensiveCopy<T> > >
*/
int main(int argc, char* argv[])
try {
	typedef std::vector<CompType> Input;
	std::locale::global(std::locale(""));

	bool quiet = false;
	const ft::Expected<Input, Error> expected_input =
	    parse_args(argc, argv, quiet);
	if (!expected_input) {
		// Avoid "still reachable" valgrind warnings.
		std::locale::global(std::locale::classic());
		return expected_input.error();
	}
	const Input& input = *expected_input;
	
	if (!quiet) {
		print_before_after_sort<std::vector<CompType> >(input,
		                                                MergeInsertionSorter());
	}

	PmergeMe pmerge_me;
	pmerge_me_sort<std::vector<CompType> >(
	    pmerge_me, input, MergeInsertionSorter());
	pmerge_me_sort<std::deque<CompType> >(
	    pmerge_me, input, MergeInsertionSorter());
	pmerge_me_sort<std::list<CompType> >(
	    pmerge_me, input, MergeInsertionSorter());
	pmerge_me_sort<std::vector<CompType> >(pmerge_me, input, StandardSorter());
	pmerge_me_sort<std::deque<CompType> >(pmerge_me, input, StandardSorter());
	pmerge_me_sort<std::list<CompType> >(
	    pmerge_me, input, StandardListSorter());
	pmerge_me.print_stats();

	// return OK;

	std::cout << "\nMergeInsertionList\n";
	std::clock_t start, end;

	std::auto_ptr<std::list<CompType> > lst(
	    new std::list<CompType>(input.begin(), input.end()));

	// encapsulation test
	// MergeInsertionList<CompType>::iterator::CompType test(lst->begin());

	// std::cout << "Before: ";
	// std::copy(
	//     lst.begin(), lst.end(), std::ostream_iterator<CompType>(std::cout,
	//     " "));
	// std::cout << '\n';

	// std::clock_t start = std::clock();
	// sort_pairwise(lst);
	// std::clock_t end = std::clock();

	// std::cout << "After:  ";
	// std::copy(
	//     lst.begin(), lst.end(), std::ostream_iterator<CompType>(std::cout,
	//     " "));
	// std::cout << '\n';

	// std::cout << "Time: " << (end - start) / clocks_per_usec << "us\n";

	// sort(*lst, sort_pairwise<CompType>);
	// CompType::reset();

	start = std::clock();
	MergeInsertionList<CompType> lazy_list(lst);
	lazy_list.sort();
	end = std::clock();
	std::cout << "Time: " << (end - start) / clocks_per_usec << "us\n";

	// print_container("List:  ", lst);
	std::cout << '\n';

	// std::cout << "size: " << lazy_list._lst.size() << '\n';
	// std::cout << "step_size:  " << lazy_list._step_size << '\n';
	// print_container("Lazy1: ", lazy_list);
	// std::cout << '\n';

	// lazy_list.sort();
	// print_container("sorted: ", lazy_list);
	// std::cout << '\n';

	// lazy_list.sort();
	// print_container("sorted: ", lazy_list);
	// std::cout << '\n';

	// lazy_list.sort();
	// print_container("sorted: ", lazy_list);
	// std::cout << '\n';

	std::cout << "release()\n";
	start = std::clock();
	lst = lazy_list.release();
	// lst = lazy_list.release(); // TODO segfault
	end = std::clock();
	std::cout << "Time: " << (end - start) / clocks_per_usec << "us\n";

	// print_container("List:  ", *lst);
	// std::cout << '\n';

	// std::cout << "Comparisons: " << CompType::comparisons() << '\n';
	// std::cout << "Copies:      " << CompType::copies() << '\n';

	// std::cout << "\nhalf_skip_size\n", lazy_list.half_skip_size();
	// print_container("Lazy1: ", lazy_list);
	// std::cout << '\n';

	// std::cout << "\nhalf_skip_size\n", lazy_list.half_skip_size();
	// print_container("Lazy1: ", lazy_list);
	// std::cout << '\n';

	// lazy_list.half_skip_size(); // throws

	// std::cout << "size:  " << lazy_list._next.size() << '\n';
	// std::cout << "step_size:  " << lazy_list._step_size << '\n';
	// std::cout << '\n';

	// std::cout << "size:  " << lazy_list._next.front()._next.size() << '\n';
	// std::cout << "step_size:  " << lazy_list._next.front()._step_size <<
	// '\n'; std::cout << '\n';

	// std::cout << "pos:   " << *lazy_list.pos() << '\n';
	// print_container("List1: ", lazy_list._next);

	// std::cout << "\nhalf_step_size\n", lazy_list.half_step_size();
	// std::cout << "pos:   " << *lazy_list.pos() << '\n';
	// print_container("List2: ", lazy_list._next);

	// std::cout << "\nhalf_step_size\n", lazy_list.half_step_size();
	// std::cout << "pos:   " << *lazy_list.pos() << '\n';
	// print_container("List2: ", lazy_list._next);

	std::locale::global(std::locale::classic());
	return OK;
}
catch (const std::exception& e) {
	std::cerr << ft::log::error(BOLD("Unexpected exception: ") + e.what())
	          << '\n';
	std::locale::global(std::locale::classic());
	return UNEXPECTED;
}
