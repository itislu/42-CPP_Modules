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
    : v(value)
{}

template <typename T, unsigned long DummyOperations>
bool operator==(const ExpensiveComparison<T, DummyOperations>& lhs,
                const ExpensiveComparison<T, DummyOperations>& rhs)
{
	busy_wait<DummyOperations>();
	return lhs.v == rhs.v;
}

template <typename T, unsigned long DummyOperations>
bool operator!=(const ExpensiveComparison<T, DummyOperations>& lhs,
                const ExpensiveComparison<T, DummyOperations>& rhs)
{
	busy_wait<DummyOperations>();
	return lhs.v != rhs.v;
}

template <typename T, unsigned long DummyOperations>
bool operator<(const ExpensiveComparison<T, DummyOperations>& lhs,
               const ExpensiveComparison<T, DummyOperations>& rhs)
{
	busy_wait<DummyOperations>();
	return lhs.v < rhs.v;
}

template <typename T, unsigned long DummyOperations>
bool operator>(const ExpensiveComparison<T, DummyOperations>& lhs,
               const ExpensiveComparison<T, DummyOperations>& rhs)
{
	busy_wait<DummyOperations>();
	return lhs.v > rhs.v;
}

template <typename T, unsigned long DummyOperations>
bool operator<=(const ExpensiveComparison<T, DummyOperations>& lhs,
                const ExpensiveComparison<T, DummyOperations>& rhs)
{
	busy_wait<DummyOperations>();
	return lhs.v <= rhs.v;
}

template <typename T, unsigned long DummyOperations>
bool operator>=(const ExpensiveComparison<T, DummyOperations>& lhs,
                const ExpensiveComparison<T, DummyOperations>& rhs)
{
	busy_wait<DummyOperations>();
	return lhs.v >= rhs.v;
}

template <typename T, unsigned long DummyOperations>
std::istream& operator>>(std::istream& is,
                         ExpensiveComparison<T, DummyOperations>& rhs)
{
	is >> rhs.v;
	return is;
}

template <typename T, unsigned long DummyOperations>
std::ostream& operator<<(std::ostream& os,
                         const ExpensiveComparison<T, DummyOperations>& rhs)
{
	os << rhs.v;
	return os;
}
