#pragma once

#include "libftpp/Expected.hpp"
#include <stack>
#include <string>

class RPN {
public:
	enum Operator {
		PLUS,
		MINUS,
		STAR,
		SLASH
	};

	RPN();
	RPN(const RPN& other);
	RPN& operator=(const RPN& other);
	~RPN();

	ft::Expected<long, std::string> calculate(std::string& input);
	ft::Expected<long, std::string> result();

private:
	void _push_operator(Operator op);
	void _push_operand(const std::string& word);

	std::stack<long> _stack;
};
