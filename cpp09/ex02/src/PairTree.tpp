#pragma once

#include "PairTree.hpp"
#include <algorithm>
#include <list>

template <typename T>
PairTree<T>::PairTree(const value_type& pos)
    : _last(pos),
      _size(1)
{}

template <typename T>
PairTree<T>::PairTree(const PairTree& other)
    : _halfs(other._halfs),
      _last(other._last),
      _size(other._size)
{}

template <typename T>
PairTree<T>& PairTree<T>::operator=(PairTree other)
{
	swap(other);
	return *this;
}

template <typename T>
PairTree<T>::~PairTree()
{}

template <typename T>
bool PairTree<T>::operator<(const PairTree& other) const
{
	return *_last < *other._last;
}

template <typename T>
void PairTree<T>::insert(std::list<PairTree>& src_lst, iterator node)
{
	if (*this < *node) {
		swap(*node);
	}
	_halfs.splice(_halfs.begin(), src_lst, node);
	_size *= 2;
}

template <typename T>
void PairTree<T>::split(std::list<PairTree>& dest_lst, iterator dest_pos)
{
	dest_lst.splice(dest_pos, _halfs, _halfs.begin());
	_size /= 2;
}

template <typename T>
void PairTree<T>::swap(PairTree& other)
{
	using std::swap;
	swap(_halfs, other._halfs);
	swap(_last, other._last);
	swap(_size, other._size);
}

template <typename T>
typename PairTree<T>::const_reference PairTree<T>::first() const
{
	const PairTree* node = this;
	while (!node->_halfs.empty()) {
		node = &node->_halfs.front();
	}
	return node->_last;
}

template <typename T>
typename PairTree<T>::const_reference PairTree<T>::last() const throw()
{
	return _last;
}

template <typename T>
typename PairTree<T>::size_type PairTree<T>::size() const throw()
{
	return _size;
}
