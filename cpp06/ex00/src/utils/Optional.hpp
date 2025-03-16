#pragma once

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
class Optional {
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
	Optional& operator=(Optional other);

	const T* operator->() const throw();
	T* operator->() throw();
	const T& operator*() const throw();
	T& operator*() throw();
	operator bool() const throw();
	bool has_value() const throw();
	const T& value() const;
	T& value();
	T value_or(const T& default_value) const;
	T& value_or(T& default_value);

	void swap(Optional& other);
	void reset() throw();

private:
	T* _value;
	bool _has_value;
};

template <typename T>
Optional<T> make_optional(const T& value);
template <typename T>
void swap(Optional<T>& a, Optional<T>& b);

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
