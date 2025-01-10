// NOLINTBEGIN

#include "Fixed.hpp"
#include <climits>
#include <cmath>
#include <iomanip>
#include <iostream>

int main(void)
{
	// Undefined behavior:
	// std::cout << (int)(2147483648.f) << '\n';
	// std::cout << (int)(long)argv << '\n';

	Fixed a;
	Fixed const b(10);
	Fixed const c(42.42f);
	Fixed const d(b);
	Fixed const nan(NAN);
	Fixed const inf(INFINITY);
	Fixed const nan_copy(nan);
	Fixed clamped_float = Fixed(8388607.6f);
	Fixed zero = Fixed(0);
	Fixed negative = Fixed(-10);
	Fixed max_int = Fixed(INT_MAX);
	Fixed min_int = Fixed(INT_MIN);

	a = Fixed(1234.4321f);

	std::cout << "a is " << a << std::endl;
	std::cout << "b is " << b << std::endl;
	std::cout << "c is " << c << std::endl;
	std::cout << "d is " << d << std::endl;
	std::cout << std::setprecision(38);
	std::cout << "nan is " << nan << std::endl;
	std::cout << "inf is " << inf << std::endl;
	std::cout << "nan_copy is " << nan_copy << std::endl;
	std::cout << "clamped_float is " << clamped_float << std::endl;
	std::cout << "zero is " << zero << std::endl;
	std::cout << "negative is " << negative << std::endl;
	std::cout << "max_int is " << max_int << std::endl;
	std::cout << "min_int is " << min_int << std::endl;

	std::cout << "a is " << a.toInt() << " as integer" << std::endl;
	std::cout << "b is " << b.toInt() << " as integer" << std::endl;
	std::cout << "c is " << c.toInt() << " as integer" << std::endl;
	std::cout << "d is " << d.toInt() << " as integer" << std::endl;
	std::cout << "nan is " << nan.toInt() << " as integer" << std::endl;
	std::cout << "inf is " << inf.toInt() << " as integer" << std::endl;
	std::cout << "nan_copy is " << nan_copy.toInt() << " as integer" << std::endl;
	std::cout << "clamped_float is " << clamped_float.toInt() << " as integer" << std::endl;
	std::cout << "zero is " << zero.toInt() << " as integer" << std::endl;
	std::cout << "negative is " << negative.toInt() << " as integer" << std::endl;
	std::cout << "max_int is " << max_int.toInt() << " as integer" << std::endl;
	std::cout << "min_int is " << min_int.toInt() << " as integer" << std::endl;

	return 0;
}

// NOLINTEND
