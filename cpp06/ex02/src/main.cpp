// NOLINTBEGIN(cppcoreguidelines-avoid-goto)

#include "A.hpp"
#include "B.hpp"
#include "Base.hpp"
#include "C.hpp"
#include "libftpp/common.hpp"
#include "libftpp/log.hpp"
#include <cstddef>
#include <exception>
#include <iostream>
#include <string>

static Base* generate();
static void identifiy(Base* p);
static void identifiy(Base& p);

int main()
try {
	Base* p = generate();

	identifiy(p);
	identifiy(*p);

	std::cerr << '\n' << ft::log::info("NULL pointer") << '\n';
	identifiy(NULL);

	std::cerr << '\n' << ft::log::info("Base object") << '\n';
	Base b;
	identifiy(&b);
	identifiy(b);

	delete p;
}
catch (const std::exception& e) {
	std::cerr << ft::log::error(BOLD("Exception: ") + e.what()) << '\n';
	return 1;
}

static Base* generate()
{
	switch (ft::urandom<unsigned int>() % 3) {
	case 0:
		std::cerr << ft::log::info("Generated A") << '\n';
		return new A();
	case 1:
		std::cerr << ft::log::info("Generated B") << '\n';
		return new B();
	case 2:
		std::cerr << ft::log::info("Generated C") << '\n';
		return new C();
	default:
		UNREACHABLE();
	}
}

static void identifiy(Base* p)
{
	std::string log;
	std::string type;

	if (dynamic_cast<A*>(p) != NULL) {
		log = ft::log::ok("");
		type = "A";
	}
	else if (dynamic_cast<B*>(p) != NULL) {
		log = ft::log::ok("");
		type = "B";
	}
	else if (dynamic_cast<C*>(p) != NULL) {
		log = ft::log::ok("");
		type = "C";
	}
	else {
		log = ft::log::error("");
		type = "Unknown";
	}

	std::cerr << log << "Pointer type: ";
	std::cout << type << '\n';
}

static void identifiy(Base& p)
{
	std::string log;
	std::string type;

	try {
		(void)dynamic_cast<A&>(p);
		log = ft::log::ok("");
		type = "A";
		goto finish;
	}
	catch (...) { // NOLINT(bugprone-empty-catch)
	}
	try {
		(void)dynamic_cast<B&>(p);
		log = ft::log::ok("");
		type = "B";
		goto finish;
	}
	catch (...) { // NOLINT(bugprone-empty-catch)
	}
	try {
		(void)dynamic_cast<C&>(p);
		log = ft::log::ok("");
		type = "C";
		goto finish;
	}
	catch (...) { // NOLINT(bugprone-empty-catch)
	}
	log = ft::log::error("");
	type = "Unknown";

finish:
	std::cerr << log << "Reference type: ";
	std::cout << type << '\n';
}

// NOLINTEND(cppcoreguidelines-avoid-goto)
