#pragma once

#include <ostream>

class Grade {
public:
	static const unsigned int highest_grade = 1;
	static const unsigned int lowest_grade = 150;

	Grade(unsigned int grade);
	Grade(const Grade& other);
	~Grade();

	Grade& operator=(Grade other) throw();
	void swap(Grade& other) throw();

	Grade& operator++();
	Grade& operator--();
	Grade operator++(int);
	Grade operator--(int);
	bool operator>(const Grade& other) const;
	bool operator<(const Grade& other) const;
	bool operator>(unsigned int other) const;
	bool operator<(unsigned int other) const;

	void test(const Grade& min) const;
	unsigned int get() const;

private:
	Grade();

	unsigned int _raw;
};

std::ostream& operator<<(std::ostream& os, const Grade& grade);
