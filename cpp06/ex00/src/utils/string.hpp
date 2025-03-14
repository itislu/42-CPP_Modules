#pragma once

#include <string>

namespace utils {
namespace string {

template <typename T>
T from_string(const std::string& str);
template <>
inline bool from_string<bool>(const std::string& str);
template <>
inline float from_string<float>(const std::string& str);
template <>
inline double from_string<double>(const std::string& str);
template <>
inline long double from_string<long double>(const std::string& str);

template <typename T>
std::string to_string(T v);
template <typename T>
std::string to_string(T* v);
template <>
inline std::string to_string(bool v);

template <typename InputIterator,
          typename OutputIterator,
          typename UnaryOperator>
OutputIterator transform(InputIterator first,
                         InputIterator last,
                         OutputIterator result,
                         UnaryOperator op);

std::string& trim(std::string& str);
std::string trim(const std::string& str);

} // namespace string
} // namespace utils

#include "string.tpp" // IWYU pragma: export
