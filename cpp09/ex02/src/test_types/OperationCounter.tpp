#pragma once

#include "OperationCounter.hpp"
#include <algorithm>
#include <cstddef>
#include <istream>
#include <ostream>

template <typename T, typename UniqueTag /*= void*/>
std::size_t OperationCounter<T, UniqueTag>::_comparisons = 0;
template <typename T, typename UniqueTag /*= void*/>
std::size_t OperationCounter<T, UniqueTag>::_copies = 0;

template <typename T, typename UniqueTag /*= void*/>
std::size_t OperationCounter<T, UniqueTag>::comparisons() throw()
{
	return _comparisons;
}

template <typename T, typename UniqueTag /*= void*/>
std::size_t OperationCounter<T, UniqueTag>::copies() throw()
{
	return _copies;
}

template <typename T, typename UniqueTag /*= void*/>
void OperationCounter<T, UniqueTag>::reset() throw()
{
	_comparisons = 0;
	_copies = 0;
}

template <typename T, typename UniqueTag /*= void*/>
OperationCounter<T, UniqueTag>::OperationCounter()
    : _v()
{}

template <typename T, typename UniqueTag /*= void*/>
OperationCounter<T, UniqueTag>::OperationCounter(const T& v)
    : _v(v)
{}

template <typename T, typename UniqueTag /*= void*/>
OperationCounter<T, UniqueTag>::OperationCounter(const OperationCounter& other)
    : _v(other._v)
{
	++_copies;
}

template <typename T, typename UniqueTag /*= void*/>
OperationCounter<T, UniqueTag>&
OperationCounter<T, UniqueTag>::operator=(const OperationCounter& other)
{
	if (&other == this) {
		return *this;
	}
	_v = other._v;
	++_copies;
	return *this;
}

template <typename T, typename UniqueTag /*= void*/>
OperationCounter<T, UniqueTag>::~OperationCounter()
{}

template <typename T, typename UniqueTag /*= void*/>
bool
OperationCounter<T, UniqueTag>::operator==(const OperationCounter& other) const
{
	const bool b = _v == other._v;
	++_comparisons;
	return b;
}

template <typename T, typename UniqueTag /*= void*/>
bool
OperationCounter<T, UniqueTag>::operator!=(const OperationCounter& other) const
{
	const bool b = _v != other._v;
	++_comparisons;
	return b;
}

template <typename T, typename UniqueTag /*= void*/>
bool
OperationCounter<T, UniqueTag>::operator<(const OperationCounter& other) const
{
	const bool b = _v < other._v;
	++_comparisons;
	return b;
}

template <typename T, typename UniqueTag /*= void*/>
bool
OperationCounter<T, UniqueTag>::operator>(const OperationCounter& other) const
{
	const bool b = _v > other._v;
	++_comparisons;
	return b;
}

template <typename T, typename UniqueTag /*= void*/>
bool
OperationCounter<T, UniqueTag>::operator<=(const OperationCounter& other) const
{
	const bool b = _v <= other._v;
	++_comparisons;
	return b;
}

template <typename T, typename UniqueTag /*= void*/>
bool
OperationCounter<T, UniqueTag>::operator>=(const OperationCounter& other) const
{
	const bool b = _v >= other._v;
	++_comparisons;
	return b;
}

template <typename T, typename UniqueTag /*= void*/>
void OperationCounter<T, UniqueTag>::swap(OperationCounter& other)
{
	using std::swap;
	swap(_v, other._v);
}

template <typename T, typename UniqueTag /*= void*/>
T& OperationCounter<T, UniqueTag>::value() throw()
{
	return _v;
}

template <typename T, typename UniqueTag /*= void*/>
const T& OperationCounter<T, UniqueTag>::value() const throw()
{
	return _v;
}

template <typename T, typename UniqueTag>
void swap(OperationCounter<T, UniqueTag>& lhs,
          OperationCounter<T, UniqueTag>& rhs)
{
	lhs.swap(rhs);
}

template <typename T, typename UniqueTag>
std::istream& operator>>(std::istream& is, OperationCounter<T, UniqueTag>& rhs)
{
	is >> rhs.value();
	return is;
}

template <typename T, typename UniqueTag>
std::ostream& operator<<(std::ostream& os,
                         const OperationCounter<T, UniqueTag>& rhs)
{
	os << rhs.value();
	return os;
}
