#include "libftpp/format.hpp"
#include "utils.hpp"
#include <exception>
#include <iostream>
#include <locale>

void init_user_locale()
{
	try {
		const std::locale user_locale("");
		std::locale::global(user_locale);
		std::cout.imbue(user_locale);
		std::cerr.imbue(user_locale);
		std::clog.imbue(user_locale);
	}
	catch (const std::exception& e) {
		std::cerr << ft::log::info("Cannot change locale: ") << e.what()
		          << '\n';
	}
}

void reset_locale()
{
	std::locale::global(std::locale::classic());
	std::cout.imbue(std::locale::classic());
	std::cerr.imbue(std::locale::classic());
	std::clog.imbue(std::locale::classic());
}
