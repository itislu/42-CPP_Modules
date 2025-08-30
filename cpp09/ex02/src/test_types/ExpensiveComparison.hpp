#pragma once

#include <istream>
#include <ostream>

/**
 * Is POD.
 */
template <typename T, unsigned long DummyOperations>
struct ExpensiveComparison {
	ExpensiveComparison();
	// Implicit conversion wanted for thin wrapper type.
	// NOLINTNEXTLINE(google-explicit-constructor)
	ExpensiveComparison(const T& value);

    // Thin POD type.
    // NOLINTNEXTLINE(misc-non-private-member-variables-in-classes)
	T v;
};

template <typename T, unsigned long DummyOperations>
bool operator==(const ExpensiveComparison<T, DummyOperations>& lhs,
                const ExpensiveComparison<T, DummyOperations>& rhs);

template <typename T, unsigned long DummyOperations>
bool operator!=(const ExpensiveComparison<T, DummyOperations>& lhs,
                const ExpensiveComparison<T, DummyOperations>& rhs);

template <typename T, unsigned long DummyOperations>
bool operator<(const ExpensiveComparison<T, DummyOperations>& lhs,
               const ExpensiveComparison<T, DummyOperations>& rhs);

template <typename T, unsigned long DummyOperations>
bool operator>(const ExpensiveComparison<T, DummyOperations>& lhs,
               const ExpensiveComparison<T, DummyOperations>& rhs);

template <typename T, unsigned long DummyOperations>
bool operator<=(const ExpensiveComparison<T, DummyOperations>& lhs,
                const ExpensiveComparison<T, DummyOperations>& rhs);

template <typename T, unsigned long DummyOperations>
bool operator>=(const ExpensiveComparison<T, DummyOperations>& lhs,
                const ExpensiveComparison<T, DummyOperations>& rhs);

template <typename T, unsigned long DummyOperations>
std::istream& operator>>(std::istream& is,
                         ExpensiveComparison<T, DummyOperations>& rhs);

template <typename T, unsigned long DummyOperations>
std::ostream& operator<<(std::ostream& os,
                         const ExpensiveComparison<T, DummyOperations>& rhs);

#include "ExpensiveComparison.tpp" // IWYU pragma: export
