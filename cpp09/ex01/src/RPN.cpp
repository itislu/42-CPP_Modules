#include "RPN.hpp"
#include "libftpp/Exception.hpp"
#include "libftpp/Expected.hpp"
#include "libftpp/Optional.hpp"
#include "libftpp/string.hpp"
#include "libftpp/utility.hpp"
#include <cstddef>
#include <math.h>
#include <sstream>
#include <string>

static ft::Optional<RPN::Operator> get_operator(const std::string& word);

RPN::RPN() {}

RPN::RPN(const RPN& other)
    : _stack(other._stack)
{}

RPN& RPN::operator=(const RPN& other)
{
	if (&other != this) {
		_stack = other._stack;
	}
	return *this;
}

RPN::~RPN() {}

ft::Expected<RPN::value_type, std::string>
RPN::calculate(const std::string& input)
{
	std::istringstream word_stream(input);
	std::string word;
	std::size_t operator_count = 0;
	std::size_t operand_count = 0;

	while (word_stream >> word) {
		const ft::Optional<Operator> op = get_operator(word);
		if (op) {
			++operator_count;
			try {
				_push_operator(*op);
			}
			catch (const ft::Exception& e) {
				// Keep what was processed so far.
				return ft::Unexpected<std::string>(
				    "stopping at operator #" + ft::to_string(operator_count)
				    + " (" + word + "): " + e.error());
			}
		}
		else {
			++operand_count;
			try {
				_push_operand(word);
			}
			catch (const ft::Exception& e) {
				// Keep what was processed so far.
				return ft::Unexpected<std::string>(
				    "stopping at operand #" + ft::to_string(operand_count)
				    + ": " + e.error());
			}
		}
	}
	return result();
}

ft::Expected<RPN::value_type, std::string> RPN::result()
{
	if (_stack.empty()) {
		return ft::Unexpected<std::string>("empty");
	}
	if (_stack.size() > 1) {
		// Keep what was processed so far.
		const std::size_t missing_ops = _stack.size() - 1;
		return ft::Unexpected<std::string>(
		    "missing " + ft::to_string(missing_ops) + " operator"
		    + (missing_ops > 1 ? "s" : ""));
	}
	return _stack.top();
}

void RPN::_push_operator(Operator op)
{
	if (_stack.size() < 2) {
		throw ft::Exception("missing operand");
	}
	const value_type rhs = _stack.top();
	_stack.pop();
	const value_type lhs = _stack.top();
	_stack.pop();

	try {
		const value_type result = _calc_checked(op, lhs, rhs);
		_stack.push(result);
	}
	catch (const ft::Exception&) {
		_stack.push(lhs);
		_stack.push(rhs);
		throw;
	}
}

RPN::value_type RPN::_calc_checked(Operator op, value_type lhs, value_type rhs)
{
	value_type result = 0;
	switch (op) {
	case ADD:
		result = lhs + rhs;
		break;
	case SUB:
		result = lhs - rhs;
		break;
	case MUL:
		result = lhs * rhs;
		break;
	case DIV:
		if (rhs == 0) {
			throw ft::Exception("division by zero");
		}
		result = lhs / rhs;
		break;
	}

	switch (fpclassify(result)) {
	case FP_INFINITE:
		throw ft::Exception("result out of range for "
		                    + ft::demangle(typeid(value_type).name()));
	case FP_NAN:
		throw ft::Exception("result is NaN");
	case FP_SUBNORMAL:
		throw ft::Exception("floating point underflow");
	default:
		return result;
	}
}

void RPN::_push_operand(const std::string& word)
{
	std::string::size_type endpos = 0;
	const value_type operand = ft::from_string<value_type>(word, &endpos);
	if (endpos != word.length()) {
		throw ft::Exception("excess characters: \"" + word + "\"");
	}

	switch (fpclassify(operand)) {
	case FP_INFINITE:
		throw ft::Exception("infinity not allowed");
	case FP_NAN:
		throw ft::Exception("NaN not allowed");
	case FP_SUBNORMAL:
		throw ft::Exception("subnormal number: " + word);
	default:
		_stack.push(operand);
	}
}

static ft::Optional<RPN::Operator> get_operator(const std::string& word)
{
	if (word.length() != 1) {
		return ft::nullopt;
	}
	switch (word[0]) {
	case RPN::ADD:
	case RPN::SUB:
	case RPN::MUL:
	case RPN::DIV:
		return static_cast<RPN::Operator>(word[0]);
	default:
		return ft::nullopt;
	}
}
