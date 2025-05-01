#include "MutantStack.hpp"
#include "libftpp/algorithm.hpp"
#include "libftpp/format.hpp"
#include <deque>
#include <exception>
#include <iostream>
#include <list>
#include <sstream>
#include <stack>
#include <string>
#include <vector>

static void test_subject();
static void test_subject_mstack();
static void test_subject_list();
static void test_copy();
static void test_reverse_iterator();
static void test_containers();
template <typename Mstack>
static void print_mstack(const Mstack& mstack);
static void print_seperator(const std::string& title);

int main()
try {
	test_subject();
	test_copy();
	test_reverse_iterator();
	test_containers();
}
catch (const std::exception& e) {
	std::cerr << ft::log::error(BOLD("Unexpected exception: ") + e.what())
	          << '\n';
	return 1;
}

static void test_subject()
{
	print_seperator("Subject Test Case");

	std::streambuf* const og_cout = std::cout.rdbuf();
	const std::stringstream mstack_output;
	const std::stringstream list_output;
	try {
		std::cout.rdbuf(mstack_output.rdbuf());
		test_subject_mstack();
		std::cout.rdbuf(list_output.rdbuf());
		test_subject_list();
	}
	catch (...) {
		std::cout.rdbuf(og_cout);
		throw;
	}
	std::cout.rdbuf(og_cout);

	std::cout << BOLD(UNDERLINE("MutantStack")) << '\n';
	std::cout << mstack_output.str();
	std::cout << '\n' << BOLD(UNDERLINE("std::list")) << '\n';
	std::cout << list_output.str();

	if (mstack_output.str() == list_output.str()) {
		std::cout << '\n' << ft::log::ok("Outputs are the same.") << '\n';
	}
	else {
		std::cout << '\n' << ft::log::error("Outputs differ!") << '\n';
	}
}

// NOLINTBEGIN
static void test_subject_mstack()
{
	MutantStack<int> mstack;
	mstack.push(5);
	mstack.push(17);
	std::cout << mstack.top() << std::endl;
	mstack.pop();
	std::cout << mstack.size() << std::endl;
	mstack.push(3);
	mstack.push(5);
	mstack.push(737);
	//[...]
	mstack.push(0);
	MutantStack<int>::iterator it = mstack.begin();
	MutantStack<int>::iterator ite = mstack.end();
	++it;
	--it;
	while (it != ite) {
		std::cout << *it << std::endl;
		++it;
	}
	std::stack<int> s(mstack);
}
// NOLINTEND

// NOLINTBEGIN
static void test_subject_list()
{
	std::list<int> list;
	list.push_back(5);
	list.push_back(17);
	std::cout << list.back() << std::endl;
	list.pop_back();
	std::cout << list.size() << std::endl;
	list.push_back(3);
	list.push_back(5);
	list.push_back(737);
	//[...]
	list.push_back(0);
	std::list<int>::iterator it = list.begin();
	std::list<int>::iterator ite = list.end();
	++it;
	--it;
	while (it != ite) {
		std::cout << *it << std::endl;
		++it;
	}
	std::list<int> l(list);
}
// NOLINTEND

static void test_copy()
{
	print_seperator("Copy and Assignment");

	MutantStack<int> a;
	std::cout << GRAY("a default constructed") << '\n';
	a.push(1);
	a.push(2);
	a.push(3);
	std::cout << GRAY("a pushed 1, 2 and 3") << '\n';
	std::cout << BOLD("a: "), print_mstack(a), std::cout << '\n';

	MutantStack<int> b(a);
	std::cout << GRAY("b copy constructed from a") << '\n';
	std::cout << BOLD("b: "), print_mstack(b), std::cout << '\n';

	b.pop();
	std::cout << GRAY("b popped") << '\n';
	std::cout << BOLD("b: "), print_mstack(b);
	std::cout << BOLD("a: "), print_mstack(a), std::cout << '\n';

	a = b;
	std::cout << GRAY("a assigned with b") << '\n';
	std::cout << BOLD("a: "), print_mstack(a), std::cout << '\n';

	a.pop();
	std::cout << GRAY("a popped") << '\n';
	std::cout << BOLD("a: "), print_mstack(a);
	std::cout << BOLD("b: "), print_mstack(b);
}

static void test_reverse_iterator()
{
	print_seperator("Reverse Iterator");

	MutantStack<int> mstack;
	mstack.push(0);
	mstack.push(0);
	mstack.push(0);
	mstack.push(0);
	mstack.push(0);

	ft::iota(mstack.begin(), mstack.end(), 1);
	print_mstack(mstack);

	ft::iota(mstack.rbegin(), mstack.rend(), 1);
	print_mstack(mstack);
}

static void test_containers()
{
	print_seperator("Underlying Containers");
	{
		std::cout << BOLD(UNDERLINE("std::deque")) << '\n';
		std::deque<int> deque(128);
		ft::iota(deque.begin(), deque.end(), 1);
		std::cout << GRAY("Created std::deque with 128 numbers") << '\n';

		MutantStack<int> mstack(deque);
		std::cout << GRAY("Copy constructed MutantStack from std::deque")
		          << '\n';
		print_mstack(mstack);
		std::cout << "empty: " << std::boolalpha << mstack.empty() << '\n';
		std::cout << "size : " << mstack.size() << '\n';
		std::cout << "top  : " << mstack.top() << '\n';
		mstack.push(0);
		std::cout << GRAY("Pushed 0") << '\n';
		mstack.pop();
		std::cout << GRAY("Popped") << '\n';
	}
	std::cout << '\n';
	{
		std::cout << BOLD(UNDERLINE("std::list")) << '\n';
		std::list<int> list(128);
		ft::iota(list.begin(), list.end(), 1);
		std::cout << GRAY("Created std::list with 128 numbers") << '\n';

		MutantStack<int, std::list<int> > mstack(list);
		std::cout << GRAY("Copy constructed MutantStack from std::list")
		          << '\n';
		mstack.push(0);
		std::cout << GRAY("Pushed 0") << '\n';
		print_mstack(mstack);
		std::cout << "empty: " << std::boolalpha << mstack.empty() << '\n';
		std::cout << "size : " << mstack.size() << '\n';
		std::cout << "top  : " << mstack.top() << '\n';
		mstack.pop();
		std::cout << GRAY("Popped") << '\n';
	}
	std::cout << '\n';
	{
		std::cout << BOLD(UNDERLINE("std::vector")) << '\n';
		std::vector<int> vector(128);
		ft::iota(vector.begin(), vector.end(), 1);
		std::cout << GRAY("Created std::vector with 128 numbers") << '\n';

		MutantStack<int, std::vector<int> > mstack(vector);
		std::cout << GRAY("Copy constructed MutantStack from std::vector")
		          << '\n';
		mstack.push(0);
		std::cout << GRAY("Pushed 0") << '\n';
		print_mstack(mstack);
		mstack.pop();
		std::cout << GRAY("Popped") << '\n';
		std::cout << "empty: " << std::boolalpha << mstack.empty() << '\n';
		std::cout << "size : " << mstack.size() << '\n';
		std::cout << "top  : " << mstack.top() << '\n';
	}
	std::cout << '\n';
	{
		std::cout << BOLD(UNDERLINE("std::string")) << '\n';
		std::string string(26, '\0'); // NOLINT(readability-magic-numbers)
		ft::iota(string.begin(), string.end(), 'A');
		std::cout << GRAY("Created std::string with 26 characters") << '\n';
		std::cout << string << '\n';

		MutantStack<char, std::string> mstack(string);
		std::cout << GRAY("Copy constructed MutantStack from std::string")
		          << '\n';
		mstack.push('0');
		std::cout << GRAY("Pushed '0'") << '\n';
		print_mstack(mstack);
		std::cout << "empty: " << std::boolalpha << mstack.empty() << '\n';
		std::cout << "size : " << mstack.size() << '\n';
#if __cplusplus >= 201103L // C++11 or later
		std::cout << "top  : " << mstack.top() << '\n';
		mstack.pop();
		std::cout << GRAY("Popped") << '\n';
#else
		std::cout
		    << "top  : "
		    << "not available with std::string in C++98 because of LWG 534 "
		       "(https://cplusplus.github.io/LWG/issue534)"
		    << '\n';
#endif
	}
}

template <typename Mstack>
static void print_mstack(const Mstack& mstack)
{
	for (typename Mstack::const_iterator cur = mstack.begin(),
	                                     end = mstack.end();
	     cur != end;
	     ++cur) {
		if (cur != mstack.begin()) {
			std::cout << ", ";
		}
		std::cout << *cur;
	}
	std::cout << '\n';
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
