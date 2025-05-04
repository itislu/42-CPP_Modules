#pragma once

#include "libftpp/Array.hpp"
#include <cstddef>
#include <fstream>
#include <iterator>
#include <string>
#include <utility>

/**
 * Lazy iteration over a filestream.
 * Does not support quoting of fields.
 * Iterator loosely follows design of `std::istream_iterator`.
 */
template <std::size_t Columns>
class Csv {
public:
	class iterator;

	typedef typename iterator::value_type value_type;
	typedef std::size_t size_type;
	typedef typename iterator::difference_type difference_type;
	typedef typename iterator::reference reference;
	typedef typename iterator::reference const_reference;
	typedef typename iterator::pointer pointer;
	typedef typename iterator::pointer const_pointer;
	typedef iterator iterator;
	typedef iterator const_iterator;

	class iterator {
	public:
		typedef std::input_iterator_tag iterator_category;
		typedef ft::Array<
		    std::pair<std::string /*field*/, std::size_t /*line number*/>,
		    Columns>
		    value_type;
		typedef std::ptrdiff_t difference_type;
		typedef const value_type* pointer;
		typedef const value_type& reference;

		iterator();
		iterator(Csv& csv);
		iterator(const iterator& other);
		iterator& operator=(iterator other);
		~iterator();

		reference operator*() const throw();
		pointer operator->() const throw();
		iterator& operator++();
		iterator operator++(int);
		bool operator==(const iterator& other) const throw();
		bool operator!=(const iterator& other) const throw();

		void swap(iterator& other);

	private:
		void _store_next_row();

		Csv* _csv;
		value_type _cur_row;
	};

	enum OnRowError {
		Skip,
		Stop,
		Throw
	};

	Csv(const std::string& filename,
	    char delim = ',',
	    bool has_header = true,
	    bool trim_whitespace = true,
	    OnRowError on_row_error = Skip);
	~Csv();

	iterator begin();
	iterator end();

private:
	Csv();
	Csv(const Csv& other);
	Csv& operator=(Csv other);

	bool _process_next_line(value_type& out_fields);

	std::ifstream _file;
	std::string _filename;
	std::size_t _line_nbr;
	OnRowError _on_row_error;
	char _delim;
	bool _has_header;
	bool _trim_whitespace;
};

template <>
class Csv<0>;

template <std::size_t Columns>
void swap(typename Csv<Columns>::iterator& lhs,
          typename Csv<Columns>::iterator& rhs);

#include "Csv.tpp" // IWYU pragma: export
