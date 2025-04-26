// NOLINTBEGIN(cppcoreguidelines-pro-bounds-pointer-arithmetic)

#pragma once

#include "libftpp/algorithm.hpp"
#include "libftpp/type_traits.hpp"
#include <cstddef>

// Allows only arrays and pointers
// template <typename F, typename Array>
// typename ft::enable_if<ft::is_array<Array>::value>::type
// iter(Array& array, std::size_t size, F func)
// {
// 	for (std::size_t i = 0; i < size; ++i) {
// 		func(array[i]);
// 	}
// }

template <typename F, typename Array>
void iter(Array& array, std::size_t size, F func)
{
	for (std::size_t i = 0; i < size; ++i) {
		func(array[i]);
	}
}

template <typename F, typename Array>
void iter(Array*& array, std::size_t size, F func)
{
	if (array == NULL) {
		return;
	}
	for (std::size_t i = 0; i < size; ++i) {
		func(array[i]);
	}
}

template <typename F, typename T, std::size_t N>
void iter(T (&array)[N], std::size_t size, F func)
{
	std::size_t end = MIN(size, N);
	for (std::size_t i = 0; i < end; ++i) {
		func(array[i]);
	}
}

// template <typename FuncRet, typename Array>
// void iter(Array& array,
//           std::size_t size,
//           FuncRet (*func)(typename ft::remove_extent<Array>::type&))
// {
// 	for (std::size_t i = 0; i < size; ++i) {
// 		func(array[i]);
// 	}
// }

// template <typename FuncRet, typename Array>
// void iter(Array& array,
//           std::size_t size,
//           FuncRet (*func)(const typename ft::remove_extent<Array>::type&))
// {
// 	for (std::size_t i = 0; i < size; ++i) {
// 		func(array[i]);
// 	}
// }

// template <typename FuncRet, typename Array>
// void iter(Array& array,
//           std::size_t size,
//           FuncRet (*func)(volatile typename ft::remove_extent<Array>::type&))
// {
// 	for (std::size_t i = 0; i < size; ++i) {
// 		func(array[i]);
// 	}
// }

// template <typename FuncRet, typename Array>
// void iter(Array& array,
//           std::size_t size,
//           FuncRet (*func)(const volatile typename
//           ft::remove_extent<Array>::type&))
// {
// 	for (std::size_t i = 0; i < size; ++i) {
// 		func(array[i]);
// 	}
// }

// NOLINTEND(cppcoreguidelines-pro-bounds-pointer-arithmetic)
