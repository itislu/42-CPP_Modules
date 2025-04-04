#pragma once

#include "Optional.hpp"
#include <ios>
#include <new>
#include <string>

namespace ft {

/* starts_with */

/**
 * https://en.cppreference.com/w/cpp/string/basic_string/starts_with
 */
bool starts_with(const std::string& str, const std::string& prefix);
bool starts_with(const std::string& str, char prefix);
bool starts_with(const std::string& str, unsigned char prefix);

/* ends_with */

/**
 * https://en.cppreference.com/w/cpp/string/basic_string/ends_with
 */
bool ends_with(const std::string& str, const std::string& suffix);
bool ends_with(const std::string& str, char suffix);
bool ends_with(const std::string& str, unsigned char suffix);

/* from_string */

/**
 * @brief Converts a string to a specified type
 *
 * @tparam T The type to convert to
 * @param str The string to convert
 * @return T The converted value
 *
 * @throws std::out_of_range When the value is out of the representable range
 * @throws std::invalid_argument When the string cannot be converted to the type
 */
template <typename T>
T from_string(const std::string& str);

/**
 * @brief Converts a string to a specified type without throwing exceptions
 *
 * This is the non-throwing version of the `from_string` function.
 * Instead of throwing exceptions on failure, it returns an empty
 * `ft::Optional`.
 *
 * @tparam T The type to convert to
 * @param str The string to convert
 * @param nothrow A tag (f.e. `std::nothrow`) to indicate the non-throwing
 * behavior
 * @return ft::Optional<T> The converted value wrapped in an `ft::Optional`, or
 * an empty `ft::Optional` if the conversion fails
 */
template <typename T>
ft::Optional<T> from_string(const std::string& str, std::nothrow_t nothrow);

/**
 * @brief Converts a string to a specified type
 *
 * @tparam T The type to convert to
 * @param str The string to convert
 * @param fmt Stream formatting flags that determine how the string is
 * interpreted
 * @return T The converted value
 *
 * @throws std::out_of_range When the value is out of the representable range
 * @throws std::invalid_argument When the string cannot be converted to the type
 */
template <typename T>
T from_string(const std::string& str, std::ios::fmtflags fmt);

/**
 * @brief Converts a string to a specified type without throwing exceptions
 *
 * This is the non-throwing version of the `from_string` function.
 * Instead of throwing exceptions on failure, it returns an empty
 * `ft::Optional`.
 *
 * @tparam T The type to convert to
 * @param str The string to convert
 * @param fmt Stream formatting flags that determine how the string is
 * interpreted
 * @param nothrow A tag (f.e. `std::nothrow`) to indicate the non-throwing
 * behavior
 * @return ft::Optional<T> The converted value wrapped in an `ft::Optional`, or
 * an empty `ft::Optional` if the conversion fails
 */
template <typename T>
ft::Optional<T> from_string(const std::string& str,
                            std::ios::fmtflags fmt,
                            std::nothrow_t nothrow);

/**
 * @brief Converts a string to a boolean.
 *
 * Accepts both alpha (true/false) and numeric (1/0) formats.
 *
 * @param str The string to convert
 * @return bool The converted boolean value
 *
 * @throws std::invalid_argument When the string neither starts with true/false
 * nor 1/0
 */
template <>
inline bool from_string<bool>(const std::string& str);

/**
 * @brief Converts a string to a float
 *
 * @param str The string to convert
 * @return float The converted floating-point value
 *
 * @throws std::out_of_range When the value is out of the representable range
 * @throws std::invalid_argument When the string cannot be converted to a float
 */
template <>
inline float from_string<float>(const std::string& str);

/**
 * @brief Converts a string to a double
 *
 * @param str The string to convert
 * @return double The converted floating-point value
 *
 * @throws std::out_of_range When the value is out of the representable range
 * @throws std::invalid_argument When the string cannot be converted to a double
 */
template <>
inline double from_string<double>(const std::string& str);

/**
 * @brief Converts a string to a long double
 *
 * @param str The string to convert
 * @return long double The converted floating-point value
 *
 * @throws std::out_of_range When the value is out of the representable range
 * @throws std::invalid_argument When the string cannot be converted to a long
 * double
 */
template <>
inline long double from_string<long double>(const std::string& str);

/* to_string */

/**
 * https://en.cppreference.com/w/cpp/string/basic_string/to_string
 */
template <typename T>
std::string to_string(T v, std::ios::fmtflags fmt = std::ios::fmtflags());
template <typename T>
std::string to_string(T* v, std::ios::fmtflags fmt = std::ios::fmtflags());
std::string to_string(bool v, std::ios::fmtflags fmt = std::ios::boolalpha);

/* trim */

std::string& trim(std::string& str);
std::string trim(const std::string& str);

} // namespace ft

#include "src/string/from_string.tpp" // IWYU pragma: export
#include "src/string/to_string.tpp"   // IWYU pragma: export
