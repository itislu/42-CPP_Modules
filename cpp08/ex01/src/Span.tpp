#pragma once

#include "Span.hpp"

template <typename InputIt>
void Span::addNumber(InputIt first, InputIt last)
{
	for (; first != last; ++first) {
		addNumber(*first);
	}
}
