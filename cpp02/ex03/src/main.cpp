// NOLINTBEGIN

#include "Fixed.hpp"
#include "Point.hpp"
#include <iostream>

bool bsp(Point const a, Point const b, Point const c, Point const point);

int main(void)
{
	{
		Point a(0, 4);
		Point b(5, 0);
		Point c(0, 0);
		Point point(0.002, 1);

		std::cout << "Point " << point << " is "
				  << (bsp(a, b, c, point) ? "INSIDE" : "OUTSIDE")
				  << " the triangle." << '\n';
	}
	{
		Point a(0, 1);
		Point b(1, 0);
		Point c(0, 0);
		Point point(--Fixed(0.5F), --Fixed(0.5F));

		std::cout << "Point " << point << " is "
				  << (bsp(a, b, c, point) ? "INSIDE" : "OUTSIDE")
				  << " the triangle." << '\n';
	}
	{
		Point a(0, 1);
		Point b(1, 0);
		Point c(0, 0);
		Point point(0.499F, 0.499F);

		std::cout << "Point " << point << " is "
				  << (bsp(a, b, c, point) ? "INSIDE" : "OUTSIDE")
				  << " the triangle." << '\n';
	}
}

// NOLINTEND
