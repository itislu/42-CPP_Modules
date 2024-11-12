// NOLINTBEGIN(performance-unnecessary-value-param)

#include "Fixed.hpp"
#include "Point.hpp"

bool bsp(Point const a, Point const b, Point const c, Point const point)
{
	const Fixed abp = a.vec(b).cross(a.vec(point));
	const Fixed bcp = b.vec(c).cross(b.vec(point));
	const Fixed cap = c.vec(a).cross(c.vec(point));

	if (abp == 0 || bcp == 0 || cap == 0) {
		return false;
	}
	return (abp > 0) == (bcp > 0) && (abp > 0) == (cap > 0);
}

// NOLINTEND(performance-unnecessary-value-param)
