#pragma once

#include "Csv.hpp"
#include "libftpp/format.hpp"
#include "libftpp/string.hpp"
#include <algorithm>
#include <cassert>
#include <cstddef>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <utility>

template <std::size_t Columns>
Csv<Columns>::Csv(const std::string& filename,
                  char delim,
                  bool has_header,
                  bool trim_whitespace,
                  OnRowError on_row_error)
    : _filename(filename),
      _line_nbr(0),
      _on_row_error(on_row_error),
      _delim(delim),
      _has_header(has_header),
      _trim_whitespace(trim_whitespace)
{
	if (!ft::ends_with(_filename, ".csv")) {
		std::cerr << ft::log::warn("Csv: filename does not end with \".csv\"")
		          << '\n';
	}
	_file.exceptions(std::ifstream::badbit);
	_file.open(_filename.c_str());
	if (!_file.is_open()) {
		throw std::runtime_error("Csv: failed to open file \"" + _filename
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
	_line_nbr = 0;
	if (_has_header) {
		typename iterator::value_type header;
		_process_next_line(header);
	}
	return iterator(*this);
}

template <std::size_t Columns>
typename Csv<Columns>::iterator Csv<Columns>::end()
{
	return iterator();
}

template <std::size_t Columns>
bool Csv<Columns>::_process_next_line(typename iterator::value_type& out_fields)
{
	while (true) {
		std::string line;
		if (!std::getline(_file, line)) {
			return false;
		}
		++_line_nbr;

		std::size_t col = 0;
		std::string::size_type cur_pos = 0;
		while (col < Columns && cur_pos != std::string::npos) {
			if (col > 0) {
				++cur_pos;
			}
			std::string::size_type next_pos = line.find(_delim, cur_pos);
			out_fields[col] = std::make_pair(
			    line.substr(cur_pos, next_pos - cur_pos), _line_nbr);
			if (_trim_whitespace) {
				ft::trim(out_fields[col].first);
			}
			cur_pos = next_pos;
			++col;
		}

		if (col < Columns || cur_pos != std::string::npos) {
			const std::string msg = _filename + ":" + ft::to_string(_line_nbr)
			                        + (col < Columns ? ": Not enough columns"
			                                         : ": Too many columns");
			switch (_on_row_error) {
			case Skip:
				std::cerr << ft::log::warn(msg) << '\n';
				continue;
			case Stop:
				std::cerr << ft::log::error(msg) << '\n';
				return false;
			case Throw:
				throw std::runtime_error(msg);
			}
		}
		return true;
	}
}

template <std::size_t Columns>
Csv<Columns>::iterator::iterator()
    : _csv(NULL),
      _cur_row()
{}

template <std::size_t Columns>
Csv<Columns>::iterator::iterator(Csv& csv)
    : _csv(&csv),
      _cur_row()
{
	_store_next_row();
}

template <std::size_t Columns>
Csv<Columns>::iterator::iterator(const iterator& other)
    : _csv(other._csv),
      _cur_row(other._cur_row)
{}

template <std::size_t Columns>
typename Csv<Columns>::iterator&
Csv<Columns>::iterator::operator=(iterator other)
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
	return _cur_row;
}

template <std::size_t Columns>
typename Csv<Columns>::iterator::pointer
Csv<Columns>::iterator::operator->() const throw()
{
	return &_cur_row;
}

template <std::size_t Columns>
typename Csv<Columns>::iterator& Csv<Columns>::iterator::operator++()
{
	_store_next_row();
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
	return _csv == other._csv;
}

template <std::size_t Columns>
bool Csv<Columns>::iterator::operator!=(const iterator& other) const throw()
{
	return !(*this == other);
}

template <std::size_t Columns>
void Csv<Columns>::iterator::swap(iterator& other)
{
	using std::swap;
	swap(_csv, other._csv);
	swap(_cur_row, other._cur_row);
}

template <std::size_t Columns>
void Csv<Columns>::iterator::_store_next_row()
{
	assert(_csv != NULL);
	if (!_csv->_process_next_line(_cur_row)) {
		_csv = NULL;
	}
}

template <std::size_t Columns>
void swap(typename Csv<Columns>::iterator& lhs,
          typename Csv<Columns>::iterator& rhs)
{
	lhs.swap(rhs);
}
