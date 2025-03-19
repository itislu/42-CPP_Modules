#pragma once

#include "SafeBool.hpp"
#include <exception>

namespace utils {

class BadOptionalAccess : public std::exception {
public:
	const char* what() const throw();
};

struct nullopt_t {
	explicit nullopt_t(int /*unused*/) throw();
};

extern const nullopt_t nullopt;

template <typename T>
class Optional : public SafeBool<Optional<T> > {
public:
	Optional() throw();
	Optional(nullopt_t /*unused*/) throw();
	Optional(const Optional& other);
	template <typename U>
	Optional(const Optional<U>& other);
	template <typename U>
	Optional(const U& value);
	~Optional();

	Optional& operator=(nullopt_t /*unused*/) throw();
	Optional& operator=(Optional other) throw();

	const T* operator->() const throw();
	T* operator->() throw();
	const T& operator*() const throw();
	T& operator*() throw();
	bool boolean_test() const throw();
	bool has_value() const throw();
	const T& value() const;
	T& value();
	template <typename U>
	T value_or(const U& default_value) const;

	void swap(Optional& other) throw();
	void reset() throw();

private:
	T* _value;
};

template <typename T>
Optional<T> make_optional(const T& value);
template <typename T>
void swap(Optional<T>& lhs, Optional<T>& rhs) throw();

template <typename T, typename U>
bool operator==(const Optional<T>& lhs, const Optional<U>& rhs);
template <typename T, typename U>
bool operator!=(const Optional<T>& lhs, const Optional<U>& rhs);
template <typename T, typename U>
bool operator<(const Optional<T>& lhs, const Optional<U>& rhs);
template <typename T, typename U>
bool operator<=(const Optional<T>& lhs, const Optional<U>& rhs);
template <typename T, typename U>
bool operator>(const Optional<T>& lhs, const Optional<U>& rhs);
template <typename T, typename U>
bool operator>=(const Optional<T>& lhs, const Optional<U>& rhs);

template <class T>
bool operator==(const Optional<T>& opt, nullopt_t /*unused*/) throw();
template <class T>
bool operator==(nullopt_t /*unused*/, const Optional<T>& opt) throw();
template <class T>
bool operator!=(const Optional<T>& opt, nullopt_t /*unused*/) throw();
template <class T>
bool operator!=(nullopt_t /*unused*/, const Optional<T>& opt) throw();
template <class T>
bool operator<(const Optional<T>& opt, nullopt_t /*unused*/) throw();
template <class T>
bool operator<(nullopt_t /*unused*/, const Optional<T>& opt) throw();
template <class T>
bool operator<=(const Optional<T>& opt, nullopt_t /*unused*/) throw();
template <class T>
bool operator<=(nullopt_t /*unused*/, const Optional<T>& opt) throw();
template <class T>
bool operator>(const Optional<T>& opt, nullopt_t /*unused*/) throw();
template <class T>
bool operator>(nullopt_t /*unused*/, const Optional<T>& opt) throw();
template <class T>
bool operator>=(const Optional<T>& opt, nullopt_t /*unused*/) throw();
template <class T>
bool operator>=(nullopt_t /*unused*/, const Optional<T>& opt) throw();

template <typename T, typename U>
bool operator==(const Optional<T>& opt, const U& value);
template <typename U, typename T>
bool operator==(const U& value, const Optional<T>& opt);
template <typename T, typename U>
bool operator!=(const Optional<T>& opt, const U& value);
template <typename U, typename T>
bool operator!=(const U& value, const Optional<T>& opt);
template <typename T, typename U>
bool operator<(const Optional<T>& opt, const U& value);
template <typename U, typename T>
bool operator<(const U& value, const Optional<T>& opt);
template <typename T, typename U>
bool operator<=(const Optional<T>& opt, const U& value);
template <typename U, typename T>
bool operator<=(const U& value, const Optional<T>& opt);
template <typename T, typename U>
bool operator>(const Optional<T>& opt, const U& value);
template <typename U, typename T>
bool operator>(const U& value, const Optional<T>& opt);
template <typename T, typename U>
bool operator>=(const Optional<T>& opt, const U& value);
template <typename U, typename T>
bool operator>=(const U& value, const Optional<T>& opt);

} // namespace utils

#include "Optional.tpp" // IWYU pragma: export
