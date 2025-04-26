#pragma once

#include "libftpp/algorithm.hpp"

using ft::swap;

template <typename T>
T& min(T& a, T& b);

template <typename T>
const T& min(const T& a, const T& b);

template <typename T>
T& max(T& a, T& b);

template <typename T>
const T& max(const T& a, const T& b);

#include "whatever.tpp" // IWYU pragma: export
