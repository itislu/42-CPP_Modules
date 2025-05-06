#pragma once

#include "Csv.hpp"
#include "libftpp/Expected.hpp"
#include "libftpp/algorithm.hpp"
#include "libftpp/format.hpp"
#include "libftpp/string.hpp"
#include <cassert>
#include <cstddef>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>

template <std::size_t Columns>
Csv<Columns>::Csv(const std::string& filename, char delim, bool trim_whitespace)
    : _filename(filename),
      _cur_row(),
      _cur_row_error(ft::unexpect),
      _cur_line_nbr(0),
      _is_eof(false),
      _delim(delim),
      _trim_whitespace(trim_whitespace)
{
	if (!ft::ends_with(_filename, ".csv")) {
		std::cerr << ft::log::warn("Csv: Filename does not end with \".csv\"")
		          << '\n';
	}
	_file.exceptions(std::ifstream::badbit);
	_file.open(_filename.c_str());
	if (!_file.is_open()) {
		throw std::runtime_error("Csv: Failed to open file \"" + _filename
		                         + "\"");
	}
}

template <std::size_t Columns>
Csv<Columns>::~Csv()
{}

template <std::size_t Columns>
typename Csv<Columns>::iterator Csv<Columns>::begin()
{
	_file.clear();
	_file.seekg(0);
	_cur_line_nbr = 0;
	_is_eof = false;
	return iterator(*this);
}

template <std::size_t Columns>
typename Csv<Columns>::iterator Csv<Columns>::end() const throw()
{
	return iterator();
}

template <std::size_t Columns>
const std::string& Csv<Columns>::filename() const throw()
{
	return _filename;
}

template <std::size_t Columns>
std::size_t Csv<Columns>::cur_line_nbr() const throw()
{
	return _cur_line_nbr;
}

template <std::size_t Columns>
bool Csv<Columns>::_process_next_line()
{
	std::string& line = _cur_row->line;
	if (!std::getline(_file, line)) {
		_is_eof = true;
		return false;
	}
	_cur_row->line_nbr = ++_cur_line_nbr;

	std::size_t col = 0;
	std::string::size_type cur_pos = 0;
	while (col < Columns && cur_pos != std::string::npos) {
		if (col > 0) {
			++cur_pos;
		}
		std::string::size_type next_pos = line.find(_delim, cur_pos);
		_cur_row->fields[col] = line.substr(cur_pos, next_pos - cur_pos);
		if (_trim_whitespace) {
			ft::trim(_cur_row->fields[col]);
		}
		cur_pos = next_pos;
		++col;
	}

	if (col < Columns || cur_pos != std::string::npos) {
		_cur_row_error.error() =
		    col < Columns ? "Not enough columns" : "Too many columns";
		return false;
	}
	return true;
}

template <std::size_t Columns>
Csv<Columns>::iterator::iterator() throw()
    : _csv_ptr(NULL),
      _cur_row_ptr(),
      _is_eof(true)
{}

template <std::size_t Columns>
Csv<Columns>::iterator::iterator(Csv& csv)
    : _csv_ptr(&csv),
      _cur_row_ptr(&csv._cur_row),
      _is_eof(csv._is_eof)
{
	_request_next_row();
}

template <std::size_t Columns>
Csv<Columns>::iterator::iterator(const iterator& other) throw()
    : _csv_ptr(other._csv_ptr),
      _cur_row_ptr(other._cur_row_ptr),
      _is_eof(other._is_eof)
{}

template <std::size_t Columns>
typename Csv<Columns>::iterator&
Csv<Columns>::iterator::operator=(iterator other) throw()
{
	swap(other);
	return *this;
}

template <std::size_t Columns>
Csv<Columns>::iterator::~iterator()
{}

template <std::size_t Columns>
typename Csv<Columns>::iterator::reference
Csv<Columns>::iterator::operator*() const throw()
{
	assert(_cur_row_ptr != NULL);
	return *_cur_row_ptr;
}

template <std::size_t Columns>
typename Csv<Columns>::iterator::pointer
Csv<Columns>::iterator::operator->() const throw()
{
	return _cur_row_ptr;
}

template <std::size_t Columns>
typename Csv<Columns>::iterator& Csv<Columns>::iterator::operator++()
{
	_request_next_row();
	return *this;
}

template <std::size_t Columns>
typename Csv<Columns>::iterator Csv<Columns>::iterator::operator++(int)
{
	iterator prev = *this;
	++(*this);
	return prev;
}

template <std::size_t Columns>
bool Csv<Columns>::iterator::operator==(const iterator& other) const throw()
{
	return _csv_ptr == other._csv_ptr && _is_eof == other._is_eof;
}

template <std::size_t Columns>
bool Csv<Columns>::iterator::operator!=(const iterator& other) const throw()
{
	return !(*this == other);
}

template <std::size_t Columns>
void Csv<Columns>::iterator::swap(iterator& other) throw()
{
	ft::swap(_csv_ptr, other._csv_ptr);
	ft::swap(_cur_row_ptr, other._cur_row_ptr);
	ft::swap(_is_eof, other._is_eof);
}

template <std::size_t Columns>
void Csv<Columns>::iterator::_request_next_row()
{
	if (_is_eof) {
		return;
	}
	if (_csv_ptr->_process_next_line()) {
		_cur_row_ptr = &_csv_ptr->_cur_row;
		return;
	}
	_cur_row_ptr = &_csv_ptr->_cur_row_error;
	if (_csv_ptr->_is_eof) {
		_is_eof = true;
		_csv_ptr = NULL;
	}
}

template <std::size_t Columns>
void swap(typename Csv<Columns>::iterator& lhs,
          typename Csv<Columns>::iterator& rhs) throw()
{
	lhs.swap(rhs);
}
