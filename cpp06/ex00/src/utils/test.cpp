#include "string.hpp"
#include "string.tpp"
#include <cctype>
#include <cmath>
#include <iostream>
#include <iterator>
#include <string>

class A {
public:
	A()
	    : i(42)
	{}

	int i;
};

std::ostream& operator<<(std::ostream& os, A a)
{
	os << a.i;
	return os;
}

std::istream& operator>>(std::istream& is, A& a)
{
	is >> a.i;
	return is;
}

int main()
{
	// float f = NAN;
	// std::cout << std::isnan(-f) << '\n';

	// std::cout << std::stof("1111111111111111111111111111111111111111") <<
	// '\n';

	// A a = utils::string::from_string<A>("   123asdf1");

	std::cout << "|" << utils::string::from_string<char>("48") << "|" << '\n';

	// utils::string::_detail::from_string_floating_point<float>("");
	std::cout << utils::string::to_string(A()) << '\n';

	std::cout << utils::string::from_string<A>("   123asdf1") << '\n';
	std::cout << utils::string::from_string<double>("   123asdf1") << '\n';
	std::cout << utils::string::from_string<long double>("   123asdf1") << '\n';
	std::cout << utils::string::from_string<int>("   123asdf1") << '\n';
	std::cout << utils::string::from_string<bool>("   2") << '\n';

	// std::cout << utils::string::transform("hello world", toupper) << '\n';

	std::string in("hello world");
	std::string out;
	// out.resize(in.length());
	utils::string::transform(
	    in.begin(), in.end(), std::inserter(out, out.begin()), toupper);
	std::cout << out << '\n';
}
