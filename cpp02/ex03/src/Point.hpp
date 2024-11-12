// NOLINTBEGIN(cppcoreguidelines-avoid-const-or-ref-data-members)

#ifndef POINT_HPP
#define POINT_HPP

#include "Fixed.hpp"
#include <ostream>

class Point {
public:
	typedef Point Vector;

	Point();
	Point(float x, float y);
	Point(const Fixed& x, const Fixed& y);
	Point(const Point& other);
	~Point();

	Point& operator=(const Point& other);
	Point operator-(const Point& other) const;

	Vector vec(const Point& point) const;
	Fixed cross(const Vector& vector) const;

	Fixed x() const;
	Fixed y() const;

private:
	const Fixed _x;
	const Fixed _y;
};

std::ostream& operator<<(std::ostream& os, const Point& point);

#endif

// NOLINTEND(cppcoreguidelines-avoid-const-or-ref-data-members)
