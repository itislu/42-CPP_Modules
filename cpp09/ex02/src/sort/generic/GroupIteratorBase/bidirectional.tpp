#pragma once

#include "GroupIteratorBase.hpp"
#include "libftpp/iterator.hpp"
#include <cassert>
#include <iterator>

namespace detail_group_iterator {

template <typename BidirIt, typename Derived>
Derived
GroupIteratorBase<BidirIt, Derived, std::bidirectional_iterator_tag>::end(
    BidirIt first,
    BidirIt last,
    difference_type group_size)
{
	assert(group_size > 0);
	if (group_size == 1) {
		return Derived(last, group_size);
	}
	const difference_type dist = std::distance(first, last);
	return Derived(ft::prev(last, dist % group_size), group_size);
}

template <typename BidirIt, typename Derived>
GroupIteratorBase<BidirIt, Derived, std::bidirectional_iterator_tag>::
    GroupIteratorBase()
    : Base_()
{}

template <typename BidirIt, typename Derived>
GroupIteratorBase<BidirIt, Derived, std::bidirectional_iterator_tag>::
    GroupIteratorBase(BidirIt it, difference_type group_size)
    : Base_(it, group_size)
{}

template <typename BidirIt, typename Derived>
GroupIteratorBase<BidirIt, Derived, std::bidirectional_iterator_tag>::
    GroupIteratorBase(const GroupIteratorBase& other)
    : Base_(other)
{}

template <typename BidirIt, typename Derived>
GroupIteratorBase<BidirIt, Derived, std::bidirectional_iterator_tag>&
GroupIteratorBase<BidirIt, Derived, std::bidirectional_iterator_tag>::operator=(
    const GroupIteratorBase& other)
{
	Base_::operator=(other);
	return *this;
}

template <typename BidirIt, typename Derived>
GroupIteratorBase<BidirIt, Derived, std::bidirectional_iterator_tag>::
    ~GroupIteratorBase()
{}

template <typename BidirIt, typename Derived>
Derived& GroupIteratorBase<BidirIt, Derived, std::bidirectional_iterator_tag>::
operator--()
{
	std::advance(this->_base, -this->_size);
	return static_cast<Derived&>(*this);
}

template <typename BidirIt, typename Derived>
Derived GroupIteratorBase<BidirIt, Derived, std::bidirectional_iterator_tag>::
operator--(int)
{
	Derived tmp = static_cast<Derived&>(*this);
	--(*this);
	return tmp;
}

} // namespace detail_group_iterator
