#pragma once

#include "libftpp/format.hpp"
#include "libftpp/string.hpp"
#include "utils.hpp"
#include <algorithm>
#include <cstddef>
#include <iostream>
#include <string>
#include <vector>

namespace detail_parse {
static inline int parse_options(int argc, char* argv[], Options* options_out);
static inline void check_excess(const std::string& arg,
                                std::string::size_type endpos);
} // namespace detail_parse

// NOLINTBEGIN(cppcoreguidelines-pro-bounds-pointer-arithmetic): argv
template <typename T>
std::vector<T>
parse_args(int argc, char* argv[], Options* options_out /*= NULL*/)
{
	const int start_idx = detail_parse::parse_options(argc, argv, options_out);
	if (start_idx == argc) {
		std::cerr
		    << "Usage: " << argv[0]
		    << " [-m|--more-types] [-n|--no-before-after] <positive_number> [...]\n";
		throw NO_ARGS; // NOLINT: Exit code.
	}

	std::vector<T> input;
	input.reserve(argc - start_idx);
	std::string arg;
	std::string::size_type endpos = 0;
	try {
		for (int i = start_idx; i < argc; ++i) {
			arg = argv[i];
			input.push_back(ft::from_string<T>(arg, std::ios::dec, &endpos));
			detail_parse::check_excess(arg, endpos);
		}
	}
	catch (const ft::FromStringException& e) {
		// Give excess priority before range error.
		if (dynamic_cast<const ft::FromStringRangeException*>(&e) != NULL) {
			detail_parse::check_excess(arg, endpos);
		}
		std::cerr << ft::log::error(e.error()) << '\n';
		throw PARSE_ERROR; // NOLINT: Exit code.
	}
	return input;
}
// NOLINTEND(cppcoreguidelines-pro-bounds-pointer-arithmetic): argv

namespace detail_parse {

// NOLINTBEGIN(cppcoreguidelines-pro-bounds-pointer-arithmetic): argv
static inline int parse_options(int argc, char* argv[], Options* options_out)
{
	// Ensure valid references.
	Options _ = {};
	Options& options = (options_out ? *options_out : _) = _;

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
				options.more_types = true;
			}
			if (arg.find('n') != std::string::npos) {
				options.no_before_after = true;
			}
			continue;
		}

		// Long opts.
		if (arg == "--more-types") {
			options.more_types = true;
		}
		else if (arg == "--no-before-after") {
			options.no_before_after = true;
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
// NOLINTEND(cppcoreguidelines-pro-bounds-pointer-arithmetic): argv

static inline void check_excess(const std::string& arg,
                                std::string::size_type endpos)
{
	if (endpos != arg.length()) {
		std::cerr << ft::log::error("excess characters: \"" + arg + "\"")
		          << '\n';
		throw PARSE_ERROR; // NOLINT: Exit code.
	}
}

} // namespace detail_parse
