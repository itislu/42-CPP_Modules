#pragma once

#include "libftpp/iterator.hpp"
#include "libftpp/type_traits.hpp"

/**
 * @brief A generic implementation of merge-insertion sort
 *
 * Fastest with random access iterators and contiguous storage.
 *
 * @tparam C Type of the container to sort. Its iterator must be a bidirectional
 * iterator or stronger
 */
template <typename C>
REQUIRES(ft::is_bidirectional_iterator<typename C::iterator>::value)
(void)merge_insertion_sort(C& container);

#include "merge_insertion_sort.tpp" // IWYU pragma: export
