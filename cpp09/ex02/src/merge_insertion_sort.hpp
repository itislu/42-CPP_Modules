#pragma once

#include "libftpp/iterator.hpp"
#include "libftpp/type_traits.hpp"
#include <list>

/**
 * @brief A generic implementation of merge-insertion sort
 *
 * Fastest with random access iterators and contiguous storage.
 *
 * The value type in the container gets copied a great amount.
 *
 * @tparam C Type of the container to sort. Its iterator must be a bidirectional
 * iterator or stronger
 */
template <typename C>
REQUIRES(ft::is_bidirectional_iterator<typename C::iterator>::value)
(void)merge_insertion_sort(C& container);

/**
 * @brief An implementation of merge-insertion sort optimized for `std::list`
 *
 * Around 10x faster for `std::list` with a POD value type than the generic
 * implementation.
 *
 * The value type in the container never gets copied.
 */
template <typename T>
void merge_insertion_sort_list(std::list<T>& lst);

#include "merge_insertion_sort.tpp"      // IWYU pragma: export
#include "merge_insertion_sort_list.tpp" // IWYU pragma: export
