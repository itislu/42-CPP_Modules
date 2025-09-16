#pragma once

#include <cstddef>
#include <string>
#include <vector>

enum Error {
	UNEXPECTED = -1,
	OK = 0,
	NO_ARGS = 1,
	PARSE_ERROR = 2
};

struct Options {
	bool more_types;
	bool no_before_after;
};

/* Parsing */

template <typename T>
std::vector<T> parse_args(int argc, char* argv[], Options* options_out = NULL);

/* Printing */

template <typename C>
void print_container(const C& container, const std::string& prefix);
void print_seperator(const std::string& title);

/* Locale */

/**
 * Use the user-preferred locale for better formatting of large numbers.
 * On failure, keep the standard locale.
 */
void init_user_locale();
/**
 * Avoids "still reachable" valgrind warnings for sake of the subject...
 */
void reset_locale();

#include "parse.tpp" // IWYU pragma: export
#include "print.tpp" // IWYU pragma: export
