#pragma once

#include "GroupIterator.hpp"
#include "libftpp/iterator.hpp"
#include "libftpp/type_traits.hpp"
#include <algorithm>
#include <cassert>
#include <iterator>

// =============================================================================
// GroupIterator
// =============================================================================

template <typename ForwardIt>
GroupIterator<ForwardIt>::GroupIterator()
    : Base_()
{}

template <typename ForwardIt>
GroupIterator<ForwardIt>::GroupIterator(ForwardIt it,
                                        difference_type group_size)
    : Base_(it, group_size)
{}

template <typename ForwardIt>
GroupIterator<ForwardIt>::GroupIterator(const GroupIterator& other)
    : Base_(other)
{}

template <typename ForwardIt>
GroupIterator<ForwardIt>&
GroupIterator<ForwardIt>::operator=(const GroupIterator& other)
{
	Base_::operator=(other);
	return *this;
}

template <typename ForwardIt>
GroupIterator<ForwardIt>::~GroupIterator()
{}

namespace detail_group_iterator {

// =============================================================================
// GroupIteratorBase (Forward+ Iterators)
// =============================================================================

template <typename ForwardIt>
GroupIterator<ForwardIt>
GroupIteratorBase<ForwardIt, std::forward_iterator_tag>::end(
    ForwardIt first,
    ForwardIt last,
    difference_type group_size)
{
	assert(group_size > 0);
	if (group_size == 1) {
		return GroupIterator<ForwardIt>(last, group_size);
	}
	ForwardIt end = first;
	while (end != last) {
		const ForwardIt tmp = ft::next(end, group_size, last);
		if (tmp == last && std::distance(end, tmp) != group_size) {
			break;
		}
		end = tmp;
	}
	return GroupIterator<ForwardIt>(end, group_size);
}

template <typename ForwardIt>
GroupIteratorBase<ForwardIt, std::forward_iterator_tag>::GroupIteratorBase()
    : _base(),
      _size()
{}

template <typename ForwardIt>
GroupIteratorBase<ForwardIt, std::forward_iterator_tag>::GroupIteratorBase(
    ForwardIt it,
    difference_type group_size)
    : _base(it),
      _size(group_size)
{
	assert(_size > 0);
}

template <typename ForwardIt>
GroupIteratorBase<ForwardIt, std::forward_iterator_tag>::GroupIteratorBase(
    const GroupIteratorBase& other)
    : _base(other._base),
      _size(other._size)
{}

template <typename ForwardIt>
GroupIteratorBase<ForwardIt, std::forward_iterator_tag>&
GroupIteratorBase<ForwardIt, std::forward_iterator_tag>::operator=(
    const GroupIteratorBase& other)
{
	if (&other == this) {
		return *this;
	}
	_base = other._base;
	_size = other._size;
	return *this;
}

template <typename ForwardIt>
GroupIteratorBase<ForwardIt, std::forward_iterator_tag>::~GroupIteratorBase()
{}

template <typename ForwardIt>
typename GroupIteratorBase<ForwardIt, std::forward_iterator_tag>::reference
GroupIteratorBase<ForwardIt, std::forward_iterator_tag>::operator*() const
{
	return *ft::next(_base, _size - 1);
}

template <typename ForwardIt>
typename GroupIteratorBase<ForwardIt, std::forward_iterator_tag>::pointer
GroupIteratorBase<ForwardIt, std::forward_iterator_tag>::operator->() const
{
	return &(**this);
}

template <typename ForwardIt>
GroupIterator<ForwardIt>&
GroupIteratorBase<ForwardIt, std::forward_iterator_tag>::operator++()
{
	std::advance(_base, _size);
	return static_cast<GroupIterator<ForwardIt>&>(*this);
}

template <typename ForwardIt>
GroupIterator<ForwardIt>
GroupIteratorBase<ForwardIt, std::forward_iterator_tag>::operator++(int)
{
	GroupIterator<ForwardIt> tmp =
	    static_cast<GroupIterator<ForwardIt>&>(*this);
	++(*this);
	return tmp;
}

template <typename ForwardIt>
typename GroupIteratorBase<ForwardIt, std::forward_iterator_tag>::iterator
GroupIteratorBase<ForwardIt, std::forward_iterator_tag>::begin() const
{
	return _base;
}

template <typename ForwardIt>
typename GroupIteratorBase<ForwardIt, std::forward_iterator_tag>::iterator
GroupIteratorBase<ForwardIt, std::forward_iterator_tag>::middle() const
{
	return ft::next(_base, _size / 2);
}

template <typename ForwardIt>
typename GroupIteratorBase<ForwardIt, std::forward_iterator_tag>::iterator
GroupIteratorBase<ForwardIt, std::forward_iterator_tag>::end() const
{
	return ft::next(_base, _size);
}

template <typename ForwardIt>
const ForwardIt&
GroupIteratorBase<ForwardIt, std::forward_iterator_tag>::base() const throw()
{
	return _base;
}

template <typename ForwardIt>
typename GroupIteratorBase<ForwardIt,
                           std::forward_iterator_tag>::difference_type
GroupIteratorBase<ForwardIt, std::forward_iterator_tag>::size() const throw()
{
	return _size;
}

// =============================================================================
// GroupIteratorBase (Bidirectional+ Iterators)
// =============================================================================

template <typename BidirIt>
GroupIterator<BidirIt>
GroupIteratorBase<BidirIt, std::bidirectional_iterator_tag>::end(
    BidirIt first,
    BidirIt last,
    difference_type group_size)
{
	assert(group_size > 0);
	if (group_size == 1) {
		return GroupIterator<BidirIt>(last, group_size);
	}
	const difference_type dist = std::distance(first, last);
	return GroupIterator<BidirIt>(ft::prev(last, dist % group_size),
	                              group_size);
}

template <typename BidirIt>
GroupIteratorBase<BidirIt, std::bidirectional_iterator_tag>::GroupIteratorBase()
    : Base_()
{}

template <typename BidirIt>
GroupIteratorBase<BidirIt, std::bidirectional_iterator_tag>::GroupIteratorBase(
    BidirIt it,
    difference_type group_size)
    : Base_(it, group_size)
{}

template <typename BidirIt>
GroupIteratorBase<BidirIt, std::bidirectional_iterator_tag>::GroupIteratorBase(
    const GroupIteratorBase& other)
    : Base_(other)
{}

template <typename BidirIt>
GroupIteratorBase<BidirIt, std::bidirectional_iterator_tag>&
GroupIteratorBase<BidirIt, std::bidirectional_iterator_tag>::operator=(
    const GroupIteratorBase& other)
{
	Base_::operator=(other);
	return *this;
}

template <typename BidirIt>
GroupIteratorBase<BidirIt,
                  std::bidirectional_iterator_tag>::~GroupIteratorBase()
{}

template <typename BidirIt>
GroupIterator<BidirIt>&
GroupIteratorBase<BidirIt, std::bidirectional_iterator_tag>::operator--()
{
	std::advance(this->_base, -this->_size);
	return static_cast<GroupIterator<BidirIt>&>(*this);
}

template <typename BidirIt>
GroupIterator<BidirIt>
GroupIteratorBase<BidirIt, std::bidirectional_iterator_tag>::operator--(int)
{
	GroupIterator<BidirIt> tmp = static_cast<GroupIterator<BidirIt>&>(*this);
	--(*this);
	return tmp;
}

// =============================================================================
// GroupIteratorBase (Random Access Iterators)
// =============================================================================

template <typename RandomIt>
GroupIteratorBase<RandomIt,
                  std::random_access_iterator_tag>::GroupIteratorBase()
    : Base_()
{}

template <typename RandomIt>
GroupIteratorBase<RandomIt, std::random_access_iterator_tag>::GroupIteratorBase(
    RandomIt it,
    difference_type group_size)
    : Base_(it, group_size)
{}

template <typename RandomIt>
GroupIteratorBase<RandomIt, std::random_access_iterator_tag>::GroupIteratorBase(
    const GroupIteratorBase& other)
    : Base_(other)
{}

template <typename RandomIt>
GroupIteratorBase<RandomIt, std::random_access_iterator_tag>&
GroupIteratorBase<RandomIt, std::random_access_iterator_tag>::operator=(
    const GroupIteratorBase& other)
{
	Base_::operator=(other);
	return *this;
}

template <typename RandomIt>
GroupIteratorBase<RandomIt,
                  std::random_access_iterator_tag>::~GroupIteratorBase()
{}

template <typename RandomIt>
GroupIterator<RandomIt>&
GroupIteratorBase<RandomIt, std::random_access_iterator_tag>::operator+=(
    difference_type n)
{
	this->_base += n * this->_size;
	return static_cast<GroupIterator<RandomIt>&>(*this);
}

template <typename RandomIt>
GroupIterator<RandomIt>&
GroupIteratorBase<RandomIt, std::random_access_iterator_tag>::operator-=(
    difference_type n)
{
	this->_base -= n * this->_size;
	return static_cast<GroupIterator<RandomIt>&>(*this);
}

template <typename RandomIt>
typename GroupIteratorBase<RandomIt, std::random_access_iterator_tag>::reference
GroupIteratorBase<RandomIt, std::random_access_iterator_tag>::operator[](
    difference_type n) const
{
	return this->_base[n * this->_size];
}

} // namespace detail_group_iterator

// =============================================================================
// Non-member Functions (Forward+ Iterators)
// =============================================================================

template <typename ForwardIt1, typename ForwardIt2>
bool operator==(const GroupIterator<ForwardIt1>& lhs,
                const GroupIterator<ForwardIt2>& rhs)
{
	return lhs.base() == rhs.base();
}

template <typename ForwardIt1, typename ForwardIt2>
bool operator!=(const GroupIterator<ForwardIt1>& lhs,
                const GroupIterator<ForwardIt2>& rhs)
{
	return !(lhs == rhs);
}

template <typename ForwardIt1, typename ForwardIt2>
void iter_swap(GroupIterator<ForwardIt1> lhs, GroupIterator<ForwardIt2> rhs)
{
	std::swap_ranges(lhs.begin(), lhs.end(), rhs.begin());
}

// =============================================================================
// Non-member Functions (Random Access Iterators)
// =============================================================================

template <typename RandomIt1, typename RandomIt2>
REQUIRES(ft::is_random_access_iterator<RandomIt1>::value and
             ft::is_random_access_iterator<RandomIt2>::value)
(bool)operator<(const GroupIterator<RandomIt1>& lhs,
                const GroupIterator<RandomIt2>& rhs)
{
	return (rhs - lhs) > 0;
}

template <typename RandomIt1, typename RandomIt2>
REQUIRES(ft::is_random_access_iterator<RandomIt1>::value and
             ft::is_random_access_iterator<RandomIt2>::value)
(bool)operator>(const GroupIterator<RandomIt1>& lhs,
                const GroupIterator<RandomIt2>& rhs)
{
	return rhs < lhs;
}

template <typename RandomIt1, typename RandomIt2>
REQUIRES(ft::is_random_access_iterator<RandomIt1>::value and
             ft::is_random_access_iterator<RandomIt2>::value)
(bool)operator<=(const GroupIterator<RandomIt1>& lhs,
                 const GroupIterator<RandomIt2>& rhs)
{
	return !(lhs > rhs);
}

template <typename RandomIt1, typename RandomIt2>
REQUIRES(ft::is_random_access_iterator<RandomIt1>::value and
             ft::is_random_access_iterator<RandomIt2>::value)
(bool)operator>=(const GroupIterator<RandomIt1>& lhs,
                 const GroupIterator<RandomIt2>& rhs)
{
	return !(lhs < rhs);
}

/* Difference between two iterators */
template <typename RandomIt1, typename RandomIt2>
REQUIRES(ft::is_random_access_iterator<RandomIt1>::value and
             ft::is_random_access_iterator<RandomIt2>::value)
(typename GroupIterator<RandomIt1>::difference_type) operator-(
    const GroupIterator<RandomIt1>& lhs,
    const GroupIterator<RandomIt2>& rhs)
{
	return (lhs.base() - rhs.base()) / rhs.size();
}

/* Arithmetic with difference_type n */

template <typename RandomIt>
REQUIRES(ft::is_random_access_iterator<RandomIt>::value)
(GroupIterator<RandomIt>)operator+(
    GroupIterator<RandomIt> it,
    typename GroupIterator<RandomIt>::difference_type n)
{
	return it += n;
}

template <typename RandomIt>
REQUIRES(ft::is_random_access_iterator<RandomIt>::value)
(GroupIterator<RandomIt>)operator+(
    typename GroupIterator<RandomIt>::difference_type n,
    GroupIterator<RandomIt> it)
{
	return it += n;
}

template <typename RandomIt>
REQUIRES(ft::is_random_access_iterator<RandomIt>::value)
(GroupIterator<RandomIt>)operator-(
    GroupIterator<RandomIt> it,
    typename GroupIterator<RandomIt>::difference_type n)
{
	return it -= n;
}
