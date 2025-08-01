#pragma once

#include "preprocessor.hpp"

/**
 * @brief Performs a compile-time assertion that works in C++98
 *
 * This implementation enhances a common template technique to create an
 * assertion by making it work in all scopes.
 *
 * Usage: `STATIC_ASSERT(21 + 21 == 42);`
 * A comment in the same line as STATIC_ASSERT can be used as an error message.
 *
 * How it works:
 * 1. `ft::static_assert::Impl<bool(EXPR)>::static_assertion_failure`:
 * The `Impl` template is intentionally left incomplete for the false case.
 *   - When `EXPR` is true, it resolves to a complete type with a member
 *     `static_assertion_failure` (its value is irrelevant);
 *   - when `EXPR` is false, it resolves to an incomplete type and trying to
 *     access a member results in a compile-time error.
 * This provides the core assertion mechanism.
 *
 * 2. `APPEND_UNIQUE_NUM(...)`: Generates unique enum names, preventing
 * redefinition errors when multiple assertions are used in the same scope.
 *
 * 3. `enum { ... }`: The `enum` wrapper serves three purposes:
 *   - It makes the macro valid in all scopes, including file scope (where
 *     statements are not allowed).
 *   - Since `enum`s can only be initialized with constant expressions, it
 *     ensures that the expression can be evaluated at compile time, preventing
 *     accidental use as runtime assertion.
 *   - It naturally avoids any "unused" warnings.
 *
 * The common `typedef char name[(EXPR) ? 1 : -1]` solution is avoided because
 * it can trigger "-Wunused-local-typedefs" warnings when used inside a
 * function.
 * Another common `1 / ((EXPR) ? 1 : 0)` technique, leveraging division by zero,
 * is also avoided because of its longer error messages.
 *
 * Helpful article:
 * https://web.archive.org/web/20130323104707/https://www.drdobbs.com/compile-time-assertions/184401873
 */
#define STATIC_ASSERT(EXPR)                                               \
	enum {                                                                \
		APPEND_UNIQUE_NUM(static_assert_) =                               \
		    ft::_static_assert::Impl<bool(EXPR)>::static_assertion_failed \
	}

#include "src/assert/static_assert.tpp" // IWYU pragma: export
