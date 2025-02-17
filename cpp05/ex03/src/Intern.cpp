// NOLINTBEGIN(cppcoreguidelines-pro-bounds-constant-array-index)

#include "Intern.hpp"
#include "AForm.hpp"
#include "utils/log.hpp"
#include "utils/utils.hpp"
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

const std::string Intern::forms[] = {"PresidentialPardonForm",
                                     "RobotomyRequestForm",
                                     "ShrubberyCreationForm"};
std::string Intern::_known_forms;

AForm* Intern::makeForm(const std::string& form, const std::string& target)
{
	if (!_is_known_form(form)) {
		std::cout << utils::log::error("A form named '" + form
		                               + "' does not exist.")
		          << '\n';
		return NULL;
	}
	std::cout << utils::log::ok("Found form '" + form + "'!") << '\n';
	(void)target;
	return NULL;
}

void Intern::print_known_forms()
{
	std::string::size_type start = 0;
	std::string::size_type end = 0;

	while (end < _known_forms.length()) {
		end = _known_forms.find('\0', start);
		std::cout << _known_forms.substr(start, end - start) << '\n';
		start = end + 1;
	}
}

Intern::Intern()
{
	if (_known_forms.empty()) {
		_init_known_forms();
	}
}

Intern::~Intern() {}

bool Intern::_is_known_form(const std::string& input)
{
	return _known_forms.find(input + '\0') != std::string::npos;
}

/**
 * Split form names into words by uppercase letters, then generate
 * permutations of form names and save in _known_forms with '\0' as seperator.
 */
void Intern::_init_known_forms()
{
	for (unsigned int i = 0; i < ARRAY_SIZE(forms); ++i) {
		const std::string words(split_words(forms[i]));

		_known_forms.append(
		    concat_words(change_capitalization(words, toupper)));
		_known_forms.append(
		    concat_words(change_capitalization(words, tolower)));
		_known_forms.append(
		    concat_words(change_capitalization(words, toupper, true)));
	}
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
 *         - Concatenate all but "Form" word.
 *             - Append "Form" word with space.
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
