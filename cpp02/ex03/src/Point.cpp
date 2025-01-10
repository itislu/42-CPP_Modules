#include "Point.hpp"
#include "Fixed.hpp"
#include <ostream>

Point::Point() : _x(0), _y(0) {}

Point::Point(const float x, const float y) : _x(x), _y(y) {}

Point::Point(const Fixed& x, const Fixed& y) : _x(x), _y(y) {}

Point::Point(const Point& other) : _x(other._x), _y(other._y) {}

Point::~Point() {}

// Nothing to copy
Point& Point::operator=(const Point& other)
{
	if (this != &other) {
	}
	return *this;
}

Point Point::operator-(const Point& other) const
{
	return Point(this->_x - other._x, this->_y - other._y);
}

bool Point::bad()
{
	return Fixed::bad();
}

void Point::clear()
{
	Fixed::clear();
}

Point::Vector Point::vec(const Point& point) const
{
	return point - *this;
}

Fixed Point::cross(const Point::Vector& vector) const
{
	return (this->_x.toFloat() * vector._y.toFloat())
	       - (vector._x.toFloat() * this->_y.toFloat());
}

Fixed Point::x() const
{
	return this->_x;
}

Fixed Point::y() const
{
	return this->_y;
}

std::ostream& operator<<(std::ostream& os, const Point& point)
{
	return os << "(" << point.x() << ", " << point.y() << ")";
}
