#pragma once

#include "libftpp/iterator.hpp"
#include "libftpp/type_traits.hpp"
#include <iterator>

namespace detail_group_iterator {
template <typename ForwardIt, typename Tag>
class GroupIteratorBase;
} // namespace detail_group_iterator

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
 */
template <typename ForwardIt>
class GroupIterator
    : public detail_group_iterator::GroupIteratorBase<
          ForwardIt,
          typename std::iterator_traits<ForwardIt>::iterator_category> {
	typedef detail_group_iterator::GroupIteratorBase<
	    ForwardIt,
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

namespace detail_group_iterator {

template <typename ForwardIt>
class GroupIteratorBase<ForwardIt, std::forward_iterator_tag> {
public:
	typedef ForwardIt iterator;
	typedef typename std::iterator_traits<ForwardIt>::iterator_category
	    iterator_category;
	typedef typename std::iterator_traits<ForwardIt>::value_type value_type;
	typedef typename std::iterator_traits<ForwardIt>::difference_type
	    difference_type;
	typedef typename std::iterator_traits<ForwardIt>::pointer pointer;
	typedef typename std::iterator_traits<ForwardIt>::reference reference;

	static GroupIterator<ForwardIt>
	end(ForwardIt first, ForwardIt last, difference_type group_size);

	GroupIteratorBase();
	GroupIteratorBase(ForwardIt it, difference_type group_size);
	GroupIteratorBase(const GroupIteratorBase& other);
	GroupIteratorBase& operator=(const GroupIteratorBase& other);
	~GroupIteratorBase();

	/* Accesses the last element in the group. */
	reference operator*() const;
	pointer operator->() const;
	GroupIterator<ForwardIt>& operator++();
	GroupIterator<ForwardIt> operator++(int);

	/* Range access within the group */
	iterator begin() const;
	iterator middle() const;
	iterator end() const;

	const ForwardIt& base() const throw();
	difference_type size() const throw();

protected:
	/* Data shared by all iterator categories */
	// NOLINTBEGIN(misc-non-private-member-variables-in-classes)
	ForwardIt _base;
	difference_type _size;
	// NOLINTEND(misc-non-private-member-variables-in-classes)
};

template <typename BidirIt>
class GroupIteratorBase<BidirIt, std::bidirectional_iterator_tag>
    : public GroupIteratorBase<BidirIt, std::forward_iterator_tag> {
	typedef detail_group_iterator::GroupIteratorBase<BidirIt,
	                                                 std::forward_iterator_tag>
	    Base_;

public:
	typedef typename Base_::difference_type difference_type;

	/* Compute an aligned end GroupIterator with the given group size. */
	static GroupIterator<BidirIt>
	end(BidirIt first, BidirIt last, difference_type group_size);
	using Base_::end; // Needed to also find overload in base class.

	GroupIteratorBase();
	GroupIteratorBase(BidirIt it, difference_type group_size);
	GroupIteratorBase(const GroupIteratorBase& other);
	GroupIteratorBase& operator=(const GroupIteratorBase& other);
	~GroupIteratorBase();

	GroupIterator<BidirIt>& operator--();
	GroupIterator<BidirIt> operator--(int);
};

template <typename RandomIt>
class GroupIteratorBase<RandomIt, std::random_access_iterator_tag>
    : public GroupIteratorBase<RandomIt, std::bidirectional_iterator_tag> {
	typedef detail_group_iterator::
	    GroupIteratorBase<RandomIt, std::bidirectional_iterator_tag>
	        Base_;

public:
	typedef typename Base_::difference_type difference_type;
	typedef typename Base_::reference reference;

	GroupIteratorBase();
	GroupIteratorBase(RandomIt it, difference_type group_size);
	GroupIteratorBase(const GroupIteratorBase& other);
	GroupIteratorBase& operator=(const GroupIteratorBase& other);
	~GroupIteratorBase();

	GroupIterator<RandomIt>& operator+=(difference_type n);
	GroupIterator<RandomIt>& operator-=(difference_type n);
	reference operator[](difference_type n) const;
};

} // namespace detail_group_iterator

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
