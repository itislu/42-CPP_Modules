#pragma once

#include "whatever.hpp"

template <typename T>
T& min(T& a, T& b)
{
	return (a < b) ? a : b;
}

template <typename T>
const T& min(const T& a, const T& b)
{
	return (a < b) ? a : b;
}

template <typename T>
T& max(T& a, T& b)
{
	return (a > b) ? a : b;
}

template <typename T>
const T& max(const T& a, const T& b)
{
	return (a > b) ? a : b;
}
