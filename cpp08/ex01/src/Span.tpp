#pragma once

#include "Span.hpp"
#include "libftpp/numeric.hpp"
#include <algorithm>
#include <cstdlib>
#include <set>

// Satisfies subject requirement to fill as much as possible:
// "Any attempt to add a new element if there are already N elements stored
// should throw an exception."
template <typename InputIt>
void Span::addNumber(InputIt first, InputIt last)
{
	const std::multiset<int>::size_type amount =
	    static_cast<std::multiset<int>::size_type>(
	        std::labs(std::distance(first, last)));

	if (amount < 16 || amount > _max_size - _elems.size()) {
		for (; first != last; ++first) {
			addNumber(*first);
		}
		return;
	}

	_elems.insert(first, last);
	_longest_span = ft::abs_diff(*_elems.begin(), *_elems.rbegin());
	for (std::multiset<int>::iterator next = _elems.begin(),
	                                  cur = next++,
	                                  end = _elems.end();
	     next != end;
	     ++cur, ++next) {
		_shortest_span = std::min(ft::abs_diff(*cur, *next), _shortest_span);
		if (_shortest_span == 0) {
			break;
		}
	}
}
