#pragma once

#include "../../Expected.hpp"
#include "../../numeric.hpp"
#include "../../type_traits.hpp"
#include "../../utility.hpp"
#include <limits>

namespace ft {

namespace _arithmetic {
enum Error {
	OK,
	NEGATIVE_OVERFLOW,
	POSITIVE_OVERFLOW,
	DIVISION_BY_ZERO
};
template <typename T>
static REQUIRES(ft::is_integral<T>)
(Error) add(T x, T y, T* result) throw();
template <typename T>
static REQUIRES(ft::is_integral<T>)
(Error) sub(T x, T y, T* result) throw();
template <typename T>
static REQUIRES(ft::is_integral<T>)
(Error) mul(T x, T y, T* result) throw();
template <typename T>
static REQUIRES(ft::is_integral<T>)
(Error) div(T x, T y, T* result) throw();
} // namespace _arithmetic

/* Checked arithmetic */

template <typename T>
REQUIRES(ft::is_integral<T>)
((ft::Expected<T, ArithmeticException>)) add_checked(T x, T y)
{
	T result;
	switch (_arithmetic::add(x, y, &result)) {
	case _arithmetic::OK:
		return result;
	case _arithmetic::NEGATIVE_OVERFLOW:
		return ft::Unexpected<ArithmeticException>(
		    ArithmeticNegativeOverflowException("ft::add_checked"));
	case _arithmetic::POSITIVE_OVERFLOW:
		return ft::Unexpected<ArithmeticException>(
		    ArithmeticPositiveOverflowException("ft::add_checked"));
	case _arithmetic::DIVISION_BY_ZERO:
		UNREACHABLE();
	}
	UNREACHABLE();
}

template <typename T>
REQUIRES(ft::is_integral<T>)
((ft::Expected<T, ArithmeticException>)) sub_checked(T x, T y)
{
	T result;
	switch (_arithmetic::sub(x, y, &result)) {
	case _arithmetic::OK:
		return result;
	case _arithmetic::NEGATIVE_OVERFLOW:
		return ft::Unexpected<ArithmeticException>(
		    ArithmeticNegativeOverflowException("ft::sub_checked"));
	case _arithmetic::POSITIVE_OVERFLOW:
		return ft::Unexpected<ArithmeticException>(
		    ArithmeticPositiveOverflowException("ft::sub_checked"));
	case _arithmetic::DIVISION_BY_ZERO:
		UNREACHABLE();
	}
	UNREACHABLE();
}

template <typename T>
REQUIRES(ft::is_integral<T>)
((ft::Expected<T, ArithmeticException>)) mul_checked(T x, T y)
{
	T result;
	switch (_arithmetic::mul(x, y, &result)) {
	case _arithmetic::OK:
		return result;
	case _arithmetic::NEGATIVE_OVERFLOW:
		return ft::Unexpected<ArithmeticException>(
		    ArithmeticNegativeOverflowException("ft::mul_checked"));
	case _arithmetic::POSITIVE_OVERFLOW:
		return ft::Unexpected<ArithmeticException>(
		    ArithmeticPositiveOverflowException("ft::mul_checked"));
	case _arithmetic::DIVISION_BY_ZERO:
		UNREACHABLE();
	}
	UNREACHABLE();
}

template <typename T>
REQUIRES(ft::is_integral<T>)
((ft::Expected<T, ArithmeticException>)) div_checked(T x, T y)
{
	T result;
	switch (_arithmetic::div(x, y, &result)) {
	case _arithmetic::OK:
		return result;
	case _arithmetic::NEGATIVE_OVERFLOW:
		UNREACHABLE();
	case _arithmetic::POSITIVE_OVERFLOW:
		return ft::Unexpected<ArithmeticException>(
		    ArithmeticPositiveOverflowException("ft::div_checked"));
	case _arithmetic::DIVISION_BY_ZERO:
		return ft::Unexpected<ArithmeticException>(
		    ArithmeticDivisionByZeroException("ft::div_checked"));
	}
	UNREACHABLE();
}

/* Saturating arithmetic */

template <typename T>
REQUIRES(ft::is_integral<T>)
(T) add_sat(T x, T y) throw()
{
	T result;
	switch (_arithmetic::add(x, y, &result)) {
	case _arithmetic::OK:
		return result;
	case _arithmetic::NEGATIVE_OVERFLOW:
		return std::numeric_limits<T>::min();
	case _arithmetic::POSITIVE_OVERFLOW:
		return std::numeric_limits<T>::max();
	case _arithmetic::DIVISION_BY_ZERO:
		UNREACHABLE();
	}
	UNREACHABLE();
}

template <typename T>
REQUIRES(ft::is_integral<T>)
(T) sub_sat(T x, T y) throw()
{
	T result;
	switch (_arithmetic::sub(x, y, &result)) {
	case _arithmetic::OK:
		return result;
	case _arithmetic::NEGATIVE_OVERFLOW:
		return std::numeric_limits<T>::min();
	case _arithmetic::POSITIVE_OVERFLOW:
		return std::numeric_limits<T>::max();
	case _arithmetic::DIVISION_BY_ZERO:
		UNREACHABLE();
	}
	UNREACHABLE();
}

template <typename T>
REQUIRES(ft::is_integral<T>)
(T) mul_sat(T x, T y) throw()
{
	T result;
	switch (_arithmetic::mul(x, y, &result)) {
	case _arithmetic::OK:
		return result;
	case _arithmetic::NEGATIVE_OVERFLOW:
		return std::numeric_limits<T>::min();
	case _arithmetic::POSITIVE_OVERFLOW:
		return std::numeric_limits<T>::max();
	case _arithmetic::DIVISION_BY_ZERO:
		UNREACHABLE();
	}
	UNREACHABLE();
}

template <typename T>
REQUIRES(ft::is_integral<T>)
(T) div_sat(T x, T y) throw()
{
	T result;
	switch (_arithmetic::div(x, y, &result)) {
	case _arithmetic::OK:
		return result;
	case _arithmetic::NEGATIVE_OVERFLOW:
		UNREACHABLE();
	case _arithmetic::POSITIVE_OVERFLOW:
		return std::numeric_limits<T>::max();
	case _arithmetic::DIVISION_BY_ZERO:
		if (x > 0) {
			return std::numeric_limits<T>::max();
		}
		if (x < 0) {
			return std::numeric_limits<T>::min();
		}
		return 0; // 0/0
	}
	UNREACHABLE();
}

/* Throwing arithmetic */

template <typename T>
REQUIRES(ft::is_integral<T>)
(T) add_throw(T x, T y)
{
	T result;
	switch (_arithmetic::add(x, y, &result)) {
	case _arithmetic::OK:
		return result;
	case _arithmetic::NEGATIVE_OVERFLOW:
		throw ArithmeticNegativeOverflowException("ft::add_throw");
	case _arithmetic::POSITIVE_OVERFLOW:
		throw ArithmeticPositiveOverflowException("ft::add_throw");
	case _arithmetic::DIVISION_BY_ZERO:
		UNREACHABLE();
	}
	UNREACHABLE();
}

template <typename T>
REQUIRES(ft::is_integral<T>)
(T) sub_throw(T x, T y)
{
	T result;
	switch (_arithmetic::sub(x, y, &result)) {
	case _arithmetic::OK:
		return result;
	case _arithmetic::NEGATIVE_OVERFLOW:
		throw ArithmeticNegativeOverflowException("ft::sub_throw");
	case _arithmetic::POSITIVE_OVERFLOW:
		throw ArithmeticPositiveOverflowException("ft::sub_throw");
	case _arithmetic::DIVISION_BY_ZERO:
		UNREACHABLE();
	}
	UNREACHABLE();
}

template <typename T>
REQUIRES(ft::is_integral<T>)
(T) mul_throw(T x, T y)
{
	T result;
	switch (_arithmetic::mul(x, y, &result)) {
	case _arithmetic::OK:
		return result;
	case _arithmetic::NEGATIVE_OVERFLOW:
		throw ArithmeticNegativeOverflowException("ft::mul_throw");
	case _arithmetic::POSITIVE_OVERFLOW:
		throw ArithmeticPositiveOverflowException("ft::mul_throw");
	case _arithmetic::DIVISION_BY_ZERO:
		UNREACHABLE();
	}
	UNREACHABLE();
}

template <typename T>
REQUIRES(ft::is_integral<T>)
(T) div_throw(T x, T y)
{
	T result;
	switch (_arithmetic::div(x, y, &result)) {
	case _arithmetic::OK:
		return result;
	case _arithmetic::NEGATIVE_OVERFLOW:
		UNREACHABLE();
	case _arithmetic::POSITIVE_OVERFLOW:
		throw ArithmeticPositiveOverflowException("ft::div_throw");
	case _arithmetic::DIVISION_BY_ZERO:
		throw ArithmeticDivisionByZeroException("ft::div_throw");
	}
	UNREACHABLE();
}

namespace _arithmetic {

template <typename T>
static REQUIRES(ft::is_integral<T>)
(Error) add(T x, T y, T* result) throw()
{
	const T max = std::numeric_limits<T>::max();
	if (std::numeric_limits<T>::is_signed) {
		if (x > 0 && y > 0 && x > max - y) {
			return POSITIVE_OVERFLOW;
		}
		const T min = std::numeric_limits<T>::min();
		if (x < 0 && y < 0 && x < min - y) {
			return NEGATIVE_OVERFLOW;
		}
	}
	else {
		// For unsigned types only positive overflow is possible
		if (y > max - x) {
			return POSITIVE_OVERFLOW;
		}
	}
	*result = x + y;
	return OK;
}

template <typename T>
static REQUIRES(ft::is_integral<T>)
(Error) sub(T x, T y, T* result) throw()
{
	if (std::numeric_limits<T>::is_signed) {
		const T max = std::numeric_limits<T>::max();
		const T min = std::numeric_limits<T>::min();
		if (x > 0 && y < 0 && x > max + y) {
			return POSITIVE_OVERFLOW;
		}
		if (x < 0 && y > 0 && x < min + y) {
			return NEGATIVE_OVERFLOW;
		}
	}
	else {
		// For unsigned types only negative overflow is possible
		if (x < y) {
			return NEGATIVE_OVERFLOW;
		}
	}
	*result = x - y;
	return OK;
}

template <typename T>
static REQUIRES(ft::is_integral<T>)
(Error) mul(T x, T y, T* result) throw()
{
	const T max = std::numeric_limits<T>::max();
	if (std::numeric_limits<T>::is_signed) {
		if ((x > 0 && y > 0 && x > max / y)
		    || (x < 0 && y < 0 && x < max / y)) {
			return POSITIVE_OVERFLOW;
		}
		const T min = std::numeric_limits<T>::min();
		if ((x > 0 && y < 0 && y < min / x)
		    || (x < 0 && y > 0 && x < min / y)) {
			return NEGATIVE_OVERFLOW;
		}
	}
	else {
		// For unsigned types only positive overflow is possible
		if (y > 0 && x > max / y) {
			return POSITIVE_OVERFLOW;
		}
	}
	*result = x * y;
	return OK;
}

template <typename T>
static REQUIRES(ft::is_integral<T>)
(Error) div(T x, T y, T* result) throw()
{
	if (y == 0) {
		return DIVISION_BY_ZERO;
	}

	if (std::numeric_limits<T>::is_signed) {
		const T min = std::numeric_limits<T>::min();
		// MIN / -1 positive overflow
		if (x == min && y == -1) {
			return POSITIVE_OVERFLOW;
		}
	}
	*result = x / y;
	return OK;
}

} // namespace _arithmetic

} // namespace ft
