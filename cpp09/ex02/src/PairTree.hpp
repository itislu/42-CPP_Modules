#pragma once

#include <list>

// TODO Need to write that the iterators passed must not change outside.
/**
 * 16: .......1.......L
 *  8:         ...2...L
 *  4:             .3.L
 *  2:               4L
 *  1:                L
 * L = _last, N = _halfs
 */
template <typename T>
class PairTree {
public:
	typedef typename std::list<T>::iterator value_type;
	typedef typename std::list<T>::size_type size_type;
	typedef typename std::list<PairTree>::difference_type difference_type;
	typedef value_type& reference;
	typedef const value_type& const_reference;
	typedef value_type* pointer;
	typedef const value_type* const_pointer;
	typedef typename std::list<PairTree>::iterator iterator;

	explicit PairTree(const value_type& pos);
	PairTree(const PairTree& other);
	PairTree& operator=(PairTree other);
	~PairTree();

	bool operator<(const PairTree& other) const;

	void insert(std::list<PairTree>& src_lst, iterator node);
	void split(std::list<PairTree>& dest_lst, iterator dest_pos);
	void swap(PairTree& other);

	const_reference first() const;
	const_reference last() const throw();
	size_type size() const throw();

private:
	PairTree();

	std::list<PairTree> _halfs; // Front is first child.
	value_type _last;
	size_type _size;
};

#include "PairTree.tpp" // IWYU pragma: export
