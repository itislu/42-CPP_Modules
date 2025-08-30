#include "libftpp/format.hpp"
#include "utils.hpp"
#include <exception>
#include <iostream>
#include <locale>

void init_user_locale()
{
	try {
		std::locale::global(std::locale(""));
	}
	catch (const std::exception& e) {
		std::cerr << ft::log::info("Cannot change locale: ") << e.what()
		          << '\n';
	}
}

void reset_locale() { std::locale::global(std::locale::classic()); }
