#pragma once

#include "libftpp/format.hpp"
#include "libftpp/string.hpp"
#include "utils.hpp"
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

namespace detail_parse {
static inline int parse_options(int argc,
                                char* argv[],
                                bool* more_types_out,
                                bool* no_before_after_out);
} // namespace detail_parse

// NOLINTBEGIN(cppcoreguidelines-pro-bounds-pointer-arithmetic): argv
template <typename T>
std::vector<T> parse_args(int argc,
                          char* argv[],
                          bool* more_types_out /*= NULL*/,
                          bool* no_before_after_out /*= NULL*/)
{
	const int start_idx = detail_parse::parse_options(
	    argc, argv, more_types_out, no_before_after_out);
	if (start_idx == argc) {
		std::cerr
		    << "Usage: " << argv[0]
		    << " [-m|--more-types] [-n|--no-before-after] <positive_number...>\n";
		throw NO_ARGS; // NOLINT: Exit code.
	}

	std::vector<T> input;
	input.reserve(argc - start_idx);
	try {
		std::string arg;
		std::string::size_type endpos = 0;
		for (int i = start_idx; i < argc; ++i) {
			arg = argv[i];
			input.push_back(ft::from_string<T>(arg, &endpos));
			if (endpos != arg.length()) {
				std::cerr << ft::log::error("excess characters: \"" + arg
				                            + "\"")
				          << '\n';
				throw PARSE_ERROR; // NOLINT: Exit code.
			}
		}
	}
	catch (const ft::FromStringException& e) {
		std::cerr << ft::log::error(e.error()) << '\n';
		throw PARSE_ERROR; // NOLINT: Exit code.
	}
	return input;
}
// NOLINTEND(cppcoreguidelines-pro-bounds-pointer-arithmetic)

namespace detail_parse {

// NOLINTBEGIN(cppcoreguidelines-pro-bounds-pointer-arithmetic): argv
static inline int parse_options(int argc,
                                char* argv[],
                                bool* more_types_out,
                                bool* no_before_after_out)
{
	// Ensure valid references.
	bool _ = false;
	bool& more_types = (more_types_out ? *more_types_out : _) = false;
	bool& no_before_after = (no_before_after_out ? *no_before_after_out : _) =
	    false;

	const int max_start_idx = std::min(3, argc);
	int start_idx = 1;
	for (; start_idx < max_start_idx; ++start_idx) {
		const std::string arg(argv[start_idx]);
		if (arg.length() < 2 || arg[0] != '-') {
			break;
		}

		// Short opts.
		if (arg[1] != '-'
		    && arg.find_first_not_of("mn", 1) == std::string::npos) {
			if (arg.find('m') != std::string::npos) {
				more_types = true;
			}
			if (arg.find('n') != std::string::npos) {
				no_before_after = true;
			}
			continue;
		}

		// Long opts.
		if (arg == "--more-types") {
			more_types = true;
		}
		else if (arg == "--no-before-after") {
			no_before_after = true;
		}
		else if (arg == "--") {
			++start_idx;
			break;
		}
		else {
			break;
		}
	}
	return start_idx;
}
// NOLINTEND(cppcoreguidelines-pro-bounds-pointer-arithmetic)

} // namespace detail_parse
