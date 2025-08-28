#pragma once

#include "OperationCounter.hpp"
#include <algorithm>
#include <cstddef>
#include <istream>
#include <ostream>

template <typename T>
std::size_t OperationCounter<T>::_comparisons = 0;
template <typename T>
std::size_t OperationCounter<T>::_copies = 0;

template <typename T>
std::size_t OperationCounter<T>::comparisons() throw()
{
	return _comparisons;
}

template <typename T>
std::size_t OperationCounter<T>::copies() throw()
{
	return _copies;
}

template <typename T>
void OperationCounter<T>::reset() throw()
{
	_comparisons = 0;
	_copies = 0;
}

template <typename T>
OperationCounter<T>::OperationCounter()
    : _v()
{}

template <typename T>
OperationCounter<T>::OperationCounter(const T& v)
    : _v(v)
{}

template <typename T>
OperationCounter<T>::OperationCounter(const OperationCounter& other)
    : _v(other._v)
{
	++_copies;
}

template <typename T>
OperationCounter<T>&
OperationCounter<T>::operator=(const OperationCounter& other)
{
	if (&other == this) {
		return *this;
	}
	_v = other._v;
	++_copies;
	return *this;
}

template <typename T>
OperationCounter<T>::~OperationCounter()
{}

template <typename T>
bool OperationCounter<T>::operator==(const OperationCounter& other) const
{
	const bool b = _v == other._v;
	++_comparisons;
	return b;
}

template <typename T>
bool OperationCounter<T>::operator!=(const OperationCounter& other) const
{
	const bool b = _v != other._v;
	++_comparisons;
	return b;
}

template <typename T>
bool OperationCounter<T>::operator<(const OperationCounter& other) const
{
	const bool b = _v < other._v;
	++_comparisons;
	return b;
}

template <typename T>
bool OperationCounter<T>::operator>(const OperationCounter& other) const
{
	const bool b = _v > other._v;
	++_comparisons;
	return b;
}

template <typename T>
bool OperationCounter<T>::operator<=(const OperationCounter& other) const
{
	const bool b = _v <= other._v;
	++_comparisons;
	return b;
}

template <typename T>
bool OperationCounter<T>::operator>=(const OperationCounter& other) const
{
	const bool b = _v >= other._v;
	++_comparisons;
	return b;
}

template <typename T>
void OperationCounter<T>::swap(OperationCounter& other)
{
	using std::swap;
	swap(_v, other._v);
}

template <typename T>
T& OperationCounter<T>::value() throw()
{
	return _v;
}

template <typename T>
const T& OperationCounter<T>::value() const throw()
{
	return _v;
}

template <typename T>
void swap(OperationCounter<T>& lhs, OperationCounter<T>& rhs)
{
	lhs.swap(rhs);
}

template <typename T>
std::istream& operator>>(std::istream& is, OperationCounter<T>& rhs)
{
	is >> rhs.value();
	return is;
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const OperationCounter<T>& rhs)
{
	os << rhs.value();
	return os;
}
