#include "IntWithId.hpp"
#include <ostream>

unsigned int IntWithId::_next_id = 1;

IntWithId::IntWithId(int value)
    : _id(_next_id++),
      _value(value)

{}

IntWithId::IntWithId(const IntWithId& other)
    : _id(_next_id++),
      _value(other._value)

{}

IntWithId& IntWithId::operator=(const IntWithId& other)
{
	if (&other == this) {
		return *this;
	}
	_value = other._value;
	return *this;
}

IntWithId::~IntWithId() {}

IntWithId& IntWithId::operator=(int value)
{
	_value = value;
	return *this;
}

bool IntWithId::operator<(const IntWithId& rhs) const
{
	return _value < rhs._value;
}

unsigned int IntWithId::id() const { return _id; }

int IntWithId::value() const { return _value; }

std::ostream& operator<<(std::ostream& os, const IntWithId& int_with_id)
{
	os << "id: " << int_with_id.id() << ", value: " << int_with_id.value();
	return os;
}
