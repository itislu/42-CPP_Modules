#pragma once

#include "libftpp/type_traits.hpp"
#include <cstddef>

/* Arrays of known bound */
template <typename FuncRet, typename FuncArg, typename ArrayOf, std::size_t N>
void iter(ArrayOf (&array)[N], std::size_t size, FuncRet (*func)(FuncArg));

/* Arrays of unknown bound */
template <typename FuncRet, typename FuncArg, typename Array>
typename ft::enable_if<ft::is_unbounded_array<Array>::value>::type
iter(Array& array, std::size_t size, FuncRet (*func)(FuncArg));

/* Dynamic arrays */
template <typename FuncRet, typename FuncArg, typename Ptr>
typename ft::enable_if<ft::is_pointer<Ptr>::value>::type
iter(Ptr& ptr, std::size_t size, FuncRet (*func)(FuncArg));

/* Complex types - comment out if not wished to support complex types */
template <typename FuncRet, typename FuncArg, typename Complex>
typename ft::enable_if<!ft::is_array<Complex>::value
                       && !ft::is_pointer<Complex>::value>::type
iter(Complex& complex, std::size_t size, FuncRet (*func)(FuncArg));

#include "iter.tpp" // IWYU pragma: export
