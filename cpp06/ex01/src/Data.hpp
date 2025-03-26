#pragma once

#include <ostream>
#include <string>

struct Data {
	std::string s;
	void* p;
	double d;
	int i;
};

std::ostream& operator<<(std::ostream& os, const Data& data);
