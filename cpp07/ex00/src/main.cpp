#include "Fast.hpp"
#include "IntWithId.hpp"
#include "Slow.hpp"
#include "libftpp/format.hpp"
#include "libftpp/string.hpp"
#include "whatever.hpp"
#include <climits>
#include <ctime>
#include <iostream>
#include <string>

static void test_subject();
static void test_min_max();
static void benchmark_swap();
template <typename T>
static void swap_test(T& a, T& b);
static void print_seperator(const std::string& title);

int main()
{
	test_subject();
	test_min_max();
	benchmark_swap();
}

static void test_subject()
{
	print_seperator("Subject Test Cases");

	int a = 2;
	int b = 3;

	::swap(a, b);
	std::cout << "a = " << a << ", b = " << b << '\n';
	std::cout << "min( a, b ) = " << ::min(a, b) << '\n';
	std::cout << "max( a, b ) = " << ::max(a, b) << '\n';

	std::string c = "chaine1";
	std::string d = "chaine2";

	::swap(c, d);
	std::cout << "c = " << c << ", d = " << d << '\n';
	std::cout << "min( c, d ) = " << ::min(c, d) << '\n';
	std::cout << "max( c, d ) = " << ::max(c, d) << '\n';
}

static void test_min_max()
{
	print_seperator("Min/Max Test");

	std::cout << BOLD("IntWithId") << '\n';
	IntWithId a(42);
	IntWithId b(42);
	std::cout << BOLD("a: ") << a << '\n';
	std::cout << BOLD("b: ") << b << '\n';
	std::cout << BOLD("min(a, b): ") << min(a, b) << '\n';
	std::cout << BOLD("max(a, b): ") << max(a, b) << '\n';
	std::cout << BOLD("min(a, b) = 0: ") << (min(a, b) = 0) << '\n';
	std::cout << BOLD("max(a, b): ") << (max(a, b)) << '\n';

	std::cout << '\n' << BOLD("Integer Literal") << '\n';
	std::cout << BOLD("min(1, 2): ") << min(1, 2) << '\n';
	std::cout << BOLD("max(1, 2): ") << max(1, 2) << '\n';

	std::cout << '\n' << BOLD("Const Volatile Integer") << '\n';
	const volatile int x = INT_MAX;
	const volatile int y = INT_MIN;
	std::cout << BOLD("min(x, y): ") << min(x, y) << '\n';
	std::cout << BOLD("max(x, y): ") << max(x, y) << '\n';
}

static void benchmark_swap()
{
	print_seperator("Swap Benchmark");

	Slow::string_init_size = 1024LU * 1024 * 1024; // 1 GiB
	std::cout << BOLD("Constructing strings with "
	                  + ft::to_string(Slow::string_init_size)
	                  + " characters...")
	          << '\n';
	Fast fast1;
	Fast fast2;
	Slow& slow1 = fast1;
	Slow& slow2 = fast2;
	std::cerr << ft::log::ok(BOLD("Done!")) << '\n';
	std::cout << '\n';

	std::cout << BOLD("Using Forwarding Swap:") << '\n';
	swap_test(fast1, fast2);

	std::cout << BOLD("Using Standard Swap:") << '\n';
	swap_test(slow1, slow2);
}

template <typename T>
static void swap_test(T& a, T& b)
{
	std::cout << "Press Enter to start the benchmark... ";
	std::string dummy;
	std::getline(std::cin, dummy);
	std::cout << "\033[A\033[2K\r", std::cout.flush(); // Clear previous line

	const clock_t start = clock();
	for (unsigned int i = 0; i < 10; ++i) {
		std::cerr << ft::log::info(BOLD("swap #" + ft::to_string(i + 1) + ":"))
		          << '\n';
		swap(a, b);
	}
	const clock_t end = clock();

	std::cerr << ft::log::ok(BOLD("Done!")) << "\n";
	const double duration = static_cast<double>(end - start) / CLOCKS_PER_SEC;
	std::cout << BOLD("Execution time: ") << std::fixed << duration
	          << " seconds\n\n";
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
	          << "\n\n";
}
