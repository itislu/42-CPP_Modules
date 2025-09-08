#pragma once

#include <cstddef>
#include <istream>
#include <ostream>

template <typename T, typename UniqueTag = void>
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

template <typename T, typename UniqueTag>
void swap(OperationCounter<T, UniqueTag>& lhs,
          OperationCounter<T, UniqueTag>& rhs);

template <typename T, typename UniqueTag>
std::istream& operator>>(std::istream& is, OperationCounter<T, UniqueTag>& rhs);
template <typename T, typename UniqueTag>
std::ostream& operator<<(std::ostream& os,
                         const OperationCounter<T, UniqueTag>& rhs);

#include "OperationCounter.tpp" // IWYU pragma: export
