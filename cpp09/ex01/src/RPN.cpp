#include "RPN.hpp"
#include "libftpp/Exception.hpp"
#include "libftpp/Expected.hpp"
#include "libftpp/Optional.hpp"
#include "libftpp/numeric.hpp"
#include "libftpp/string.hpp"
#include <cstddef>
#include <sstream>
#include <string>

static ft::Optional<RPN::Token> get_operator_token(const std::string& word);

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

ft::Expected<long, std::string> RPN::calculate(const std::string& input)
{
	std::istringstream word_stream(input);
	std::string word;
	std::size_t operator_count = 0;
	std::size_t operand_count = 0;

	while (word_stream >> word) {
		const ft::Optional<Token> op_token = get_operator_token(word);
		if (op_token) {
			++operator_count;
			try {
				_push_operator(*op_token);
			}
			catch (const ft::Exception& e) {
				// keeps progress
				return ft::Unexpected<std::string>(
				    "operator #" + ft::to_string(operator_count) + " (" + word
				    + "): " + e.error());
			}
		}
		else {
			++operand_count;
			try {
				_push_operand(word);
			}
			catch (const ft::Exception& e) {
				// keeps progress
				return ft::Unexpected<std::string>(
				    "operand #" + ft::to_string(operand_count) + ": "
				    + e.error());
			}
		}
	}
	return result();
}

ft::Expected<long, std::string> RPN::result()
{
	if (_stack.empty()) {
		return ft::Unexpected<std::string>("empty");
	}
	if (_stack.size() > 1) {
		// keeps progress
		const std::size_t missing = _stack.size() - 1;
		return ft::Unexpected<std::string>("missing " + ft::to_string(missing)
		                                   + " operator"
		                                   + (missing > 1 ? "s" : ""));
	}
	return _stack.top();
}

void RPN::_push_operator(Token op_token)
{
	long (*operation)(long, long); // NOLINT(cppcoreguidelines-init-variables)
	switch (op_token) {
	case PLUS:
		operation = ft::add_throw;
		break;
	case MINUS:
		operation = ft::sub_throw;
		break;
	case STAR:
		operation = ft::mul_throw;
		break;
	case SLASH:
		operation = ft::div_throw;
		break;
	}

	if (_stack.size() < 2) {
		throw ft::Exception("missing operand");
	}
	const long rhs = _stack.top();
	_stack.pop();
	const long lhs = _stack.top();
	_stack.pop();

	try {
		_stack.push(operation(lhs, rhs));
	}
	catch (const ft::ArithmeticException&) {
		_stack.push(lhs);
		_stack.push(rhs);
		throw;
	}
}

void RPN::_push_operand(const std::string& word)
{
	std::string::size_type endpos = 0;
	const long operand = ft::from_string<long>(word, &endpos);
	if (endpos != word.length()) {
		throw ft::Exception("excess characters: \"" + word + "\"");
	}
	_stack.push(operand);
}

static ft::Optional<RPN::Token> get_operator_token(const std::string& word)
{
	if (word.length() != 1) {
		return ft::nullopt;
	}
	switch (word[0]) {
	case '+':
		return RPN::PLUS;
	case '-':
		return RPN::MINUS;
	case '*':
		return RPN::STAR;
	case '/':
		return RPN::SLASH;
	default:
		return ft::nullopt;
	}
}
