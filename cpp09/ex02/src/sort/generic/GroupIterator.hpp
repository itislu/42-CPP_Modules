#pragma once

#include "GroupIteratorBase/GroupIteratorBase.hpp"
#include "libftpp/iterator.hpp"
#include "libftpp/type_traits.hpp"
#include <iterator>

/**
 * @brief An iterator adapter that groups elements from an underlying iterator
 *
 * `GroupIterator` advances by the group size it was constructed with at each
 * step.
 * Dereferencing the iterator provides access to the last element in the current
 * group.
 *
 * `GroupIterator` matches the iterator category of the iterator given as
 * template argument, including all operations to satisfy its requirements.
 *
 * @tparam ForwardIt The underlying iterator type. Must be a forward iterator or
 * stronger
 *
 * Inspiration:
 * https://github.com/Morwenn/cpp-sort/blob/1.x.y-stable/include/cpp-sort/detail/merge_insertion_sort.h
 */
template <typename ForwardIt>
class GroupIterator
    : public detail_group_iterator::GroupIteratorBase<
          ForwardIt,
          GroupIterator<ForwardIt>,
          typename std::iterator_traits<ForwardIt>::iterator_category> {
	typedef detail_group_iterator::GroupIteratorBase<
	    ForwardIt,
	    GroupIterator<ForwardIt>,
	    typename std::iterator_traits<ForwardIt>::iterator_category>
	    Base_;

public:
	typedef typename Base_::iterator iterator;
	typedef typename Base_::iterator_category iterator_category;
	typedef typename Base_::value_type value_type;
	typedef typename Base_::difference_type difference_type;
	typedef typename Base_::pointer pointer;
	typedef typename Base_::reference reference;

	GroupIterator();
	GroupIterator(ForwardIt it, difference_type group_size);
	GroupIterator(const GroupIterator& other);
	GroupIterator& operator=(const GroupIterator& other);
	~GroupIterator();
};

template <typename ForwardIt1, typename ForwardIt2>
bool operator==(const GroupIterator<ForwardIt1>& lhs,
                const GroupIterator<ForwardIt2>& rhs);

template <typename ForwardIt1, typename ForwardIt2>
bool operator!=(const GroupIterator<ForwardIt1>& lhs,
                const GroupIterator<ForwardIt2>& rhs);

template <typename ForwardIt1, typename ForwardIt2>
void iter_swap(GroupIterator<ForwardIt1> lhs, GroupIterator<ForwardIt2> rhs);

/* Random access operators */

template <typename RandomIt1, typename RandomIt2>
REQUIRES(ft::is_random_access_iterator<RandomIt1>::value and
             ft::is_random_access_iterator<RandomIt2>::value)
(bool)operator<(const GroupIterator<RandomIt1>& lhs,
                const GroupIterator<RandomIt2>& rhs);

template <typename RandomIt1, typename RandomIt2>
REQUIRES(ft::is_random_access_iterator<RandomIt1>::value and
             ft::is_random_access_iterator<RandomIt2>::value)
(bool)operator>(const GroupIterator<RandomIt1>& lhs,
                const GroupIterator<RandomIt2>& rhs);

template <typename RandomIt1, typename RandomIt2>
REQUIRES(ft::is_random_access_iterator<RandomIt1>::value and
             ft::is_random_access_iterator<RandomIt2>::value)
(bool)operator<=(const GroupIterator<RandomIt1>& lhs,
                 const GroupIterator<RandomIt2>& rhs);

template <typename RandomIt1, typename RandomIt2>
REQUIRES(ft::is_random_access_iterator<RandomIt1>::value and
             ft::is_random_access_iterator<RandomIt2>::value)
(bool)operator>=(const GroupIterator<RandomIt1>& lhs,
                 const GroupIterator<RandomIt2>& rhs);

template <typename RandomIt1, typename RandomIt2>
REQUIRES(ft::is_random_access_iterator<RandomIt1>::value and
             ft::is_random_access_iterator<RandomIt2>::value)
(typename GroupIterator<RandomIt1>::difference_type) operator-(
    const GroupIterator<RandomIt1>& lhs,
    const GroupIterator<RandomIt2>& rhs);

template <typename RandomIt>
REQUIRES(ft::is_random_access_iterator<RandomIt>::value)
(GroupIterator<RandomIt>)operator+(
    GroupIterator<RandomIt> it,
    typename GroupIterator<RandomIt>::difference_type n);

template <typename RandomIt>
REQUIRES(ft::is_random_access_iterator<RandomIt>::value)
(GroupIterator<RandomIt>)operator+(
    typename GroupIterator<RandomIt>::difference_type n,
    GroupIterator<RandomIt> it);

template <typename RandomIt>
REQUIRES(ft::is_random_access_iterator<RandomIt>::value)
(GroupIterator<RandomIt>)operator-(
    GroupIterator<RandomIt> it,
    typename GroupIterator<RandomIt>::difference_type n);

#include "GroupIterator.tpp" // IWYU pragma: export
