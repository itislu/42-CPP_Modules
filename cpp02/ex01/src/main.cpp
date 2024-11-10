// NOLINTBEGIN

#include "Fixed.hpp"
#include <cmath>
#include <iomanip>
#include <iostream>

int main(void)
{
	Fixed a;
	Fixed const b(10);
	Fixed const c(42.42f);
	Fixed const d(b);
	Fixed const nan(NAN);
	Fixed const inf(INFINITY);
	Fixed const nan_copy(nan);
	Fixed max = Fixed(8388607.6f);

	a = Fixed(1234.4321f);

	std::cout << "a is " << a << std::endl;
	std::cout << "b is " << b << std::endl;
	std::cout << "c is " << c << std::endl;
	std::cout << "d is " << d << std::endl;
	std::cout << std::setprecision(38);
	std::cout << "nan is " << nan << std::endl;
	std::cout << "inf is " << inf << std::endl;
	std::cout << "nan_copy is " << nan_copy << std::endl;
	std::cout << "max is " << max << std::endl;

	std::cout << "a is " << a.toInt() << " as integer" << std::endl;
	std::cout << "b is " << b.toInt() << " as integer" << std::endl;
	std::cout << "c is " << c.toInt() << " as integer" << std::endl;
	std::cout << "d is " << d.toInt() << " as integer" << std::endl;
	std::cout << "nan is " << nan.toInt() << " as integer" << std::endl;
	std::cout << "inf is " << inf.toInt() << " as integer" << std::endl;
	std::cout << "nan_copy is " << nan_copy.toInt() << " as integer" << std::endl;
	std::cout << "max is " << max.toInt() << " as integer" << std::endl;

	return 0;
}

// NOLINTEND
