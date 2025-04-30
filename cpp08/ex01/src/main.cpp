// NOLINTBEGIN(readability-magic-numbers)

#include "Span.hpp"
#include "libftpp/algorithm.hpp"
#include "libftpp/format.hpp"
#include "libftpp/functional.hpp"
#include "libftpp/random.hpp"
#include "libftpp/string.hpp"
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <exception>
#include <iomanip>
#include <iostream>
#include <limits>
#include <stdexcept>
#include <string>
#include <vector>

// Tests
static void test_subject();
static void test_numeric_limits();
static void test_duplicates();
static void test_iterators();
static void test_copy();
static void test_exceptions();
static void test_many();
static void test_performance();

// Utils
static void add_many_intervaled(unsigned int amount, unsigned int intervals);
static void add_many_timed(unsigned int amount);
static void print_addNumber(Span& sp, int nbr);
template <typename InputIt>
static void
print_addNumber(Span& sp, const InputIt& first, const InputIt& last);
static void print_spans(const Span& sp);
static void print_seperator(const std::string& title);
static std::string format_with_thousands_sep(unsigned int value);

int main(int argc, char* argv[])
try {
	if (argc > 1) {
		const std::vector<const char*> args(argv + 1, argv + argc);
		std::vector<int> nbrs(args.size());
		std::transform(args.begin(),
		               args.end(),
		               nbrs.begin(),
		               ft::functional::FromString<int>());
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

static void add_many_intervaled(unsigned int amount, unsigned int intervals)
{
	std::cout << '\n'
	          << BOLD(UNDERLINE(format_with_thousands_sep(amount))) << '\n';

	std::vector<int> range(amount);
	std::srand(ft::urandom<unsigned int>());
	std::generate(range.begin(), range.end(), std::rand);

	Span sp(amount);
	const unsigned int interval_size = amount / intervals;
	std::vector<int>::iterator cur = range.begin();

	for (unsigned int i = 1; i <= intervals; ++i) {
		const std::vector<int>::iterator next =
		    (i == intervals) ? range.end() : cur + interval_size;
		print_addNumber(sp, cur, next);
		print_spans(sp);
		cur = next;
	}
}

static void add_many_timed(unsigned int amount)
{
	std::cout << '\n'
	          << BOLD(UNDERLINE(format_with_thousands_sep(amount) + " (timed)"))
	          << '\n';

	std::vector<int> range(amount);
	std::srand(ft::urandom<unsigned int>());
	std::generate(range.begin(), range.end(), std::rand);

	double batch_duration = 0;
	double onebyone_duration = 0;
	{
		std::cout << BOLD("Batch insertion     : "), std::cout.flush();
		Span sp(amount);

		const clock_t start = clock();
		sp.addNumber(range.begin(), range.end());
		const clock_t end = clock();

		batch_duration = static_cast<double>(end - start) / CLOCKS_PER_SEC;
		std::cout << std::fixed << batch_duration << " seconds\n";
		print_spans(sp);
	}
	{
		std::cout << BOLD("One by one insertion: "), std::cout.flush();
		Span sp(amount);

		const clock_t start = clock();
		for (std::vector<int>::iterator first = range.begin(),
		                                last = range.end();
		     first != last;
		     ++first) {
			sp.addNumber(*first);
		}
		const clock_t end = clock();

		onebyone_duration = static_cast<double>(end - start) / CLOCKS_PER_SEC;
		std::cout << std::fixed << onebyone_duration << " seconds\n";
		print_spans(sp);
	}

	const std::streamsize default_precision = std::cout.precision();
	if (batch_duration < onebyone_duration) {
		const double percent_faster =
		    ((onebyone_duration - batch_duration) / batch_duration) * 100.0;
		std::cout << BOLD("Batch insertion") << " is faster by " << std::fixed
		          << std::setprecision(1) << percent_faster << "%\n";
	}
	else if (onebyone_duration < batch_duration) {
		const double percent_faster =
		    ((batch_duration - onebyone_duration) / onebyone_duration) * 100.0;
		std::cout << BOLD("One by one insertion") << " is faster by "
		          << std::fixed << std::setprecision(1) << percent_faster
		          << "%\n";
	}
	else {
		std::cout << "Both methods took exactly the same time\n";
	}
	std::cout.precision(default_precision);
}

static void print_addNumber(Span& sp, int nbr)
{
	const std::string nbr_str = ft::to_string(nbr);
	const std::string max_str = ft::to_string(std::numeric_limits<int>::min());
	std::cerr << GRAY(
	    nbr_str + " "
	    + std::string(3 + max_str.length() - nbr_str.length(), '.') + " ");

	try {
		sp.addNumber(nbr);
		std::cerr << GRAY("added") << '\n';
	}
	catch (const std::runtime_error& e) {
		std::cerr << GRAY("failed") << '\n';
		std::cerr << ft::log::error(e.what()) << '\n';
	}
}

template <typename InputIt>
static void print_addNumber(Span& sp, const InputIt& first, const InputIt& last)
{
	const std::string amount_str =
	    ft::to_string(std::labs(std::distance(first, last)));
	const std::string max_str = ft::to_string(std::numeric_limits<int>::min());
	std::cerr << GRAY(
	    amount_str + " numbers "
	    + std::string(3 + max_str.length() - amount_str.length(), '.') + " ");

	try {
		sp.addNumber(first, last);
		std::cerr << GRAY("added") << '\n';
	}
	catch (const std::runtime_error& e) {
		std::cerr << GRAY("failed") << '\n';
		std::cerr << ft::log::error(e.what()) << '\n';
	}
}

static void print_spans(const Span& sp)
{
	try {
		std::cout << "shortest span: " << BOLD(ft::to_string(sp.shortestSpan()))
		          << '\n';
		std::cout << "longest span : " << BOLD(ft::to_string(sp.longestSpan()))
		          << '\n';
	}
	catch (const std::runtime_error& e) {
		std::cout << '\n';
		std::cerr << ft::log::error(e.what()) << '\n';
	}
}

static void print_seperator(const std::string& title)
{
	const unsigned int width = 60;
	const unsigned int padding = 2;

	const unsigned int available = width - title.length() - padding;
	const unsigned int left = available / 2;
	const unsigned int right = available - left;

	std::cout << "\n\n"
	          << BOLD(std::string(left, '=') + ' ' + title + ' '
	                  + std::string(right, '='))
	          << "\n";
}

static std::string format_with_thousands_sep(unsigned int value)
{
	std::string result = ft::to_string(value);
	for (int pos = static_cast<int>(result.length()) - 3; pos > 0; pos -= 3) {
		result.insert(pos, ",");
	}
	return result;
}

// NOLINTEND(readability-magic-numbers)
