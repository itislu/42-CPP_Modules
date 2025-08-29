#pragma once

#include "MergeInsertionList.hpp"
#include "libftpp/Exception.hpp"
#include "libftpp/SourceLocation.hpp"
#include "libftpp/algorithm.hpp"
#include "libftpp/iterator.hpp"
#include "libftpp/string.hpp"
#include "libftpp/type_traits.hpp"
#include <algorithm>
#include <list>
#include <memory>

/* MergeInsertionList<T> */

/**
 * In a single iteration over the given list create "runs" of size two.
 * These small runs are then iteratively merged into larger runs whose sizes
 * double (4, 8, 16, etc). The runs are sorted always by their last element.
 */
template <typename T>
MergeInsertionList<T>::MergeInsertionList(std::auto_ptr<std::list<T> > lst)
    : _base_list(lst),
      _runs(),
      _end(_runs.end()),
      _skip_size(1)
{
	std::list<Run_> stash; // Splice-stash to avoid making copies of T.
	size_type i = 0;
	for (BaseListIterator_ it = _base_list->begin(), end = _base_list->end();
	     it != end;
	     ++i) {
		// BaseListIterator_ r_begin = it++;
		// if (i % 2 == 0) {
		// 	continue;
		// }
		// BaseListIterator_ l_begin =
		//     _runs.empty() ? _base_list->begin() :
		//     ft::next(_runs.front().last());
		// _sort_pair(l_begin, r_begin);

		stash.push_front(Run_(it++));
		Run_& run = stash.front();
		//  2:               LR
		//  4:             .L.R
		//  8:         .l.L.r.R
		// 16: ...l...L...r...R
		// 16: .......r.......R
		// L = _runs, R = run
		// l = pushed in previous run, r = pushed in this run
		for (size_type run_size = 2; (i + 1) % run_size == 0; run_size *= 2) {
			stash.splice(stash.begin(), _runs, _runs.begin());
			BaseListIterator_ l_begin = _runs.empty()
			                                ? _base_list->begin()
			                                : ft::next(_runs.front().last());
			stash.front().sort_pair(run, l_begin, *_base_list);
			run.grow(stash);
		}
		_runs.splice(_runs.begin(), stash);
	}

	if (!_runs.empty()) {
		_runs.reverse(); // Move leftovers to the back in decreasing size.
		_skip_size = _runs.front().size();
		_end = ft::next(_runs.begin());
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

	for (RunsIterator_ it = _runs.begin(); it != _end; ++it) {
		it->split(_runs, it);
	}
	_skip_size /= 2;
	// Check for leftover without pair
	if (_end != _runs.end() && _end->size() == _skip_size) {
		++_end;
	}
}

// TODO Don't return bool, but outside use while skip_size() != 1.
template <typename T>
bool MergeInsertionList<T>::sort()
{
	if (_skip_size == 1) {
		return true;
	}

	for (std::list<Run_> pend_stack; _skip_size > 1;) {
		size_type search_size = 0;
		size_type max_search_size = 1;
		RunsIterator_ it = _runs.begin();

		// First node is known to be lowest.
		it->split(_runs, it);
		++search_size;

		while (it != _end) {
			// Amount of comparisons in binary insertion is same for 2^n and
			// 2^(n+1)-1.
			max_search_size =
			    ((max_search_size + 1) * 2) - 1; // 3, 7, 15, 31, ...
			// Move lower of the pairs into pend_stack to allow for binary
			// insertion in the range up to max_search_size.
			while (search_size < max_search_size) {
				++it, ++search_size;
				if (it == _end) {
					_skip_size /= 2;
					// Check for leftover without a pair.
					if (it != _runs.end() && it->size() == _skip_size) {
						pend_stack.splice(pend_stack.begin(), _runs, it++);
						_end = it;
					}
					break;
				}
				it->split(pend_stack, pend_stack.begin());
			}

			// Binary insertion.
			const size_type search_size_after = search_size + pend_stack.size();
			for (RunsIterator_ search_end = it; !pend_stack.empty();) {
				const RunsIterator_ insert_pos = ft::lower_bound(
				    _runs.begin(), search_size, pend_stack.front());
				// Search size normally stays constant (max_search_size) bc of
				// the partial order achieved by the pairwise sorting in the
				// beginning of the algorithm and bc the pend_stack elements get
				// inserted in decreasing order.
				// But if the new element gets inserted after the next
				// pend_stack's higher pair, that higher pair will be two
				// elements apart from the current pend_stack's higher pair.
				if (insert_pos == search_end) {
					--search_size;
				}
				--search_end;
				_runs.splice(insert_pos, pend_stack, pend_stack.begin());
			}
			search_size = search_size_after;
		}
	}
	return _skip_size == 1;
}

template <typename T>
std::auto_ptr<std::list<T> > MergeInsertionList<T>::release()
{
	BaseListIterator_ insert_pos = _base_list->begin();
	for (RunsIterator_ run = _runs.begin(); run != _runs.end(); ++run) {
		BaseListIterator_ first = run->first();
		BaseListIterator_ last = run->last();
		if (first == insert_pos) {
			insert_pos = ++last;
			continue;
		}
		_base_list->splice(insert_pos, *_base_list, first, ++last);
	}

	_runs.clear();
	_end = _runs.end();
	_skip_size = 1;
	return _base_list;
}

template <typename T>
typename MergeInsertionList<T>::iterator MergeInsertionList<T>::begin()
{
	return iterator(_runs.begin());
}

template <typename T>
typename MergeInsertionList<T>::const_iterator
MergeInsertionList<T>::begin() const
{
	return const_iterator(_runs.begin());
}

template <typename T>
typename MergeInsertionList<T>::iterator MergeInsertionList<T>::end()
{
	return iterator(_end);
}

template <typename T>
typename MergeInsertionList<T>::const_iterator
MergeInsertionList<T>::end() const
{
	return const_iterator(_end);
}

template <typename T>
void MergeInsertionList<T>::_sort_pair(BaseListIterator_ left,
                                       BaseListIterator_ right)
{
	if (!(*left < *right)) {
		_base_list->splice(left, *_base_list, right);
	}
}

/* MergeInsertionList<T>::Run_ */

template <typename T>
MergeInsertionList<T>::Run_::Run_(BaseListIterator_ pos)
    : _last(pos),
      _size(1)
{}

template <typename T>
MergeInsertionList<T>::Run_::operator T&()
{
	return *_last;
}

template <typename T>
MergeInsertionList<T>::Run_::operator const T&() const
{
	return *_last;
}

template <typename T>
bool MergeInsertionList<T>::Run_::operator<(const Run_& other) const
{
	return *_last < *other._last;
}

template <typename T>
void MergeInsertionList<T>::Run_::grow(std::list<Run_>& node)
{
	_halfs.splice(_halfs.begin(), node, node.begin());
	_size *= 2;
}

template <typename T>
void MergeInsertionList<T>::Run_::split(std::list<Run_>& target_lst,
                                        RunsIterator_ target_pos)
{
	target_lst.splice(target_pos, _halfs, _halfs.begin());
	_size /= 2;
}

template <typename T>
void MergeInsertionList<T>::Run_::sort_pair(Run_& other,
                                            BaseListIterator_ begin,
                                            std::list<T>& lst)
{
	if (!(*_last < *other._last)) {
		lst.splice(begin, lst, ft::next(_last), ft::next(other._last));
		swap(other);
	}
}

template <typename T>
void MergeInsertionList<T>::Run_::swap(Run_& other)
{
	using std::swap;
	swap(_halfs, other._halfs);
	swap(_last, other._last);
	swap(_size, other._size);
}

template <typename T>
typename MergeInsertionList<T>::BaseListIterator_
MergeInsertionList<T>::Run_::last() const
{
	return _last;
}

template <typename T>
typename MergeInsertionList<T>::BaseListIterator_
MergeInsertionList<T>::Run_::first() const
{
	const Run_* run = this;
	while (!run->_halfs.empty()) {
		run = &run->_halfs.front();
	}
	return run->_last;
}

template <typename T>
typename std::list<T>::size_type MergeInsertionList<T>::Run_::size() const
    throw()
{
	return _size;
}

/* MergeInsertionList<T>::Iterator_ */

template <typename T>
template <bool is_const>
MergeInsertionList<T>::Iterator_<is_const>::Iterator_()
    : _it()
{}

template <typename T>
template <bool is_const>
MergeInsertionList<T>::Iterator_<is_const>::Iterator_(BaseIterator_ it)
    : _it(it)
{}

template <typename T>
template <bool is_const>
template <bool other_is_const>
MergeInsertionList<T>::Iterator_<is_const>::Iterator_(
    typename ft::enable_if<is_const && !other_is_const,
                           const Iterator_<other_is_const>&>::type other)
    : _it(other.base())
{}

template <typename T>
template <bool is_const>
typename MergeInsertionList<T>::template Iterator_<is_const>::BaseIterator_
MergeInsertionList<T>::Iterator_<is_const>::base() const
{
	return _it;
}

template <typename T>
template <bool is_const>
typename MergeInsertionList<T>::template Iterator_<is_const>::reference
MergeInsertionList<T>::Iterator_<is_const>::operator*() const
{
	return static_cast<reference>(*_it);
}

template <typename T>
template <bool is_const>
typename MergeInsertionList<T>::template Iterator_<is_const>::pointer
MergeInsertionList<T>::Iterator_<is_const>::operator->() const
{
	return &static_cast<reference>(*_it);
}

template <typename T>
template <bool is_const>
typename MergeInsertionList<T>::template Iterator_<is_const>&
MergeInsertionList<T>::Iterator_<is_const>::operator++()
{
	++_it;
	return *this;
}

template <typename T>
template <bool is_const>
typename MergeInsertionList<T>::template Iterator_<is_const>
MergeInsertionList<T>::Iterator_<is_const>::operator++(int)
{
	Iterator_ tmp = *this;
	++(*this);
	return tmp;
}

template <typename T>
template <bool is_const>
typename MergeInsertionList<T>::template Iterator_<is_const>&
MergeInsertionList<T>::Iterator_<is_const>::operator--()
{
	--_it;
	return *this;
}

template <typename T>
template <bool is_const>
typename MergeInsertionList<T>::template Iterator_<is_const>
MergeInsertionList<T>::Iterator_<is_const>::operator--(int)
{
	Iterator_ tmp = *this;
	--(*this);
	return tmp;
}

template <typename T>
template <bool is_const>
template <bool other_is_const>
bool MergeInsertionList<T>::Iterator_<is_const>::operator==(
    const Iterator_<other_is_const>& other) const
{
	return _it == other.base();
}

template <typename T>
template <bool is_const>
template <bool other_is_const>
bool MergeInsertionList<T>::Iterator_<is_const>::operator!=(
    const Iterator_<other_is_const>& other) const
{
	return !(*this == other);
}

/* Old attempt */

#include <stack>

template <typename T>
void sort_pair(std::list<T>& lst,
               typename std::list<T>::iterator* left,
               typename std::list<T>::iterator right)
{
	if (!(**left < *right)) {
		lst.splice(*left, lst, right);
		*left = right;
	}
}

template <typename T>
void sort_pair(std::list<T>& lst,
               typename std::list<T>::iterator* l_begin,
               typename std::list<T>::iterator r_begin,
               typename std::list<T>::iterator r_end)
{
	if (!(*ft::prev(r_begin) < *ft::prev(r_end))) {
		lst.splice(*l_begin, lst, r_begin, r_end);
		*l_begin = r_begin;
	}
}

/**
 * @brief O(N) pair-wise sorting
 */
template <typename T>
void sort_pairwise(std::list<T>& lst)
{
	typedef typename std::list<T>::iterator It;
	typedef typename std::list<T>::size_type Size;

	std::stack<It, std::list<It> > pairs;
	pairs.push(lst.begin());
	Size i = 0;
	for (It it = lst.begin(); it != lst.end(); ++i) {
		++it;
		if (i % 2 == 0) {
			continue;
		}
		It r_end = it;
		It r_begin = ft::prev(r_end);
		It* l_begin = &pairs.top();
		sort_pair(lst, l_begin, r_begin);
		for (Size group_size = 4; (i + 1) % group_size == 0; group_size *= 2) {
			r_begin = pairs.top();
			pairs.pop();
			l_begin = &pairs.top();
			sort_pair(lst, l_begin, r_begin, r_end);
		}
		pairs.push(it);
	}
}
