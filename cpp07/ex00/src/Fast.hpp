#pragma once

#include "Slow.hpp"

class Fast : public Slow {
public:
	Fast();
	Fast(const Fast& other);
	Fast& operator=(const Fast& other);
	~Fast();

	void swap(Fast& other);
};
