// NOLINTBEGIN(cppcoreguidelines-pro-bounds-constant-array-index)

#include "Intern.hpp"
#include "AForm.hpp"
#include "PresidentialPardonForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include "utils/Exception.hpp"
#include "utils/common.hpp"
#include "utils/log.hpp"
#include <cctype>
#include <cstddef>
#include <iostream>
#include <string>

static std::string split_words(const std::string& form);
static std::string change_capitalization(std::string words,
                                         int (*to)(int),
                                         bool first_only = false);
static std::string concat_words(const std::string& words);
static std::string::size_type next_word(const std::string& words,
                                        std::string::size_type i);

const char* Intern::forms[] = {"PresidentialPardonForm",
                               "RobotomyRequestForm",
                               "ShrubberyCreationForm"};
AForm* (*const Intern::_factory[])(const std::string&) = {
    &_makePresidentialPardonForm,
    &_makeRobotomyRequestForm,
    &_makeShrubberyCreationForm,
};
bool Intern::_is_init = false;

Intern::UnknownFormException::UnknownFormException(const std::string& where)
    : utils::Exception("Unknown form", where, "Intern")
{}

void Intern::print_known_forms()
{
	std::cout << "The Intern can accept the following forms:" << "\n\n";

	for (FormType type = Unknown; _iter_form_types(type);) {
		std::string::size_type start = 1;

		for (std::string::size_type end = _known_forms(type).find('\0', start);
		     end != std::string::npos;
		     end = _known_forms(type).find('\0', start)) {
			std::cout << "  - " << _known_forms(type).substr(start, end - start)
			          << '\n';
			start = end + 1;
		}
		std::cout << '\n';
	}
}

Intern::Intern()
{
	if (!_is_init) {
		_init_known_forms();
	}
}

Intern::~Intern() {}

// NOLINTNEXTLINE(readability-convert-member-functions-to-static)
AForm* Intern::makeForm(const std::string& form,
                        const std::string& target) const
{
	AForm* new_form = NULL;

	switch (const FormType type = _which_form(form)) {
	case PresidentialPardonForm:
	case RobotomyRequestForm:
	case ShrubberyCreationForm:
		new_form = _factory[type](target);
		break;
	case Unknown:
		std::cout << "A form named '" << form << "' does not exist" << '\n';
		throw UnknownFormException(WHERE);
	}
	std::cout << "Intern creates " << new_form->name() << '\n';
	return new_form;
}

AForm* Intern::_makePresidentialPardonForm(const std::string& target)
{
	return new class PresidentialPardonForm(target);
}

AForm* Intern::_makeRobotomyRequestForm(const std::string& target)
{
	return new class RobotomyRequestForm(target);
}

AForm* Intern::_makeShrubberyCreationForm(const std::string& target)
{
	return new class ShrubberyCreationForm(target);
}

bool Intern::_iter_form_types(FormType& it)
{
	it = FormType((it + 1) % (Unknown + 1));
	return it != Unknown;
}

/**
 * Split form names into words by uppercase letters, then generate
 * permutations of form names and save in _known_forms with '\0' as seperator.
 */
void Intern::_init_known_forms()
{
	if (_is_init) {
		return;
	}
	for (FormType type = Unknown; _iter_form_types(type);) {
		const std::string words(split_words(forms[type]));

		_known_forms(type) = '\0';
		_known_forms(type).append(
		    concat_words(change_capitalization(words, toupper)));
		_known_forms(type).append(
		    concat_words(change_capitalization(words, tolower)));
		_known_forms(type).append(concat_words(change_capitalization(
		    change_capitalization(words, tolower), toupper, true)));
	}
	_is_init = true;
}

std::string& Intern::_known_forms(FormType form)
{
	static std::string _known_forms[ARRAY_SIZE(forms)];
	return _known_forms[form];
}

Intern::FormType Intern::_which_form(const std::string& input)
{
	if (input.empty()) {
		return Unknown;
	}
	for (FormType type = Unknown; _iter_form_types(type);) {
		const std::string::size_type pos =
		    _known_forms(type).find('\0' + input + '\0');
		if (pos != std::string::npos) {
			return type;
		}
	}
	return Unknown;
}

/**
 * Insert a space before any sequence of uppercase letters.
 */
static std::string split_words(const std::string& form)
{
	std::string words(form);

	for (std::string::size_type i = 1; i < words.length(); ++i) {
		if (static_cast<bool>(isupper(words[i]))
		    && !static_cast<bool>(isupper(words[i - 1]))) {
			words.insert(i++, " ");
		}
	}
	return words;
}

static std::string
change_capitalization(std::string words, int (*to)(int), bool first_only)
{
	if (first_only) {
		words[0] = static_cast<char>(to(words[0]));
		return words;
	}
	for (std::string::size_type i = next_word(words, std::string::npos);
	     i != std::string::npos;
	     i = next_word(words, i)) {
		words[i] = static_cast<char>(to(words[i]));
	}
	return words;
}

/**
 * - For all-uppercase words:
 * - For all-lowercase words:
 * - For only first word uppercase:
 *     - For all allowed seperators:
 *         - Concatenate all words.
 *         - Concatenate all but "form" word.
 *             - Append "form" word with space.
 */
static std::string concat_words(const std::string& words)
{
	const std::string sep[] = {" ", "-", "_", ""};
	std::string options;

	for (unsigned int i = 0; i < ARRAY_SIZE(sep); ++i) {
		std::string option(words);
		std::string::size_type last_word = 0;

		for (std::string::size_type word = next_word(option, 0);
		     word != std::string::npos;
		     word = next_word(option, word)) {
			option.replace(word - 1, 1, sep[i]);
			last_word = word - (1 - sep[i].length());
		}
		options.append(option + '\0');
		options.append(option.substr(0, last_word - sep[i].length()) + '\0');
		option.replace(last_word - sep[i].length(), sep[i].length(), " ");
		options.append(option + '\0');
	}
	return options;
}

/**
 * Find words separated by a space.
 * Iterator-like. Start with std::string::npos.
 */
static std::string::size_type next_word(const std::string& words,
                                        std::string::size_type i)
{
	if (i == std::string::npos) {
		return 0;
	}
	const std::string::size_type word = words.find(' ', i + 1);
	if (word == std::string::npos) {
		return std::string::npos;
	}
	return word + 1;
}

// NOLINTEND(cppcoreguidelines-pro-bounds-constant-array-index)
