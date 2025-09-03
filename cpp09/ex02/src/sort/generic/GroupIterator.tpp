#pragma once

#include "GroupIterator.hpp"
#include "libftpp/iterator.hpp"
#include "libftpp/type_traits.hpp"
#include <algorithm>

/* Member functions */

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

/* Non-member functions (Forward+ iterators) */

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

/* Non-member functions (Random access iterators) */

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
