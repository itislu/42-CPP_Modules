#pragma once

#include "SafeBool.hpp"
#include "assert.hpp"
#include "type_traits.hpp"
#include <exception>

namespace ft {

struct nullopt_t;
class BadOptionalAccess;

/**
 * https://en.cppreference.com/w/cpp/utility/optional
 */
template <typename T>
class Optional : public ft::SafeBool<Optional<T> > {
private:
	STATIC_ASSERT( // T must not be a reference type
	    !ft::is_reference<T>::value);
	STATIC_ASSERT( // T must not be a function type
	    !ft::is_function<T>::value);
	STATIC_ASSERT( // T must not be an array type
	    !ft::is_array<T>::value);
	STATIC_ASSERT( // T must not be (possibly cv-qualified) void
	    !ft::is_void<T>::value);
	STATIC_ASSERT( // T must not be ft::nullopt_t
	    (!ft::is_same<typename ft::remove_cv<T>::type, ft::nullopt_t>::value));

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

	template <typename F>
	Optional and_then(const F& f) const;
	template <typename F>
	Optional transform(const F& f) const;
	template <typename F>
	Optional or_else(const F& f) const;

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

template <typename T>
bool operator==(const Optional<T>& opt, nullopt_t /*unused*/) throw();
template <typename T>
bool operator==(nullopt_t /*unused*/, const Optional<T>& opt) throw();
template <typename T>
bool operator!=(const Optional<T>& opt, nullopt_t /*unused*/) throw();
template <typename T>
bool operator!=(nullopt_t /*unused*/, const Optional<T>& opt) throw();
template <typename T>
bool operator<(const Optional<T>& opt, nullopt_t /*unused*/) throw();
template <typename T>
bool operator<(nullopt_t /*unused*/, const Optional<T>& opt) throw();
template <typename T>
bool operator<=(const Optional<T>& opt, nullopt_t /*unused*/) throw();
template <typename T>
bool operator<=(nullopt_t /*unused*/, const Optional<T>& opt) throw();
template <typename T>
bool operator>(const Optional<T>& opt, nullopt_t /*unused*/) throw();
template <typename T>
bool operator>(nullopt_t /*unused*/, const Optional<T>& opt) throw();
template <typename T>
bool operator>=(const Optional<T>& opt, nullopt_t /*unused*/) throw();
template <typename T>
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

/**
 * https://en.cppreference.com/w/cpp/utility/optional/nullopt_t
 */
struct nullopt_t {
	explicit nullopt_t(int /*unused*/) throw();
};

/**
 * https://en.cppreference.com/w/cpp/utility/optional/bad_optional_access
 */
class BadOptionalAccess : public std::exception {
public:
	const char* what() const throw();
};

/**
 * https://en.cppreference.com/w/cpp/utility/optional/nullopt
 */
extern const nullopt_t nullopt;

} // namespace ft

#include "src/Optional/Optional.tpp" // IWYU pragma: export
