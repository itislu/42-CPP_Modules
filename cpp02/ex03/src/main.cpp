// NOLINTBEGIN

#include "Fixed.hpp"
#include "Point.hpp"
#include <iostream>
#include <sstream>

bool bsp(Point const a, Point const b, Point const c, Point const point);
static void test_triangle(Point& a, Point& b, Point& c, Point& point);
static float ft_atof(char* str);

int main(int argc, char* argv[])
{
	if (argc > 1 && argc != 3) {
		std::cerr << "Usage: " << argv[0] << " <x> <y> (in unit triangle: 📐)"
		          << '\n';
		return 1;
	}

	if (argc == 3) {
		Point a(0, 1);
		Point b(1, 0);
		Point c(0, 0);
		float x = ft_atof(argv[1]);
		float y = ft_atof(argv[2]);
		Point point(x, y);
		test_triangle(a, b, c, point);
	}
	else {
		// Default tests
		{
			Point a(0, 4);
			Point b(5, 0);
			Point c(0, 0);
			Point point(0.002, 1);
			test_triangle(a, b, c, point);
		}
		{
			Point a(0, 1);
			Point b(1, 0);
			Point c(0, 0);
			Point point(0.499F, 0.499F);
			test_triangle(a, b, c, point);
		}
		{
			Point a(0, 1);
			Point b(1, 0);
			Point c(0, 0);
			Point point(--Fixed(0.5F), --Fixed(0.5F));
			test_triangle(a, b, c, point);
		}
		{
			Point a(0, 1);
			Point b(1, 0);
			Point c(0, 0);
			Point point(0.1015625, -8388608);
			test_triangle(a, b, c, point);
		}
		{
			Point a(-8388608, 8388608);
			Point b(8388608, -8388608);
			Point c(-8388608, -8388608);
			Point point(-10.1015625, -10);
			test_triangle(a, b, c, point);
		}
	}
}

static void test_triangle(Point& a, Point& b, Point& c, Point& point)
{
	std::cout << "Point " << point << " is "
	          << (bsp(a, b, c, point) ? "INSIDE" : "OUTSIDE")
	          << " the triangle." << '\n';
}

static float ft_atof(char* str)
{
	std::istringstream ss(str);
	float f;
	ss >> f;
	return f;
}

// NOLINTEND
