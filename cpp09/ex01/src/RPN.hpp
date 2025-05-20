#pragma once

#include "libftpp/Expected.hpp"
#include <stack>
#include <string>

class RPN {
public:
	enum Token {
		PLUS,
		MINUS,
		STAR,
		SLASH
	};

	RPN();
	RPN(const RPN& other);
	RPN& operator=(const RPN& other);
	~RPN();

	ft::Expected<long, std::string> calculate(const std::string& input);
	ft::Expected<long, std::string> result();

private:
	void _push_operator(Token op);
	void _push_operand(const std::string& word);

	std::stack<long> _stack;
};
