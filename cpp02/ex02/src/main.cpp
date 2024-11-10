// NOLINTBEGIN

#include "Fixed.hpp"
#include <iomanip>
#include <iostream>

int main(void)
{
	Fixed a;
	Fixed const b(Fixed(5.05f) * Fixed(2));

	std::cout << a << std::endl;
	std::cout << ++a << std::endl;
	std::cout << a << std::endl;
	std::cout << a++ << std::endl;
	std::cout << a << std::endl;

	std::cout << b << std::endl;

	std::cout << Fixed::max(a, b) << std::endl;

	Fixed c(8388607.6f);
	Fixed d(-8388607.6f);
	Fixed e(c + d);

	std::cout << std::setprecision(38);
	std::cout << "e: " << e << std::endl;
	std::cout << "c + 1 == c: " << (c + 1 == c) << std::endl;
	std::cout << "--a: " << --a << std::endl;
	std::cout << "a > 0: " << (a > 0) << std::endl;
	std::cout << "a < 0: " << (a < 0) << std::endl;
	std::cout << "a >= 0: " << (a >= 0) << std::endl;
	std::cout << "a <= 0: " << (a <= 0) << std::endl;
	std::cout << "a == 0: " << (a == 0) << std::endl;
	std::cout << "a != 0: " << (a != 0) << std::endl;
	std::cout << "a + b: " << a + b << std::endl;
	std::cout << "a - b: " << a - b << std::endl;
	std::cout << "a * b: " << a * b << std::endl;
	std::cout << "d / 10: " << d / 10 << std::endl;
	std::cout << "a++: " << a++ << std::endl;
	std::cout << "a--: " << a-- << std::endl;
	std::cout << "--a: " << --a << std::endl;
	std::cout << "++a: " << ++a << std::endl;
	std::cout << "(a = a - a * 2): " << (a = a - a * 2) << std::endl;
	std::cout << "min(a, 0): " << Fixed::min(a, 0) << std::endl;
	std::cout << "max(a, a): " << Fixed::max(a, a) << std::endl;

	return 0;
}

// NOLINTEND
