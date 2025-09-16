#pragma once

#include "ExpensiveComparison.hpp"
#include "busy_wait.hpp"
#include <istream>
#include <ostream>

template <typename T, unsigned long DummyOperations>
ExpensiveComparison<T, DummyOperations>::ExpensiveComparison()
{}

template <typename T, unsigned long DummyOperations>
ExpensiveComparison<T, DummyOperations>::ExpensiveComparison(const T& value)
    : _v(value)
{}

template <typename T, unsigned long DummyOperations>
bool ExpensiveComparison<T, DummyOperations>::operator==(
    const ExpensiveComparison& other) const
{
	busy_wait<DummyOperations>();
	return _v == other._v;
}

template <typename T, unsigned long DummyOperations>
bool ExpensiveComparison<T, DummyOperations>::operator!=(
    const ExpensiveComparison& other) const
{
	busy_wait<DummyOperations>();
	return _v != other._v;
}

template <typename T, unsigned long DummyOperations>
bool ExpensiveComparison<T, DummyOperations>::operator<(
    const ExpensiveComparison& other) const
{
	busy_wait<DummyOperations>();
	return _v < other._v;
}

template <typename T, unsigned long DummyOperations>
bool ExpensiveComparison<T, DummyOperations>::operator>(
    const ExpensiveComparison& other) const
{
	busy_wait<DummyOperations>();
	return _v > other._v;
}

template <typename T, unsigned long DummyOperations>
bool ExpensiveComparison<T, DummyOperations>::operator<=(
    const ExpensiveComparison& other) const
{
	busy_wait<DummyOperations>();
	return _v <= other._v;
}

template <typename T, unsigned long DummyOperations>
bool ExpensiveComparison<T, DummyOperations>::operator>=(
    const ExpensiveComparison& other) const
{
	busy_wait<DummyOperations>();
	return _v >= other._v;
}

template <typename T, unsigned long DummyOperations>
T& ExpensiveComparison<T, DummyOperations>::value() throw()
{
	return _v;
}

template <typename T, unsigned long DummyOperations>
const T& ExpensiveComparison<T, DummyOperations>::value() const throw()
{
	return _v;
}

template <typename T, unsigned long DummyOperations>
std::istream& operator>>(std::istream& is,
                         ExpensiveComparison<T, DummyOperations>& rhs)
{
	is >> rhs.value();
	return is;
}

template <typename T, unsigned long DummyOperations>
std::ostream& operator<<(std::ostream& os,
                         const ExpensiveComparison<T, DummyOperations>& rhs)
{
	os << rhs.value();
	return os;
}
