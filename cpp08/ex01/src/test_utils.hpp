#pragma once

#include "Span.hpp"
#include <string>

void add_many_intervaled(unsigned int amount, unsigned int intervals);
void add_many_timed(unsigned int amount);
void print_addNumber(Span& sp, int nbr);
template <typename InputIt>
void print_addNumber(Span& sp, const InputIt& first, const InputIt& last);
void print_spans(const Span& sp);
void print_seperator(const std::string& title);

#include "test_utils.tpp" // IWYU pragma: export
