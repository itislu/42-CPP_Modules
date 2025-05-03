#pragma once

#include <set>

class Span {
public:
	Span(unsigned int max_size);
	Span(const Span& other);
	Span& operator=(Span other);
	~Span();

	void swap(Span& other);

	void addNumber(int nbr);
	template <typename InputIt>
	void addNumber(InputIt first, InputIt last);
	unsigned int shortestSpan() const;
	unsigned int longestSpan() const;

private:
	Span();

	std::multiset<int> _elems;
	unsigned int _max_size;
	unsigned int _shortest_span;
	unsigned int _longest_span;
};

void swap(Span& lhs, Span& rhs);

#include "Span.tpp" // IWYU pragma: export
