#pragma once

#include "GroupIteratorBase.hpp"
#include "libftpp/iterator.hpp"
#include <cassert>
#include <iterator>

namespace detail_group_iterator {

template <typename ForwardIt, typename Derived>
Derived GroupIteratorBase<ForwardIt, Derived, std::forward_iterator_tag>::end(
    ForwardIt first,
    ForwardIt last,
    difference_type group_size)
{
	assert(group_size > 0);
	if (group_size == 1) {
		return Derived(last, group_size);
	}
	ForwardIt end = first;
	while (end != last) {
		const ForwardIt tmp = ft::next(end, group_size, last);
		if (tmp == last && std::distance(end, tmp) != group_size) {
			break;
		}
		end = tmp;
	}
	return Derived(end, group_size);
}

template <typename ForwardIt, typename Derived>
GroupIteratorBase<ForwardIt, Derived, std::forward_iterator_tag>::
    GroupIteratorBase()
    : _base(),
      _size()
{}

template <typename ForwardIt, typename Derived>
GroupIteratorBase<ForwardIt, Derived, std::forward_iterator_tag>::
    GroupIteratorBase(ForwardIt it, difference_type group_size)
    : _base(it),
      _size(group_size)
{
	assert(_size > 0);
}

template <typename ForwardIt, typename Derived>
GroupIteratorBase<ForwardIt, Derived, std::forward_iterator_tag>::
    GroupIteratorBase(const GroupIteratorBase& other)
    : _base(other._base),
      _size(other._size)
{}

template <typename ForwardIt, typename Derived>
GroupIteratorBase<ForwardIt, Derived, std::forward_iterator_tag>&
GroupIteratorBase<ForwardIt, Derived, std::forward_iterator_tag>::operator=(
    const GroupIteratorBase& other)
{
	if (&other == this) {
		return *this;
	}
	_base = other._base;
	_size = other._size;
	return *this;
}

template <typename ForwardIt, typename Derived>
GroupIteratorBase<ForwardIt, Derived, std::forward_iterator_tag>::
    ~GroupIteratorBase()
{}

template <typename ForwardIt, typename Derived>
typename GroupIteratorBase<ForwardIt,
                           Derived,
                           std::forward_iterator_tag>::reference
GroupIteratorBase<ForwardIt, Derived, std::forward_iterator_tag>::operator*()
    const
{
	return *ft::next(_base, _size - 1);
}

template <typename ForwardIt, typename Derived>
typename GroupIteratorBase<ForwardIt,
                           Derived,
                           std::forward_iterator_tag>::pointer
GroupIteratorBase<ForwardIt, Derived, std::forward_iterator_tag>::operator->()
    const
{
	return &(**this);
}

template <typename ForwardIt, typename Derived>
Derived&
GroupIteratorBase<ForwardIt, Derived, std::forward_iterator_tag>::operator++()
{
	std::advance(_base, _size);
	return static_cast<Derived&>(*this);
}

template <typename ForwardIt, typename Derived>
Derived
GroupIteratorBase<ForwardIt, Derived, std::forward_iterator_tag>::operator++(
    int)
{
	Derived tmp = static_cast<Derived&>(*this);
	++(*this);
	return tmp;
}

template <typename ForwardIt, typename Derived>
typename GroupIteratorBase<ForwardIt,
                           Derived,
                           std::forward_iterator_tag>::iterator
GroupIteratorBase<ForwardIt, Derived, std::forward_iterator_tag>::begin() const
{
	return _base;
}

template <typename ForwardIt, typename Derived>
typename GroupIteratorBase<ForwardIt,
                           Derived,
                           std::forward_iterator_tag>::iterator
GroupIteratorBase<ForwardIt, Derived, std::forward_iterator_tag>::middle() const
{
	return ft::next(_base, _size / 2);
}

template <typename ForwardIt, typename Derived>
typename GroupIteratorBase<ForwardIt,
                           Derived,
                           std::forward_iterator_tag>::iterator
GroupIteratorBase<ForwardIt, Derived, std::forward_iterator_tag>::end() const
{
	return ft::next(_base, _size);
}

template <typename ForwardIt, typename Derived>
const ForwardIt&
GroupIteratorBase<ForwardIt, Derived, std::forward_iterator_tag>::base() const
    throw()
{
	return _base;
}

template <typename ForwardIt, typename Derived>
typename GroupIteratorBase<ForwardIt,
                           Derived,
                           std::forward_iterator_tag>::difference_type
GroupIteratorBase<ForwardIt, Derived, std::forward_iterator_tag>::size() const
    throw()
{
	return _size;
}
} // namespace detail_group_iterator
