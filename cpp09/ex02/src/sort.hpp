#pragma once

#include "libftpp/functional.hpp"
#include "libftpp/iterator.hpp"
#include "libftpp/type_traits.hpp"
#include <list>
#include <string>

/**
 * @brief A generic implementation of merge-insertion sort
 *
 * Fastest with random access iterators and contiguous storage.
 * The value type in the container gets copied a great amount.
 *
 * Elements are compared with `ft::less`.
 *
 * @tparam C Type of the container to sort. Its iterator must be a bidirectional
 * iterator or stronger
 */
template <typename C>
REQUIRES(ft::is_bidirectional_iterator<typename C::iterator>::value)
(void)merge_insertion_sort(C& container);
template <typename C, typename Compare>
REQUIRES(ft::is_bidirectional_iterator<typename C::iterator>::value)
(void)merge_insertion_sort(C& container, Compare comp);

/**
 * @brief An implementation of merge-insertion sort optimized for `std::list`
 *
 * Around 10x faster for `std::list` with a POD value type than the generic
 * implementation.
 * The value type in the container never gets copied.
 *
 * Elements are compared with `ft::less`.
 */
template <typename T>
void merge_insertion_sort_list(std::list<T>& lst);
template <typename T, typename Compare>
void merge_insertion_sort_list(std::list<T>& lst, Compare comp);

/* Sorters */

template <typename Compare = ft::less<> >
struct MergeInsertionSorter {
	typedef Compare value_compare;

	static const std::string& name();

	template <typename C>
	void operator()(C& container);

	value_compare value_comp();
};

template <typename Compare = ft::less<> >
struct MergeInsertionListSorter {
	typedef Compare value_compare;

	static const std::string& name();

	template <typename T>
	void operator()(std::list<T>& lst);

	value_compare value_comp();
};

template <typename Compare = ft::less<> >
struct StandardSorter {
	typedef Compare value_compare;

	static const std::string& name();

	template <typename C>
	void operator()(C& container);

	value_compare value_comp();
};

template <typename Compare = ft::less<> >
struct StandardListSorter {
	typedef Compare value_compare;

	static const std::string& name();

	template <typename T>
	void operator()(std::list<T>& lst);

	value_compare value_comp();
};

#include "sort/generic/merge_insertion_sort.tpp"   // IWYU pragma: export
#include "sort/list/merge_insertion_sort_list.tpp" // IWYU pragma: export
#include "sort/sorters.tpp"                        // IWYU pragma: export
