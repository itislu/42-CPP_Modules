#pragma once

#include <iterator>

namespace utils {
namespace algorithm {

template <typename InputIterator, typename T>
typename std::iterator_traits<InputIterator>::difference_type
count(InputIterator first, InputIterator last, const T& value);

} // namespace algorithm
} // namespace utils

#include "algorithm.tpp" // IWYU pragma: export
