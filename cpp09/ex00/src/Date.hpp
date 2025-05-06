#pragma once

#include <ctime>
#include <string>

class Date {
public:
	static const char* const default_format;

	/**
	 * @brief Converts a formatted string to seconds since the Unix epoch
	 *
	 * @throws std::invalid_argument When `str` does not match the format
	 * @throws std::out_of_range When impossible date
	 */
	static std::time_t serialize(const std::string& str,
	                             std::string::size_type* endpos_out = NULL,
	                             const char* format = default_format);
	/**
	 * @brief Converts seconds since the Unix epoch to a formatted string
	 *
	 * @throws std::out_of_range When value too large or string would exceed
	 * buffer size
	 */
	static std::string str(std::time_t time,
	                       const char* format = default_format);

private:
	Date();
	Date(const Date& other);
	Date& operator=(const Date& other);
	~Date();
};
