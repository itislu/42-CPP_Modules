#pragma once

#include <iterator>

namespace detail_group_iterator {

/* Anything weaker than forward iterator is not specialized. */
template <typename ForwardIt, typename Derived, typename Tag>
class GroupIteratorBase;

template <typename ForwardIt, typename Derived>
class GroupIteratorBase<ForwardIt, Derived, std::forward_iterator_tag> {
public:
	typedef ForwardIt iterator;
	typedef typename std::iterator_traits<ForwardIt>::iterator_category
	    iterator_category;
	typedef typename std::iterator_traits<ForwardIt>::value_type value_type;
	typedef typename std::iterator_traits<ForwardIt>::difference_type
	    difference_type;
	typedef typename std::iterator_traits<ForwardIt>::pointer pointer;
	typedef typename std::iterator_traits<ForwardIt>::reference reference;

	static Derived
	end(ForwardIt first, ForwardIt last, difference_type group_size);

	GroupIteratorBase();
	GroupIteratorBase(ForwardIt it, difference_type group_size);
	GroupIteratorBase(const GroupIteratorBase& other);
	GroupIteratorBase& operator=(const GroupIteratorBase& other);
	~GroupIteratorBase();

	/* Accesses the last element in the group. */
	reference operator*() const;
	pointer operator->() const;
	Derived& operator++();
	Derived operator++(int);

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

template <typename BidirIt, typename Derived>
class GroupIteratorBase<BidirIt, Derived, std::bidirectional_iterator_tag>
    : public GroupIteratorBase<BidirIt, Derived, std::forward_iterator_tag> {
	typedef detail_group_iterator::
	    GroupIteratorBase<BidirIt, Derived, std::forward_iterator_tag>
	        Base_;

public:
	typedef typename Base_::difference_type difference_type;

	/* Compute an aligned end GroupIterator with the given group size. */
	static Derived end(BidirIt first, BidirIt last, difference_type group_size);
	using Base_::end; // Needed to also find overload in base class.

	GroupIteratorBase();
	GroupIteratorBase(BidirIt it, difference_type group_size);
	GroupIteratorBase(const GroupIteratorBase& other);
	GroupIteratorBase& operator=(const GroupIteratorBase& other);
	~GroupIteratorBase();

	Derived& operator--();
	Derived operator--(int);
};

template <typename RandomIt, typename Derived>
class GroupIteratorBase<RandomIt, Derived, std::random_access_iterator_tag>
    : public GroupIteratorBase<RandomIt,
                               Derived,
                               std::bidirectional_iterator_tag> {
	typedef detail_group_iterator::
	    GroupIteratorBase<RandomIt, Derived, std::bidirectional_iterator_tag>
	        Base_;

public:
	typedef typename Base_::difference_type difference_type;
	typedef typename Base_::reference reference;

	GroupIteratorBase();
	GroupIteratorBase(RandomIt it, difference_type group_size);
	GroupIteratorBase(const GroupIteratorBase& other);
	GroupIteratorBase& operator=(const GroupIteratorBase& other);
	~GroupIteratorBase();

	Derived& operator+=(difference_type n);
	Derived& operator-=(difference_type n);
	reference operator[](difference_type n) const;
};

} // namespace detail_group_iterator

#include "bidirectional.tpp" // IWYU pragma: export
#include "forward.tpp"       // IWYU pragma: export
#include "random_access.tpp" // IWYU pragma: export
