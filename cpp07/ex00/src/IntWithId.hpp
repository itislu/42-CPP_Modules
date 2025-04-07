#pragma once

#include "libftpp/operators.hpp"
#include <ostream>

class IntWithId : ft::operators::Comparison {
public:
	IntWithId(int value);
	IntWithId(const IntWithId& other);
	IntWithId& operator=(const IntWithId& other);
	~IntWithId();

	bool operator<(const IntWithId& rhs) const;

	unsigned int id() const;
	int value() const;

private:
	static unsigned int _next_id;

	IntWithId();

	unsigned int _id;
	int _value;
};

std::ostream& operator<<(std::ostream& os, const IntWithId& int_with_id);
