#pragma once

#include <cstddef>
#include <istream>
#include <ostream>

template <typename T>
class OperationCounter {
public:
	static std::size_t comparisons() throw();
	static std::size_t copies() throw();
	static void reset() throw();

	OperationCounter();
	// Implicit conversion wanted for thin wrapper type.
	// NOLINTNEXTLINE(google-explicit-constructor)
	OperationCounter(const T& v);
	OperationCounter(const OperationCounter& other);
	OperationCounter& operator=(const OperationCounter& other);
	~OperationCounter();

	bool operator==(const OperationCounter& other) const;
	bool operator!=(const OperationCounter& other) const;
	bool operator<(const OperationCounter& other) const;
	bool operator>(const OperationCounter& other) const;
	bool operator<=(const OperationCounter& other) const;
	bool operator>=(const OperationCounter& other) const;

	void swap(OperationCounter& other);

	T& value() throw();
	const T& value() const throw();

private:
	static std::size_t _comparisons;
	static std::size_t _copies;
	T _v;
};

template <typename T>
void swap(OperationCounter<T>& lhs, OperationCounter<T>& rhs);

template <typename T>
std::istream& operator>>(std::istream& is, OperationCounter<T>& rhs);
template <typename T>
std::ostream& operator<<(std::ostream& os, const OperationCounter<T>& rhs);

#include "OperationCounter.tpp" // IWYU pragma: export
