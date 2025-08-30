#pragma once

#include <istream>
#include <ostream>

template <typename T, unsigned long DummyOperations>
class ExpensiveCopy {
public:
	ExpensiveCopy();
	// Implicit conversion wanted for thin wrapper type.
	// NOLINTNEXTLINE(google-explicit-constructor)
	ExpensiveCopy(const T& value);
	ExpensiveCopy(const ExpensiveCopy& other);
	ExpensiveCopy& operator=(const ExpensiveCopy& other);
	~ExpensiveCopy();

	bool operator==(const ExpensiveCopy& other) const;
	bool operator!=(const ExpensiveCopy& other) const;
	bool operator<(const ExpensiveCopy& other) const;
	bool operator>(const ExpensiveCopy& other) const;
	bool operator<=(const ExpensiveCopy& other) const;
	bool operator>=(const ExpensiveCopy& other) const;

	T& value();
	const T& value() const;

private:
	T _v;
};

template <typename T, unsigned long DummyOperations>
std::istream& operator>>(std::istream& is,
                         ExpensiveCopy<T, DummyOperations>& rhs);

template <typename T, unsigned long DummyOperations>
std::ostream& operator<<(std::ostream& os,
                         const ExpensiveCopy<T, DummyOperations>& rhs);

#include "ExpensiveCopy.tpp"
