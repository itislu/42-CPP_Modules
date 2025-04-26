#pragma once

#include "iter.hpp"
#include "libftpp/algorithm.hpp"
#include "libftpp/format.hpp"
#include "libftpp/type_traits.hpp"
#include <cstddef>
#include <iostream>

/* Arrays of known bound */
template <typename FuncRet, typename FuncArg, typename ArrayOf, std::size_t N>
void iter(ArrayOf (&array)[N], std::size_t size, FuncRet (*func)(FuncArg))
{
	std::cerr << ft::log::info("iter(ArrayOf (&array)[N], ...) chosen") << '\n';

	std::size_t end = MIN(size, N);
	for (std::size_t i = 0; i < end; ++i) {
		func(array[i]);
	}
}

/* Arrays of unknown bound */
template <typename FuncRet, typename FuncArg, typename Array>
typename ft::enable_if<ft::is_unbounded_array<Array>::value>::type
iter(Array& array, std::size_t size, FuncRet (*func)(FuncArg))
{
	std::cerr << ft::log::info("iter(Array& array, ...) chosen") << '\n';

	for (std::size_t i = 0; i < size; ++i) {
		func(array[i]);
	}
}

/* Dynamic arrays */
template <typename FuncRet, typename FuncArg, typename Ptr>
typename ft::enable_if<ft::is_pointer<Ptr>::value>::type
iter(Ptr& ptr, std::size_t size, FuncRet (*func)(FuncArg))
{
	std::cerr << ft::log::info("iter(Ptr& ptr, ...) chosen") << '\n';

	if (ptr == NULL) {
		return;
	}
	for (std::size_t i = 0; i < size; ++i) {
		func(ptr[i]);
	}
}

/* Complex types - comment out if not wished to support complex types */
template <typename FuncRet, typename FuncArg, typename Complex>
typename ft::enable_if<!ft::is_array<Complex>::value
                       && !ft::is_pointer<Complex>::value>::type
iter(Complex& complex, std::size_t size, FuncRet (*func)(FuncArg))
{
	std::cerr << ft::log::info("iter(Complex& complex, ...) chosen") << '\n';

	for (std::size_t i = 0; i < size; ++i) {
		func(complex[i]);
	}
}
