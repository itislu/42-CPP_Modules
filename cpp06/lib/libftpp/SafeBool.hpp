#pragma once

#include <cstddef>

namespace ft {

namespace _safe_bool {

class SafeBoolBase {
public:
	typedef void (SafeBoolBase::*safe_bool_t)() const;
	void this_type_does_not_support_comparisons() const {}

protected:
	SafeBoolBase() {}
	~SafeBoolBase() {}

private:
	SafeBoolBase(const SafeBoolBase& /*unused*/);
	SafeBoolBase& operator=(const SafeBoolBase& /*unused*/);
};

} // namespace _safe_bool

/**
 * Class to provide boolean tests for derived class but restricting it from
 * taking participation in unwanted expressions (safe bool problem).
 * Implements the Safe Bool idiom using CRTP (Curiously Recurring Template
 * Pattern).
 * https://en.wikibooks.org/wiki/More_C%2B%2B_Idioms/Safe_bool
 *
 * Usage:
 * 1. Derive from this class using CRTP idiom:
 *    `class YourClass : public SafeBool<YourClass>`
 * 2. Implement `bool boolean_test() const throw();`
 */
template <typename Derived = void>
class SafeBool : private _safe_bool::SafeBoolBase {
public:
	operator safe_bool_t() const
	{
		return (static_cast<const Derived*>(this))->boolean_test()
		           ? &SafeBoolBase::this_type_does_not_support_comparisons
		           : NULL;
	}

protected:
	SafeBool() {}
	~SafeBool() {}

private:
	SafeBool(const SafeBool& /*unused*/);
	SafeBool& operator=(const SafeBool& /*unused*/);
};

/**
 * Class to provide boolean tests for derived class but restricting it from
 * taking participation in unwanted expressions (safe bool problem).
 * Implements the Safe Bool idiom using virtual dispatch.
 * https://en.wikibooks.org/wiki/More_C%2B%2B_Idioms/Safe_bool
 *
 * Usage:
 * 1. Derive from this class with no template parameter:
 *    `class YourClass : public SafeBool<>`
 * 2. Implement `bool boolean_test() const throw();`
 *
 * @note If your class is not virtual yet, prefer to give your class as template
 * parameter (CRTP idiom) to avoid your class becoming virtual.
 */
template <>
class SafeBool<void> // NOLINT(cppcoreguidelines-virtual-class-destructor)
    : private _safe_bool::SafeBoolBase {
public:
	operator safe_bool_t() const
	{
		return boolean_test()
		           ? &SafeBoolBase::this_type_does_not_support_comparisons
		           : NULL;
	}

protected:
	SafeBool() {}
	virtual ~SafeBool() {}
	virtual bool boolean_test() const = 0;

private:
	SafeBool(const SafeBool& /*unused*/);
	SafeBool& operator=(const SafeBool& /*unused*/);
};

/**
 * To allow explicit comparison with bool.
 */
template <typename T>
bool operator==(const SafeBool<T>& lhs, bool b)
{
	return b == static_cast<bool>(lhs);
}

template <typename T>
bool operator==(bool b, const SafeBool<T>& rhs)
{
	return b == static_cast<bool>(rhs);
}

template <typename T>
bool operator!=(const SafeBool<T>& lhs, bool b)
{
	return b != static_cast<bool>(lhs);
}

template <typename T>
bool operator!=(bool b, const SafeBool<T>& rhs)
{
	return b != static_cast<bool>(rhs);
}

/**
 * To avoid unwanted comparisons with other types.
 */
template <typename T, typename U>
bool operator==(const SafeBool<T>& lhs, const U& /*rhs*/)
{
	lhs.this_type_does_not_support_comparisons();
	return false;
}

template <typename T, typename U>
bool operator==(const U& /*lhs*/, const SafeBool<T>& rhs)
{
	rhs.this_type_does_not_support_comparisons();
	return false;
}

template <typename T, typename U>
bool operator!=(const SafeBool<T>& lhs, const U& /*rhs*/)
{
	lhs.this_type_does_not_support_comparisons();
	return false;
}

template <typename T, typename U>
bool operator!=(const U& /*lhs*/, const SafeBool<T>& rhs)
{
	rhs.this_type_does_not_support_comparisons();
	return false;
}

} // namespace ft
