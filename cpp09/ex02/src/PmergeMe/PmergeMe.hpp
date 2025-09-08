#pragma once

#include "libftpp/Optional.hpp"
#include <cstddef>
#include <ctime>
#include <string>
#include <vector>

/**
 * @brief Utility class to benchmark and log different sorter, container and
 * value type combinations
 */
class PmergeMe {
public:
	/**
	 * @brief Runs a provided sorter with a provided container and collects and
	 * prints statistics of that operation
	 *
	 * Measures CPU time across multiple runs (`sort_time_measurements`), counts
	 * comparisons and copies (via `OperationCounter`), verifies sortedness, and
	 * prints a concise summary.
	 *
	 * @tparam C An STL-container
	 * @tparam Sorter Requirements:
	 * - Can be invoked with a container of type `C`.
	 * - Has a member function `value_comp` which returns a comparison function
	 *   object the sorter uses to compare values.
	 * @param container A reference to the container to be sorted. Gets mutated
	 * @param sorter A function object that sorts the container passed to it
	 * @param sorter_name Name of the sorter that gets printed in the summary
	 */
	template <typename C, typename Sorter>
	static void
	sort_logged(C& container, Sorter sorter, const std::string& sorter_name);

	static const unsigned sort_time_measurements = 5;

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

	struct _op_counter_tag {};

	PmergeMe();
	PmergeMe(const PmergeMe& other);
	PmergeMe& operator=(const PmergeMe& other);
	~PmergeMe();

	/* Collecting stats */

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
	template <typename C, typename Sorter>
	static void
	_check_is_sorted(const C& container, Sorter sorter, Stats_& stats);

	/* Printing stats */

	static void _print_stats_title(const Stats_& stats);
	static std::string _short_container_type_name(const Stats_& stats);
	static void _print_sort_times(const Stats_& stats);
	static void _print_sort_ops(const Stats_& stats);
	static void _print_is_sorted(const Stats_& stats);

	static const char* const _clear_prev_line;
};

#include "PmergeMe.tpp" // IWYU pragma: export
