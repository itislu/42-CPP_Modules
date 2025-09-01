#pragma once

#include "libftpp/iterator.hpp"
#include "libftpp/type_traits.hpp"
#include <list>

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

#include "merge_insertion_sort.tpp"      // IWYU pragma: export
#include "merge_insertion_sort_list.tpp" // IWYU pragma: export
