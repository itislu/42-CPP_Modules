#pragma once

#include "algorithm.hpp"
#include <iterator>

namespace utils {
namespace algorithm {

template <typename InputIterator, typename T>
typename std::iterator_traits<InputIterator>::difference_type
count(InputIterator first, InputIterator last, const T& value)
{
	typename std::iterator_traits<InputIterator>::difference_type res = 0;

	for (; first != last; ++first) {
		if (*first == value) {
			++res;
		}
	}
	return res;
}

} // namespace algorithm
} // namespace utils
