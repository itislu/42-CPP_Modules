#pragma once

#include "MergeInsertionList.hpp"
#include "libftpp/Exception.hpp"
#include "libftpp/SourceLocation.hpp"
#include "libftpp/iterator.hpp"
#include "libftpp/string.hpp"
#include <list>
#include <memory>

/* MergeInsertionList<T> */

/**
 * In a single iteration over the given list, create "runs" of size two.
 * These small runs are then iteratively merged into larger runs whose sizes
 * double (4, 8, 16, etc). The runs are sorted always by their last element.
 */
template <typename T>
MergeInsertionList<T>::MergeInsertionList(std::auto_ptr<std::list<T> > lst)
    : _lst_base(lst),
      _lst(),
      _end(_lst.end()),
      _skip_size(1)
{
	typedef typename std::list<T>::iterator It;
	typedef typename std::list<T>::size_type Size;

	std::list<Run> stash; // Splice stash to avoid making copies of T.
	Size i = 0;
	for (It it = _lst_base->begin(), end = _lst_base->end(); it != end; ++i) {
		It r_begin = it++;
		if (i % 2 == 0) {
			continue;
		}
		It l_begin =
		    _lst.empty() ? _lst_base->begin() : ft::next(_lst.front().pos());
		_sort_pair(l_begin, r_begin);

		//  4:             .L.R
		//  8:         .l.L.r.R
		// 16: ...l...L...r...R
		// 16: .......r.......R
		// L = _lst, R = run
		// l = saved in previous run, r = moved into run
		stash.push_front(Run(ft::prev(it)));
		Run& run = stash.front();
		for (Size run_size = 4; (i + 1) % run_size == 0; run_size *= 2) {
			stash.splice(stash.begin(), _lst, _lst.begin());
			l_begin = _lst.empty() ? _lst_base->begin()
			                       : ft::next(_lst.front().pos());
			stash.front().sort_pair(run, l_begin, *_lst_base);
			run.grow(stash);
		}
		_lst.splice(_lst.begin(), stash);
	}

	if (!_lst.empty()) {
		_lst.reverse(); // Move leftovers to the back in decreasing size.
		_skip_size = _lst.front().size();
		_end = ft::next(_lst.begin());
	}
}

template <typename T>
MergeInsertionList<T>::~MergeInsertionList()
{}

template <typename T>
void MergeInsertionList<T>::half_skip_size()
{
	// Prevent use as a normal list.
	if (_skip_size <= 2) {
		throw ft::Exception("cannot half skip size of "
		                        + ft::to_string(_skip_size),
		                    SOURCE_LOCATION_CURRENT());
	}

	for (iterator it = begin(); it != _end; ++it) {
		it->split(_lst, it);
	}
	_skip_size /= 2;
	// Check for leftover without pair
	if (_end != _lst.end() && _end->size() == _skip_size) {
		++_end;
	}
}

template <typename T>
typename MergeInsertionList<T>::iterator MergeInsertionList<T>::begin()
{
	return _lst.begin();
}

template <typename T>
typename MergeInsertionList<T>::const_iterator
MergeInsertionList<T>::begin() const
{
	return _lst.begin();
}

template <typename T>
typename MergeInsertionList<T>::iterator MergeInsertionList<T>::end()
{
	return _end;
}

template <typename T>
typename MergeInsertionList<T>::const_iterator
MergeInsertionList<T>::end() const
{
	return _end;
}

/* MergeInsertionList<T>::Run */

template <typename T>
MergeInsertionList<T>::Run::Run(typename std::list<T>::iterator pos)
    : _pos(pos),
      _size(2)
{}

template <typename T>
MergeInsertionList<T>::Run::operator const T&() const
{
	return *_pos;
}

template <typename T>
void MergeInsertionList<T>::Run::grow(std::list<Run>& node)
{
	_halfs.splice(_halfs.begin(), node, node.begin());
	_size *= 2;
}

template <typename T>
void
MergeInsertionList<T>::Run::split(std::list<Run>& lst,
                                  typename std::list<Run>::iterator this_it)
{
	lst.splice(this_it, _halfs, _halfs.begin());
	_size /= 2;
}

template <typename T>
void
MergeInsertionList<T>::Run::sort_pair(Run& other,
                                      typename std::list<T>::iterator begin,
                                      std::list<T>& lst)
{
	if (!(*_pos < *other._pos)) {
		lst.splice(begin, lst, ft::next(_pos), ft::next(other._pos));
		swap(other);
	}
}

template <typename T>
void MergeInsertionList<T>::Run::swap(Run& other)
{
	using std::swap;
	swap(_halfs, other._halfs);
	swap(_pos, other._pos);
	swap(_size, other._size);
}

template <typename T>
typename std::list<T>::iterator& MergeInsertionList<T>::Run::pos() throw()
{
	return _pos;
}

template <typename T>
const typename std::list<T>::iterator& MergeInsertionList<T>::Run::pos() const
    throw()
{
	return _pos;
}

template <typename T>
typename std::list<T>::size_type& MergeInsertionList<T>::Run::size() throw()
{
	return _size;
}

template <typename T>
const typename std::list<T>::size_type& MergeInsertionList<T>::Run::size() const
    throw()
{
	return _size;
}

template <typename T>
void MergeInsertionList<T>::_sort_pair(typename std::list<T>::iterator left,
                                       typename std::list<T>::iterator right)
{
	if (!(*left < *right)) {
		_lst_base->splice(left, *_lst_base, right);
	}
}
