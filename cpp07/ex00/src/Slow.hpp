// NOLINTBEGIN(misc-non-private-member-variables-in-classes)

#pragma once

#include <cstddef>
#include <string>

class Slow {
public:
	static std::size_t string_init_size;

	Slow();
	Slow(const Slow& other);
	Slow& operator=(const Slow& other);
	~Slow();

protected:
	std::string _str;
};

// NOLINTEND(misc-non-private-member-variables-in-classes)
