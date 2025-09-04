#pragma once

#include "libftpp/Expected.hpp"
#include <stack>
#include <string>

class RPN {
public:
	typedef long double value_type;

	enum Operator {
		ADD = '+',
		SUB = '-',
		MUL = '*',
		DIV = '/'
	};

	RPN();
	RPN(const RPN& other);
	RPN& operator=(const RPN& other);
	~RPN();

	ft::Expected<value_type, std::string> calculate(const std::string& input);
	ft::Expected<value_type, std::string> result();

private:
	void _push_operator(Operator op);
	void _push_operand(const std::string& word);

	std::stack<value_type> _stack;
};
