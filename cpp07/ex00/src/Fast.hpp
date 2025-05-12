#pragma once

#include "Slow.hpp"
#include <cstddef>

class Fast : public Slow {
public:
	Fast();
	Fast(std::size_t size, char c);
	Fast(const Fast& other);
	Fast& operator=(const Fast& other);
	~Fast();

	void swap(Fast& other);
};
