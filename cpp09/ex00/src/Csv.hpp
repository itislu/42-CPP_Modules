#pragma once

#include "libftpp/Array.hpp"
#include "libftpp/Expected.hpp"
#include "libftpp/assert.hpp"
#include <cstddef>
#include <fstream>
#include <iterator>
#include <string>

/**
 * Lazy iteration over a filestream.
 * Does not support quoting of fields.
 * `iterator` loosely follows design of `std::istream_iterator`.
 * `++begin()` is guaranteed to be comparable to allow skipping a header.
 *
 * The class is templated in order to use `ft::Array` and avoid `std::vector`
 * for subject requirements.
 */
template <std::size_t Columns>
class Csv {
	STATIC_ASSERT(Columns > 0); // Csv<Columns>: Columns must be greater than 0.

public:
	struct Row;

	class iterator;
	typedef iterator const_iterator;
	typedef ft::Expected<Row, std::string> value_type;
	typedef std::size_t size_type;
	typedef typename iterator::difference_type difference_type;
	typedef const value_type& reference;
	typedef const value_type& const_reference;
	typedef const value_type* pointer;
	typedef const value_type* const_pointer;

	struct Row { // NOLINT(cppcoreguidelines-pro-type-member-init)
		ft::Array<std::string, Columns> fields;
		std::string line;
		size_type line_nbr;
	};

	explicit Csv(const std::string& filename,
	             const std::string& delim = ",",
	             bool trim_whitespace = false);
	~Csv();

	iterator begin();
	iterator end() const throw();

	const std::string& filename() const throw();
	size_type cur_line_nbr() const throw();

private:
	Csv();
	Csv(const Csv& other);
	Csv& operator=(Csv other);

	bool _process_next_line();

	std::ifstream _file;
	std::string _filename;
	value_type _cur_row;
	value_type _cur_row_error;
	size_type _cur_line_nbr;
	std::string _delim;
	bool _trim_whitespace;
	bool _is_eof;
};

template <std::size_t Columns>
class Csv<Columns>::iterator {
public:
	typedef std::input_iterator_tag iterator_category;
	typedef typename Csv<Columns>::value_type value_type;
	typedef std::ptrdiff_t difference_type;
	typedef const value_type& reference;
	typedef const value_type* pointer;

	iterator() throw();
	explicit iterator(Csv& csv);
	iterator(const iterator& other) throw();
	iterator& operator=(iterator other) throw();
	~iterator();

	reference operator*() const throw();
	pointer operator->() const throw();
	iterator& operator++();
	iterator operator++(int);
	bool operator==(const iterator& other) const throw();
	bool operator!=(const iterator& other) const throw();

	void swap(iterator& other) throw();

private:
	void _request_next_row();

	Csv* _csv_ptr;
	value_type* _cur_row_ptr;
	bool _is_eof;
};

template <std::size_t Columns>
void swap(typename Csv<Columns>::iterator& lhs,
          typename Csv<Columns>::iterator& rhs) throw();

#include "Csv.tpp" // IWYU pragma: export
