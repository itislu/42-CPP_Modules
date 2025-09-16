#pragma once

#include <istream>
#include <ostream>

/**
 * Trivially copyable (i.e., `memcpy`-able).
 */
template <typename T, unsigned long DummyOperations>
struct ExpensiveComparison {
	ExpensiveComparison();
	// Implicit conversion wanted for thin wrapper type.
	// NOLINTNEXTLINE(google-explicit-constructor)
	ExpensiveComparison(const T& value);

	bool operator==(const ExpensiveComparison& other) const;
	bool operator!=(const ExpensiveComparison& other) const;
	bool operator<(const ExpensiveComparison& other) const;
	bool operator>(const ExpensiveComparison& other) const;
	bool operator<=(const ExpensiveComparison& other) const;
	bool operator>=(const ExpensiveComparison& other) const;

	T& value() throw();
	const T& value() const throw();

private:
	T _v;
};

template <typename T, unsigned long DummyOperations>
std::istream& operator>>(std::istream& is,
                         ExpensiveComparison<T, DummyOperations>& rhs);

template <typename T, unsigned long DummyOperations>
std::ostream& operator<<(std::ostream& os,
                         const ExpensiveComparison<T, DummyOperations>& rhs);

#include "ExpensiveComparison.tpp" // IWYU pragma: export
