#include "PmergeMe.hpp"
#include "libftpp/format.hpp"
#include "libftpp/string.hpp"
#include <algorithm>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

static std::string format_duration(std::clock_t duration);
static std::clock_t median(std::vector<std::clock_t> sort_times);

const char* const PmergeMe::_clear_prev_line = "\033[A\033[2K\r";

void PmergeMe::_print_stats_title(const Stats_& stats)
{
	std::cout << '\n'
	          << BOLD(UNDERLINE(ft::to_string(stats.container_size) + " "
	                            + stats.value_type_name + "  |  "
	                            + _short_container_type_name(stats) + "  |  "
	                            + stats.sorter_name))
	          << '\n';
}

std::string PmergeMe::_short_container_type_name(const Stats_& stats)
{
	return stats.container_type_name.substr(
	    0, stats.container_type_name.find('<'));
}

void PmergeMe::_print_sort_times(const Stats_& stats)
{
	std::cout << "Sorting time (median of " << _measurements
	          << "): " << format_duration(median(stats.sort_times)) << '\n';
	std::cout << "Sorting time (min. of " << _measurements << "):   "
	          << format_duration(*std::min_element(stats.sort_times.begin(),
	                                               stats.sort_times.end()))
	          << '\n';
}

void PmergeMe::_print_sort_ops(const Stats_& stats)
{
	std::cout << "Comparisons: "
	          << (stats.num_comparisons ? ft::to_string(*stats.num_comparisons)
	                                    : "could not be counted")
	          << '\n';
	std::cout << "Copies: "
	          << (stats.num_copies ? ft::to_string(*stats.num_copies)
	                               : "could not be counted")
	          << '\n';
}

void PmergeMe::_print_is_sorted(const Stats_& stats)
{
	std::cout << "Sorted: " << (stats.is_sorted ? "Yes" : "No") << '\n';
}

static std::string format_duration(std::clock_t duration)
{
	const long double ms_in_s = 1000;
	const long double us_in_s = ms_in_s * 1000;
	const long double us =
	    static_cast<long double>(duration) / (CLOCKS_PER_SEC / us_in_s);
	std::ostringstream oss;
	oss << std::fixed << std::setprecision(3);

	if (us >= us_in_s) {
		oss << (us / us_in_s) << " s";
	}
	else if (us >= ms_in_s) {
		oss << (us / ms_in_s) << " ms";
	}
	else {
		oss << std::setprecision(0) << us << " μs";
	}
	return oss.str();
}

static std::clock_t median(std::vector<std::clock_t> sort_times)
{
	typedef std::vector<std::clock_t>::difference_type Diff;
	typedef std::vector<std::clock_t>::iterator It;

	const Diff n = static_cast<Diff>(sort_times.size());
	const It begin = sort_times.begin();
	const It mid = sort_times.begin() + n / 2;
	const It end = sort_times.end();

	std::nth_element(begin, mid, end);
	std::clock_t median = *mid;
	if (n % 2 == 0) {
		const std::clock_t prev = *std::max_element(begin, mid);
		median = prev + (median - prev) / 2;
	}
	return median;
}
