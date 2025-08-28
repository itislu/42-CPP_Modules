#pragma once

#include "PmergeMe.hpp"
#include "libftpp/algorithm.hpp"
#include "libftpp/type_traits.hpp"
#include "libftpp/utility.hpp"
#include "test_types/OperationCounter.hpp"
#include <ctime>
#include <iostream>
#include <string>
#include <typeinfo>

template <typename C, typename Sorter>
void PmergeMe::sort(C& container, Sorter sorter, const std::string& sorter_name)
{
	typedef typename C::value_type value_type;

	Stats_ stats;
	stats.container_type_name = ft::demangle(typeid(C).name());
	stats.value_type_name = ft::demangle(typeid(value_type).name());
	stats.sorter_name = sorter_name;
	stats.container_size = container.size();

	_count_sort_stats(container, sorter, stats);

	const char* clear_prev_line = "\033[A\033[2K\r";
	std::cerr << '\n';
	for (unsigned i = 1; i <= _measurements; ++i) {
		std::cerr << clear_prev_line << "Measuring ... " << i << "/"
		          << _measurements << '\n';
		if (i != _measurements) {
			C tmp(container);
			_sort_timed(tmp, sorter, stats);
		}
		else {
			_sort_timed(container, sorter, stats);
		}
	}
	stats.is_sorted = ft::is_sorted(container.begin(), container.end());

	_stats_log.push_back(stats);
}

template <typename C, typename Sorter>
void PmergeMe::_sort_timed(C& container, Sorter sorter, Stats_& stats)
{
	const std::clock_t start = std::clock();
	sorter(container);
	const std::clock_t end = std::clock();
	stats.sort_times.push_back(end - start);
}

template <typename C, typename Sorter>
void
PmergeMe::_count_sort_stats(const C& container, Sorter sorter, Stats_& stats)
{
	typedef OperationCounter<typename C::value_type> OpCounter;
	typedef typename _rebind_value_type<C, OpCounter>::type CountedContainer;

	if (ft::is_same<CountedContainer, C>::value) {
		return;
	}

	// Scope so OpCounter can be reset after CountedContainer gets destructed.
	{
		CountedContainer tmp(container.begin(), container.end());
		OpCounter::reset();
		sorter(tmp);
		stats.num_comparisons = OpCounter::comparisons();
		stats.num_copies = OpCounter::copies();
	}
	OpCounter::reset();
}

template <typename C, typename>
struct PmergeMe::_rebind_value_type : ft::type_identity<C> {};

template <template <typename> class C, typename From, typename To>
struct PmergeMe::_rebind_value_type<C<From>, To> : ft::type_identity<C<To> > {};

template <template <typename, typename> class C,
          typename From,
          template <typename> class A,
          typename To>
struct PmergeMe::_rebind_value_type<C<From, A<From> >, To>
    : ft::type_identity<C<To, A<To> > > {};
