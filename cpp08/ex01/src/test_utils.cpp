#include "test_utils.hpp"
#include "Span.hpp"
#include "libftpp/format.hpp"
#include "libftpp/random.hpp"
#include "libftpp/string.hpp"
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <limits>
#include <stdexcept>
#include <string>
#include <vector>

static std::string format_with_thousands_sep(unsigned int value);
static bool running_on_valgrind();

static const unsigned int valgrind_max = 100000;

void add_many_intervaled(unsigned int amount, unsigned int intervals)
{
	std::cout << '\n'
	          << BOLD(UNDERLINE(format_with_thousands_sep(amount))) << '\n';
	if (amount > valgrind_max && running_on_valgrind()) {
		std::cout << ft::log::info(
		    GRAY("Skipping larger tests when running under Valgrind"))
		          << "\n";
		return;
	}

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

void add_many_timed(unsigned int amount)
{
	std::cout << '\n'
	          << BOLD(UNDERLINE(format_with_thousands_sep(amount) + " (timed)"))
	          << '\n';
	if (amount > valgrind_max && running_on_valgrind()) {
		std::cout << ft::log::info(
		    GRAY("Skipping larger tests when running under Valgrind"))
		          << "\n";
		return;
	}

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

void print_addNumber(Span& sp, int nbr)
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

void print_spans(const Span& sp)
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

void print_seperator(const std::string& title)
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

static bool running_on_valgrind()
{
	return std::getenv("RUNNING_ON_VALGRIND") != NULL;
}
