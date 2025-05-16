#pragma once

#include <ctime>
#include <string>

/**
 * @throws ft::Exception When `str` is in an invalid date format or represents
 * an impossible date, is empty, or has excess characters
 */
std::time_t parse_date(const std::string& str);

/**
 * @throws ft::Exception When the parsed `double` is negative, or `str` does not
 * represent a valid `double`, is empty, or has excess characters
 */
double parse_rate(const std::string& str);

/**
 * @throws ft::Exception When the parsed `float` is negative or exceeds
 * `max_query_amount`, or `str` does not represent a valid `float`, is empty, or
 * has excess characters
 */
float parse_amount(const std::string& str, float max_query_amount);
