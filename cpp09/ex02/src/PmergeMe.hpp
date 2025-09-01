#pragma once

#include "libftpp/Optional.hpp"
#include <cstddef>
#include <ctime>
#include <string>
#include <vector>

class PmergeMe {
public:
	template <typename C, typename Sorter>
	static void
	sort_logged(C& container, Sorter sorter, const std::string& sorter_name);

private:
	struct Stats_ {
		std::string value_type_name;
		std::string container_type_name;
		std::string sorter_name;
		std::size_t container_size;
		std::vector<std::clock_t> sort_times;
		ft::Optional<std::size_t> num_comparisons;
		ft::Optional<std::size_t> num_copies;
		bool is_sorted;
	};

	template <typename C, typename To>
	struct _rebind_value_type;

	PmergeMe();
	PmergeMe(const PmergeMe& other);
	PmergeMe& operator=(const PmergeMe& other);
	~PmergeMe();

	/* Collecting stats */

	/**
	 * @attention This modifies `container` into a sorted state.
	 */
	template <typename C, typename Sorter>
	static void _measure_sort_times(C& container,
	                                const C& unsorted,
	                                Sorter sorter,
	                                Stats_& stats);
	template <typename C, typename Sorter>
	static void _sort_timed(C& container, Sorter sorter, Stats_& stats);
	template <typename C, typename Sorter>
	static void
	_count_sort_ops(const C& container, Sorter sorter, Stats_& stats);
	template <typename C>
	static void _check_is_sorted(const C& container, Stats_& stats);

	/* Printing stats */

	static void _print_stats_title(const Stats_& stats);
	static std::string _short_container_type_name(const Stats_& stats);
	static void _print_sort_times(const Stats_& stats);
	static void _print_sort_ops(const Stats_& stats);
	static void _print_is_sorted(const Stats_& stats);

	static const unsigned _measurements = 5;
	static const char* const _clear_prev_line;
};

#include "PmergeMe.tpp" // IWYU pragma: export
