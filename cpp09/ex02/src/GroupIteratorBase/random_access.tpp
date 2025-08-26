#pragma once

#include "GroupIteratorBase.hpp"
#include <iterator>

namespace detail_group_iterator {

template <typename RandomIt, typename Derived>
GroupIteratorBase<RandomIt, Derived, std::random_access_iterator_tag>::
    GroupIteratorBase()
    : Base_()
{}

template <typename RandomIt, typename Derived>
GroupIteratorBase<RandomIt, Derived, std::random_access_iterator_tag>::
    GroupIteratorBase(RandomIt it, difference_type group_size)
    : Base_(it, group_size)
{}

template <typename RandomIt, typename Derived>
GroupIteratorBase<RandomIt, Derived, std::random_access_iterator_tag>::
    GroupIteratorBase(const GroupIteratorBase& other)
    : Base_(other)
{}

template <typename RandomIt, typename Derived>
GroupIteratorBase<RandomIt, Derived, std::random_access_iterator_tag>&
GroupIteratorBase<RandomIt, Derived, std::random_access_iterator_tag>::
operator=(const GroupIteratorBase& other)
{
	Base_::operator=(other);
	return *this;
}

template <typename RandomIt, typename Derived>
GroupIteratorBase<RandomIt, Derived, std::random_access_iterator_tag>::
    ~GroupIteratorBase()
{}

template <typename RandomIt, typename Derived>
Derived& GroupIteratorBase<RandomIt, Derived, std::random_access_iterator_tag>::
operator+=(difference_type n)
{
	this->_base += n * this->_size;
	return static_cast<Derived&>(*this);
}

template <typename RandomIt, typename Derived>
Derived& GroupIteratorBase<RandomIt, Derived, std::random_access_iterator_tag>::
operator-=(difference_type n)
{
	this->_base -= n * this->_size;
	return static_cast<Derived&>(*this);
}

template <typename RandomIt, typename Derived>
typename GroupIteratorBase<RandomIt, Derived, std::random_access_iterator_tag>::
    reference
    GroupIteratorBase<RandomIt, Derived, std::random_access_iterator_tag>::
    operator[](difference_type n) const
{
	return this->_base[n * this->_size];
}

} // namespace detail_group_iterator
