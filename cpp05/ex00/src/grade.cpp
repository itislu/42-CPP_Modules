#include "grade.hpp"

bool grade::is_higher(unsigned int a, unsigned int b) { return a < b; }

bool grade::is_lower(unsigned int a, unsigned int b) { return a > b; }

unsigned int grade::increment(unsigned int grade) { return grade - 1; }

unsigned int grade::decrement(unsigned int grade) { return grade + 1; }
