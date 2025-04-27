#pragma once

/**
 * @tparam T Assumed to be a container of integers
 */
template <typename T>
typename T::iterator easyfind(T& container, int to_find);

/**
 * @tparam T Assumed to be a container of integers
 */
template <typename T>
typename T::const_iterator easyfind(const T& container, int to_find);

#include "easyfind.tpp" // IWYU pragma: export
