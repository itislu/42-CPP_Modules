#pragma once

#include "libftpp/Optional.hpp"
#include <cstddef>
#include <ctime>
#include <string>
#include <vector>

/*
PmergeMe has a container of Stats_ structs.
Stats_ store:
- size of the container
- typeid of the container - print it until the first '<'
- typeid of the value type
- time to sort (multiple times to collect average)
- bool if it was sorted correctly
- num of comparisons
- num of copies
- maybe optional notes

// PmergeMe also has the input numbers as a vector.

.sort() is a template function; container type must be given as template arg.
// - Creates the container.
- Sorts with the provided callback function (so std::sort can also be used with
  containers that support it).
- Collects and stores stats.
- Prints the output required by the subject.

.print_stats()
- Goes through the Stats_ container and prints it in a formatted way.
*/
class PmergeMe {
public:
	PmergeMe();
	PmergeMe(const PmergeMe& other);
	PmergeMe& operator=(PmergeMe other);
	~PmergeMe();

	void swap(PmergeMe& other);

	template <typename C, typename Sorter>
	void sort(C& container, Sorter sorter, const std::string& sorter_name);
	void print_stats() const;

private:
	struct Stats_ {
		std::string container_type_name;
		std::string value_type_name;
		std::string sorter_name;
		std::size_t container_size;
		std::vector<std::clock_t> sort_times;
		ft::Optional<std::size_t> num_comparisons;
		ft::Optional<std::size_t> num_copies;
		bool is_sorted;
	};

	template <typename C, typename To>
	struct _rebind_value_type;

	static const unsigned _measurements = 5;

	template <typename C, typename Sorter>
	void _sort_timed(C& container, Sorter sorter, Stats_& stats);
	template <typename C, typename Sorter>
	void _count_sort_stats(const C& container, Sorter sorter, Stats_& stats);

	std::vector<Stats_> _stats_log;
};

void swap(PmergeMe& lhs, PmergeMe& rhs);

#include "PmergeMe.tpp" // IWYU pragma: export
