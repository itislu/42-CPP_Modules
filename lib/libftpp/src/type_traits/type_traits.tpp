#pragma once

#include "../../assert.hpp" // IWYU pragma: keep
#include "../../type_traits.hpp"
#include <cstddef>
#include <limits>

namespace ft {

/* Base classes */

/* integral_constant */
template <typename T, T v>
integral_constant<T, v>::operator integral_constant<T, v>::value_type() const
    throw()
{
	return value;
}

template <typename T, T v>
typename integral_constant<T, v>::value_type
integral_constant<T, v>::operator()() const throw()
{
	return value;
}

/**
 * Out-of-class definition required for ODR-usage (taking address or binding to
 * reference).
 * https://listarchives.boost.org/Archives/boost/2003/01/41847.php
 */
template <typename T, T v>
const T integral_constant<T, v>::value;

/* Unary type traits */

/* is_void */
template <typename T>
struct is_void : is_same<typename remove_cv<T>::type, void> {};

/* is_integral */
template <typename T>
struct is_integral : bool_constant<std::numeric_limits<T>::is_integer> {};

/* is_floating_point */
template <typename T>
struct is_floating_point
    : bool_constant<std::numeric_limits<T>::is_specialized
                    && !std::numeric_limits<T>::is_integer> {};

/* is_array */
template <typename T>
struct is_array : false_type {};

template <typename T>
struct is_array<T[]> : true_type {};

template <typename T, std::size_t N>
struct is_array<T[N]> : true_type {};

/* is_function */
template <typename T>
struct is_function
    : bool_constant<!is_const<const T>::value && !is_reference<T>::value> {};

/* is_pointer */
template <typename T>
struct is_pointer : conditional<is_const<T>::value || is_volatile<T>::value,
                                is_pointer<typename remove_cv<T>::type>,
                                false_type>::type {};

template <typename T>
struct is_pointer<T*> : true_type {};

/* is_lvalue_reference */
template <typename>
struct is_lvalue_reference : false_type {};

template <typename T>
struct is_lvalue_reference<T&> : true_type {};

/* is_object */
template <typename T>
struct is_object
    : bool_constant<!is_function<T>::value && !is_reference<T>::value
                    && !is_void<T>::value> {};

/* is_reference */
template <typename T>
struct is_reference : is_lvalue_reference<T> {};

/* is_const */
template <typename>
struct is_const : false_type {};

template <typename T>
struct is_const<const T> : true_type {};

/* is_volatile */
template <typename>
struct is_volatile : false_type {};

template <typename T>
struct is_volatile<volatile T> : true_type {};

/* is_abstract */
#if defined(__clang__) && defined(__has_feature)
#	if __has_feature(is_abstract)
#		define BUILTIN_IS_ABSTRACT(T) __is_abstract(T)
#	endif
#elif defined(__GNUC__)                                         \
    && (__GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 3))
// Introduced to gcc in commit cb68ec50055e516ac270a043f772935561b01968
#	define BUILTIN_IS_ABSTRACT(T) __is_abstract(T)
#elif defined(_MSC_VER) && _MSC_VER >= 1400
// Appears in Visual Studio 2005 Docs, but not in 2003
#	define BUILTIN_IS_ABSTRACT(T) __is_abstract(T)
#endif

#ifdef BUILTIN_IS_ABSTRACT

template <typename T>
struct is_abstract : bool_constant<BUILTIN_IS_ABSTRACT(T)> {};

#else

/**
 * Fallback implementation.
 * Relies on arrays of abstract class type causing type deduction failure.
 * (DR 337 - https://cplusplus.github.io/CWG/issues/337.html)
 * Original implementation:
 * https://groups.google.com/g/comp.lang.c++.moderated/c/C6gvK2tB_kY/m/ByKtefbsO3UJ
 *
 * However, following DR 1640, the standard was revised with P0929R2 and arrays
 * of abstract class types should not cause type deduction failure anymore.
 * - https://cplusplus.github.io/CWG/issues/1640.html
 * - https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2018/p0929r2.html
 *
 * gcc implemented this revision with gcc 11 and therefore this fallback
 * implementation would not work from there on anymore (not a problem because
 * the builtin gets chosen anyway).
 * Discussion: https://gcc.gnu.org/bugzilla/show_bug.cgi?id=17232
 *
 * For clang this implementation would still work until at least version 20.1.0
 * (latest tested).
 */
namespace _is_abstract {
template <typename T, typename = void>
struct Impl;
} // namespace _is_abstract

template <typename T>
struct is_abstract : bool_constant<_is_abstract::Impl<T>::value> {};

namespace _is_abstract {

template <typename T, typename /*= void*/>
struct Impl {
private:
	/**
	 * T must be a complete type. Further, if T is a template then this also
	 * ensures to instantiate it, which is required to get the correct answer.
	 */
	STATIC_ASSERT(sizeof(T) != 0); // T must be a complete type

	template <typename U, typename = void>
	struct can_form_array : true_type {};

	template <typename U>
	struct can_form_array<U, typename voider<U[1]>::type> : false_type {};

public:
	static const bool value = can_form_array<T>::value;
};

/**
 * Filter out types for which sizeof (completeness check) would hard error or
 * which also cannot form arrays.
 */
template <typename T>
struct Impl<T,
            typename enable_if<is_function<T>::value || is_reference<T>::value
                               || is_unbounded_array<T>::value
                               || is_void<T>::value>::type> : false_type {};

} // namespace _is_abstract

#endif

/* is_bounded_array */
template <typename>
struct is_bounded_array : false_type {};

template <typename T, std::size_t N>
struct is_bounded_array<T[N]> : true_type {};

/* is_unbounded_array */
template <typename>
struct is_unbounded_array : false_type {};

template <typename T>
struct is_unbounded_array<T[]> : true_type {};

/* Property queries */

/* rank */
template <typename>
struct rank : integral_constant<std::size_t, 0> {};

template <typename T>
struct rank<T[]> : integral_constant<std::size_t, 1 + rank<T>::value> {};

template <typename T, std::size_t N>
struct rank<T[N]> : integral_constant<std::size_t, 1 + rank<T>::value> {};

/* extent */
template <typename T, unsigned N /*= 0*/>
struct extent : integral_constant<std::size_t, 0> {};

template <typename T, unsigned N>
struct extent<T[], N>
    : integral_constant<std::size_t, N == 0 ? 0 : extent<T, N - 1>::value> {};

template <typename T, std::size_t I, unsigned N>
struct extent<T[I], N>
    : integral_constant<std::size_t, N == 0 ? I : extent<T, N - 1>::value> {};

/* Type relationships */

/* is_same */
template <typename T, typename U>
struct is_same : false_type {};

template <typename T>
struct is_same<T, T> : true_type {};

/* is_convertible */
#if defined(__clang__) && defined(__has_feature)
#	if __has_feature(is_convertible_to)
#		define BUILTIN_IS_CONVERTIBLE(FROM, TO) __is_convertible_to(FROM, TO)
#	endif
#elif defined(__GNUC__)                                           \
    && (__GNUC__ > 13 || (__GNUC__ == 13 && __GNUC_MINOR__ >= 4))
// Buggy 13.1: https://gcc.gnu.org/bugzilla/show_bug.cgi?id=106784
// Fixed 13.4: https://gcc.gnu.org/bugzilla/show_bug.cgi?id=109680
// Related writeup about "Abominable Function Types":
// https://www.open-std.org/JTC1/SC22/WG21/docs/papers/2015/p0172r0.html
#	define BUILTIN_IS_CONVERTIBLE(FROM, TO) __is_convertible(FROM, TO)
#elif defined(_MSC_VER) && _MSC_VER >= 1400
// Appears in Visual Studio 2005 Docs, but not in 2003
#	define BUILTIN_IS_CONVERTIBLE(FROM, TO) __is_convertible_to(FROM, TO)
#endif

#ifdef BUILTIN_IS_CONVERTIBLE

template <typename From, typename To>
struct is_convertible : bool_constant<BUILTIN_IS_CONVERTIBLE(From, To)> {};

#else

namespace _is_convertible {
template <typename From, typename To, typename = void>
struct Impl;
} // namespace _is_convertible

template <typename From, typename To>
struct is_convertible : bool_constant<_is_convertible::Impl<From, To>::value> {
};

template <typename From>
struct is_convertible<From, void> : false_type {};

template <typename To>
struct is_convertible<void, To> : false_type {};

template <>
struct is_convertible<void, void> : true_type {};

namespace _is_convertible {

template <typename From>
struct is_impossible_source;
template <typename To>
struct is_impossible_target;
template <typename From, typename To>
struct is_impossible_abstract_to_ref;
template <typename From, typename To>
struct is_impossible_array_to_ref;

/**
 * Uses SFINAE with function overload resolution to determine if a value of type
 * `From` can be implicitly converted to `To`.
 */
template <typename From, typename To, typename /*= void*/>
struct Impl {
private:
	/**
	 * Arrays, functions and abstract classes cannot be returned by value, so
	 * return by reference. Conversions where this would effect the result are
	 * checked seperately in a template specialization.
	 * Everything else is returned by value.
	 */
	static
	    typename conditional<is_array<From>::value || is_function<From>::value
	                             || is_abstract<From>::value,
	                         typename add_lvalue_reference<From>::type,
	                         From>::type
	    make_from();

	static yes_type test(To);
	static no_type test(...);

public:
	static const bool value = sizeof(test(make_from())) == sizeof(yes_type);
};

/**
 * Certain conversions are known to be impossible. They are separate because
 * they are not SFINAE-friendly and would otherwise cause compilation errors or
 * incorrect results.
 */
template <typename From, typename To>
struct Impl<
    From,
    To,
    typename enable_if<is_impossible_source<From>::value
                       || is_impossible_target<To>::value
                       || is_impossible_abstract_to_ref<From, To>::value
                       || is_impossible_array_to_ref<From, To>::value>::type>
    : false_type {};

// Example: `is_convertible<int() const, int (*)()>`
template <typename From>
struct is_impossible_source
    : bool_constant<
          is_function<From>::value
          && is_same<typename add_lvalue_reference<From>::type, From>::value> {
};

// Example: `is_convertible<Abstract, Abstract>`
template <typename To>
struct is_impossible_target
    : bool_constant<is_array<To>::value || is_function<To>::value
                    || (is_abstract<To>::value && !is_reference<To>::value)> {};

// Example: `is_convertible<Abstract, Abstract&>`
template <typename From, typename To>
struct is_impossible_abstract_to_ref
    : bool_constant<is_abstract<From>::value && !is_reference<From>::value
                    && is_nonconst_lvalue_reference<To>::value> {};

// Example: `is_convertible<int[2], int (&)[2]>`
template <typename From, typename To>
struct is_impossible_array_to_ref
    : bool_constant<is_array<From>::value
                    && is_nonconst_lvalue_reference<To>::value> {};

} // namespace _is_convertible

#endif

/* Type transformations */

/* remove_cv */
template <typename T>
struct remove_cv
    : type_identity<
          typename remove_volatile<typename remove_const<T>::type>::type> {};

/* remove_const */
template <typename T>
struct remove_const : type_identity<T> {};

template <typename T>
struct remove_const<const T> : type_identity<T> {};

/* remove_volatile */
template <typename T>
struct remove_volatile : type_identity<T> {};

template <typename T>
struct remove_volatile<volatile T> : type_identity<T> {};

/* add_cv */
template <typename T>
struct add_cv
    : type_identity<typename add_volatile<typename add_const<T>::type>::type> {
};

/* add_const */
template <typename T>
struct add_const : type_identity<const T> {};

/* add_volatile */
template <typename T>
struct add_volatile : type_identity<volatile T> {};

/* remove_reference */
template <typename T>
struct remove_reference : type_identity<T> {};

template <typename T>
struct remove_reference<T&> : type_identity<T> {};

/* add_lvalue_reference */
namespace _add_lvalue_reference {
template <typename T, typename = void>
struct Impl;
} // namespace _add_lvalue_reference

template <typename T>
struct add_lvalue_reference : _add_lvalue_reference::Impl<T> {};

namespace _add_lvalue_reference {

template <typename T, typename /*= void*/>
struct Impl : type_identity<T> {};

template <typename T>
struct Impl<T, typename voider<T&>::type> : type_identity<T&> {};

} // namespace _add_lvalue_reference

/* remove_extent */
template <typename T>
struct remove_extent : type_identity<T> {};

template <typename T>
struct remove_extent<T[]> : type_identity<T> {};

template <typename T, std::size_t N>
struct remove_extent<T[N]> : type_identity<T> {};

/* remove_all_extents */
template <typename T>
struct remove_all_extents : type_identity<T> {};

template <typename T>
struct remove_all_extents<T[]> : remove_all_extents<T> {};

template <typename T, std::size_t N>
struct remove_all_extents<T[N]> : remove_all_extents<T> {};

/* remove_pointer */
template <typename T>
struct remove_pointer : conditional<is_pointer<T>::value,
                                    remove_pointer<typename remove_cv<T>::type>,
                                    type_identity<T> >::type {};

template <typename T>
struct remove_pointer<T*> : type_identity<T> {};

/* enable_if */
template <bool, typename T /*= void*/>
struct enable_if : type_identity<T> {};

template <typename T>
struct enable_if<false, T> {};

/* conditional */
template <bool, typename T, typename>
struct conditional : type_identity<T> {};

template <typename T, typename F>
struct conditional<false, T, F> : type_identity<F> {};

/* voider (void_t) */
template <typename /*= void*/,
          typename /*= void*/,
          typename /*= void*/,
          typename /*= void*/,
          typename /*= void*/,
          typename /*= void*/,
          typename /*= void*/,
          typename /*= void*/,
          typename /*= void*/,
          typename /*= void*/>
struct voider : type_identity<void> {};

/* Custom type traits */

/**
 * If `T` is a reference type then `is_const<T>::value` is always `false`. The
 * proper way to check a potentially-reference type for constness is to remove
 * the reference first.
 */
template <typename T>
struct is_nonconst_lvalue_reference
    : bool_constant<is_lvalue_reference<T>::value
                    && !is_const<typename remove_reference<T>::type>::value> {};

} // namespace ft
