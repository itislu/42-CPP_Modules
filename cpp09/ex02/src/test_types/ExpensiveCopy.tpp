#pragma once

#include "ExpensiveCopy.hpp"
#include "busy_wait.hpp"
#include <istream>
#include <ostream>

template <typename T, unsigned long DummyOperations>
ExpensiveCopy<T, DummyOperations>::ExpensiveCopy()
    : _v()
{}

template <typename T, unsigned long DummyOperations>
ExpensiveCopy<T, DummyOperations>::ExpensiveCopy(const T& value)
    : _v(value)
{}

template <typename T, unsigned long DummyOperations>
ExpensiveCopy<T, DummyOperations>::ExpensiveCopy(const ExpensiveCopy& other)
    : _v(other._v)
{
	busy_wait<DummyOperations>();
}

template <typename T, unsigned long DummyOperations>
ExpensiveCopy<T, DummyOperations>&
ExpensiveCopy<T, DummyOperations>::operator=(const ExpensiveCopy& other)
{
	if (this != &other) {
		_v = other._v;
		busy_wait<DummyOperations>();
	}
	return *this;
}

template <typename T, unsigned long DummyOperations>
ExpensiveCopy<T, DummyOperations>::~ExpensiveCopy()
{}

template <typename T, unsigned long DummyOperations>
bool
ExpensiveCopy<T, DummyOperations>::operator==(const ExpensiveCopy& other) const
{
	return _v == other._v;
}

template <typename T, unsigned long DummyOperations>
bool
ExpensiveCopy<T, DummyOperations>::operator!=(const ExpensiveCopy& other) const
{
	return _v != other._v;
}

template <typename T, unsigned long DummyOperations>
bool
ExpensiveCopy<T, DummyOperations>::operator<(const ExpensiveCopy& other) const
{
	return _v < other._v;
}

template <typename T, unsigned long DummyOperations>
bool
ExpensiveCopy<T, DummyOperations>::operator>(const ExpensiveCopy& other) const
{
	return _v > other._v;
}

template <typename T, unsigned long DummyOperations>
bool
ExpensiveCopy<T, DummyOperations>::operator<=(const ExpensiveCopy& other) const
{
	return _v <= other._v;
}

template <typename T, unsigned long DummyOperations>
bool
ExpensiveCopy<T, DummyOperations>::operator>=(const ExpensiveCopy& other) const
{
	return _v >= other._v;
}

template <typename T, unsigned long DummyOperations>
T& ExpensiveCopy<T, DummyOperations>::value() throw()
{
	return _v;
}

template <typename T, unsigned long DummyOperations>
const T& ExpensiveCopy<T, DummyOperations>::value() const throw()
{
	return _v;
}

template <typename T, unsigned long DummyOperations>
std::istream& operator>>(std::istream& is,
                         ExpensiveCopy<T, DummyOperations>& rhs)
{
	is >> rhs.value();
	return is;
}

template <typename T, unsigned long DummyOperations>
std::ostream& operator<<(std::ostream& os,
                         const ExpensiveCopy<T, DummyOperations>& rhs)
{
	os << rhs.value();
	return os;
}
