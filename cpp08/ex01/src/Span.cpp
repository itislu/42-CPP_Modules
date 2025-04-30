#include "Span.hpp"
#include "libftpp/numeric.hpp"
#include "libftpp/string.hpp"
#include <algorithm>
#include <limits>
#include <set>
#include <stdexcept>

Span::Span(unsigned int max_size)
    : _max_size(max_size),
      _shortest_span(std::numeric_limits<unsigned int>::max()),
      _longest_span(std::numeric_limits<unsigned int>::min())
{}

Span::Span(const Span& other)
    : _elems(other._elems),
      _max_size(other._max_size),
      _shortest_span(other._shortest_span),
      _longest_span(other._longest_span)
{}

Span& Span::operator=(Span other)
{
	swap(other);
	return *this;
}

Span::~Span() {}

void Span::swap(Span& other)
{
	using std::swap;
	swap(_elems, other._elems);
	swap(_max_size, other._max_size);
	swap(_shortest_span, other._shortest_span);
	swap(_longest_span, other._longest_span);
}

void Span::addNumber(int nbr)
{
	if (_elems.size() == _max_size) {
		throw std::runtime_error("Trying to add " + ft::to_string(nbr)
		                         + " to already full Span ("
		                         + ft::to_string(_max_size) + ")");
	}
	const std::multiset<int>::iterator pos = _elems.insert(nbr);

	if (pos != _elems.begin()) {
		// Compare with lower neighbor
		const std::multiset<int>::iterator before(
		    --std::multiset<int>::iterator(pos));
		_shortest_span = std::min(ft::abs_diff(*pos, *before), _shortest_span);
	}
	else {
		// Inserted new lowest nbr
		_longest_span = ft::abs_diff(*_elems.begin(), *_elems.rbegin());
	}

	if (pos != --_elems.end()) {
		// Compare with higher neighbor
		const std::multiset<int>::iterator after(
		    ++std::multiset<int>::iterator(pos));
		_shortest_span = std::min(ft::abs_diff(*pos, *after), _shortest_span);
	}
	else {
		// Inserted new highest nbr
		_longest_span = ft::abs_diff(*_elems.begin(), *_elems.rbegin());
	}
}

unsigned int Span::shortestSpan() const
{
	if (_elems.size() < 2) {
		throw std::runtime_error(
		    "Trying to find shortestSpan() on Span with less than 2 elements");
	}
	return _shortest_span;
}

unsigned int Span::longestSpan() const
{
	if (_elems.size() < 2) {
		throw std::runtime_error(
		    "Trying to find longestSpan() on Span with less than 2 elements");
	}
	return _longest_span;
}

void swap(Span& a, Span& b)
{
	a.swap(b);
}
