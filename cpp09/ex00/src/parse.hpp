#pragma once

#include <ctime>
#include <string>

/**
 * @throws std::invalid_argument When `str` is an invalid date format, is empty,
 * or has excess characters
 * @throws std::out_of_range When impossible date
 */
std::time_t parse_date(const std::string& str);

/**
 * @throws std::invalid_argument When `str` does not represent a valid `double`,
 * is empty, or has excess characters
 * @throws std::out_of_range When the parsed value falls outside the
 * representable range of `double`
 */
double parse_rate(const std::string& str);

/**
 * @throws std::invalid_argument When the parsed `float` is negative or exceeds
 * `max_query_amount`, or `str` does not represent a valid `float`, is empty, or
 * has excess characters
 * @throws std::out_of_range When the parsed value falls outside the
 * representable range of `float`
 */
float parse_amount(const std::string& str, float max_query_amount);
