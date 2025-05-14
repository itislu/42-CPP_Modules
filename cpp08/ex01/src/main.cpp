// NOLINTBEGIN(readability-magic-numbers)

#include "Span.hpp"
#include "libftpp/algorithm.hpp"
#include "libftpp/format.hpp"
#include "libftpp/string.hpp"
#include "test_utils.hpp"
#include <algorithm>
#include <exception>
#include <iostream>
#include <limits>
#include <vector>

static void test_subject();
static void test_numeric_limits();
static void test_duplicates();
static void test_iterators();
static void test_copy();
static void test_exceptions();
static void test_many();
static void test_performance();

int main(int argc, char* argv[])
try {
	if (argc > 1) {
		const std::vector<const char*> args(argv + 1, argv + argc);
		std::vector<int> nbrs(args.size());
		std::transform(
		    args.begin(), args.end(), nbrs.begin(), ft::FromString<int>());
		Span sp(nbrs.size());
		sp.addNumber(nbrs.begin(), nbrs.end());
		print_spans(sp);
		return 0;
	}

	test_subject();
	test_numeric_limits();
	test_duplicates();
	test_iterators();
	test_copy();
	test_exceptions();
	test_many();
	test_performance();

	return 0;
}
catch (const std::exception& e) {
	std::cerr << ft::log::error(BOLD("Unexpected exception: ") + e.what())
	          << '\n';
	return 1;
}

// NOLINTBEGIN
static void test_subject()
{
	print_seperator("Subject Test Case"), std::cout << '\n';

	Span sp = Span(5);
	sp.addNumber(6);
	sp.addNumber(3);
	sp.addNumber(17);
	sp.addNumber(9);
	sp.addNumber(11);
	std::cout << sp.shortestSpan() << std::endl;
	std::cout << sp.longestSpan() << std::endl;
}
// NOLINTEND

static void test_numeric_limits()
{
	print_seperator("Numeric Limits");

	{
		std::cout << '\n' << BOLD(UNDERLINE("int limits")) << '\n';
		Span sp(2);
		print_addNumber(sp, std::numeric_limits<int>::max());
		print_addNumber(sp, std::numeric_limits<int>::min());
		print_spans(sp);
	}
	{
		std::cout << '\n' << BOLD(UNDERLINE("int limits + a few")) << '\n';
		Span sp(4);
		print_addNumber(sp, 0);
		print_addNumber(sp, -1);
		print_addNumber(sp, std::numeric_limits<int>::min());
		print_addNumber(sp, std::numeric_limits<int>::max());
		print_spans(sp);
	}
	{
		std::cout << '\n' << BOLD(UNDERLINE("Equal distance")) << '\n';
		Span sp(3);
		print_addNumber(sp, -1);
		print_addNumber(sp, std::numeric_limits<int>::max() - 1);
		print_addNumber(sp, std::numeric_limits<int>::min());
		print_spans(sp);
	}
}

static void test_duplicates()
{
	print_seperator("Duplicates");

	{
		std::cout << '\n'
		          << BOLD(UNDERLINE("First no duplicate, then duplicate"))
		          << '\n';
		Span sp(3);
		print_addNumber(sp, 1);
		print_addNumber(sp, 2);
		print_spans(sp);
		print_addNumber(sp, 1);
		print_spans(sp);
	}
	{
		std::cout << '\n'
		          << BOLD(UNDERLINE("First duplicate, then no duplicate"))
		          << '\n';
		Span sp(3);
		print_addNumber(sp, 1);
		print_addNumber(sp, 1);
		print_spans(sp);
		print_addNumber(sp, 2);
		print_spans(sp);
	}
	{
		std::cout << '\n' << BOLD(UNDERLINE("Only duplicates")) << '\n';
		Span sp(5);
		print_addNumber(sp, 1);
		print_addNumber(sp, 1);
		print_addNumber(sp, 1);
		print_addNumber(sp, 1);
		print_addNumber(sp, 1);
		print_spans(sp);
	}
}

static void test_iterators()
{
	print_seperator("Iterators");

	{
		std::cout << '\n' << BOLD(UNDERLINE("Only 2")) << '\n';
		std::vector<int> range(2);
		ft::iota(range.begin(), range.end(), 1);
		Span sp(2);
		print_addNumber(sp, range.begin(), range.end());
		print_spans(sp);
	}
	{
		std::cout << '\n' << BOLD(UNDERLINE("Normal iterator")) << '\n';
		std::vector<int> range(100);
		ft::iota(range.begin(), range.end(), 1);
		Span sp(101);
		print_addNumber(sp, -100);
		print_addNumber(sp, range.begin(), range.begin() + 20);
		print_spans(sp);
		print_addNumber(sp, range.begin() + 20, range.end());
		print_spans(sp);
	}
	{
		std::cout << '\n' << BOLD(UNDERLINE("Reverse iterator")) << '\n';
		std::vector<int> range(100);
		ft::iota(range.begin(), range.end(), 1);
		Span sp(101);
		print_addNumber(sp, -100);
		print_addNumber(sp, range.rbegin(), range.rbegin() + 20);
		print_spans(sp);
		print_addNumber(sp, range.rbegin() + 20, range.rend());
		print_spans(sp);
	}
	{
		std::cout << '\n' << BOLD(UNDERLINE("All zeros")) << '\n';
		std::vector<int> range(10000);
		Span sp(10000);
		print_addNumber(sp, range.begin(), range.end());
		print_spans(sp);
	}
}

static void test_copy()
{
	print_seperator("Copy");

	std::vector<int> range(9);
	ft::iota(range.begin(), range.end(), 1);

	std::cout << '\n' << BOLD("Span1:") << '\n';
	Span sp1(10);
	print_addNumber(sp1, range.begin(), range.end());
	print_spans(sp1);

	std::cout << '\n' << BOLD("Span2:") << '\n';
	Span sp2(sp1);
	std::cerr << GRAY("copied Span1") << '\n';
	print_addNumber(sp2, 100);
	print_spans(sp2);

	std::cout << '\n' << BOLD("Span2:") << '\n';
	sp2 = sp1;
	std::cerr << GRAY("assigned Span1 to Span2") << '\n';
	print_spans(sp2);
}

static void test_exceptions()
{
	print_seperator("Exceptions");

	{
		std::cout << '\n' << BOLD(UNDERLINE("Empty")) << '\n';
		const Span sp(0);
		print_spans(sp);
	}
	{
		std::cout << '\n' << BOLD(UNDERLINE("Only 1")) << '\n';
		Span sp(1);
		print_addNumber(sp, 42);
		print_spans(sp);
	}
	{
		std::cout << '\n' << BOLD(UNDERLINE("Keep trying")) << '\n';
		Span sp(10);
		print_spans(sp);
		print_addNumber(sp, 21);
		print_spans(sp);
		print_addNumber(sp, -21);
		print_spans(sp);
		print_addNumber(sp, 42);
		print_spans(sp);
	}
	{
		std::cout << '\n' << BOLD(UNDERLINE("Full")) << '\n';
		Span sp(2);
		print_addNumber(sp, -100);
		print_addNumber(sp, -200);
		print_spans(sp);
		print_addNumber(sp, -300);
		print_spans(sp);
		print_addNumber(sp, -300);
		print_spans(sp);
		print_addNumber(sp, -400);
		print_spans(sp);
	}
	{
		std::cout << '\n' << BOLD(UNDERLINE("Full from iterator")) << '\n';
		std::vector<int> range(100);
		ft::iota(range.begin(), range.end(), 1);
		Span sp(99);
		print_addNumber(sp, range.begin(), range.end());
		print_spans(sp);
	}
	{
		std::cout << '\n'
		          << BOLD(UNDERLINE("Iterator to already full")) << '\n';
		std::vector<int> range(100);
		ft::iota(range.begin(), range.end(), 1);
		Span sp(50);
		print_addNumber(sp, range.begin(), range.begin() + 20);
		print_addNumber(sp, range.begin() + 20, range.end());
		print_spans(sp);
	}
}

static void test_many()
{
	print_seperator("Many");

	add_many_intervaled(10000, 8);
	add_many_intervaled(100000, 8);
}

static void test_performance()
{
	print_seperator("Performance");

	add_many_timed(16);
	add_many_timed(32);
	add_many_timed(50);
	add_many_timed(100);
	add_many_timed(1000);
	add_many_timed(10000);
	add_many_timed(100000);
	add_many_timed(1000000);
	add_many_timed(2000000);
}

// NOLINTEND(readability-magic-numbers)
