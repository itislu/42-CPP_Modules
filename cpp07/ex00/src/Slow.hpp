// NOLINTBEGIN(misc-non-private-member-variables-in-classes)

#pragma once

#include <cstddef>
#include <string>

class Slow {
public:
	Slow();
	Slow(std::size_t size, char c);
	Slow(const Slow& other);
	Slow& operator=(const Slow& other);
	~Slow();

protected:
	std::string _str;
};

// NOLINTEND(misc-non-private-member-variables-in-classes)
