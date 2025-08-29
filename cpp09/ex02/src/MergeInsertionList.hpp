#pragma once

#include "libftpp/type_traits.hpp"
#include <iterator>
#include <list>
#include <memory>

// Actually, the user should decide if lots of copying is an issue, and supply
// a list of pointers instead...

/*
WEIRDNESSES:
TODO Need to fix!

- Construction changes _base_list, which is visible if release() after
  construction. But sort() does not change _base_list.

- Need to check everywhere if _base_list still valid (i.e. release() was not
  called).
*/

/**
 * @brief A logarithmic skip list for in-place merge-insertion sort
 *
 * The goal is to reduce unnecessary iterations over a linked list.
 * This is achieved by building a hierarchical structure during the pairwise
 * comparison part of merge-insertion sort in 1x logarithmic time.
 * It trades memory consumption for constant-time access to all points of
 * interest for the binary insertion part of merge-insertion sort.
 */
template <typename T>
class MergeInsertionList {
	class Run_;
	template <bool is_const>
	class Iterator_;

public:
	typedef T value_type;
	typedef typename std::list<T>::size_type size_type;
	typedef typename std::list<T>::difference_type difference_type;
	typedef value_type& reference;
	typedef const value_type& const_reference;
	typedef value_type* pointer;
	typedef const value_type* const_pointer;
	typedef Iterator_<false> iterator;
	typedef Iterator_<true> const_iterator;

	/**
	 * @param lst Ownership of the input list is taken.
	 */
	explicit MergeInsertionList(std::auto_ptr<std::list<T> > lst);
	~MergeInsertionList();

	void half_skip_size();
	bool sort();
	std::auto_ptr<std::list<T> > release();

	iterator begin();
	const_iterator begin() const;
	iterator end();
	const_iterator end() const;

private:
	typedef typename std::list<T>::iterator BaseListIterator_;
	typedef typename std::list<Run_>::iterator RunsIterator_;

	MergeInsertionList();
	MergeInsertionList(const MergeInsertionList& other);
	MergeInsertionList& operator=(const MergeInsertionList& other);

	void _sort_pair(BaseListIterator_ left, BaseListIterator_ right);

	std::auto_ptr<std::list<T> > _base_list;
	std::list<Run_> _runs;
	RunsIterator_ _end;
	size_type _skip_size;
};

// TODO orthodox
template <typename T>
class MergeInsertionList<T>::Run_ {
public:
	explicit Run_(BaseListIterator_ pos);

	operator T&();             // NOLINT(google-explicit-constructor)
	operator const T&() const; // NOLINT(google-explicit-constructor)

	bool operator<(const Run_& other) const;

	void grow(std::list<Run_>& node);
	void split(std::list<Run_>& target_lst, RunsIterator_ target_pos);
	void sort_pair(Run_& other, BaseListIterator_ begin, std::list<T>& lst);
	void swap(Run_& other);

	BaseListIterator_ last() const;
	BaseListIterator_ first() const;
	typename std::list<T>::size_type size() const throw();

private:
	std::list<Run_> _halfs;  // Front is top of stack.
	BaseListIterator_ _last; //? const_iterator?
	typename std::list<T>::size_type _size;
};

// TODO orthodox
template <typename T>
template <bool is_const>
class MergeInsertionList<T>::Iterator_ {
	typedef typename ft::conditional<is_const,
	                                 typename std::list<Run_>::const_iterator,
	                                 typename std::list<Run_>::iterator>::type
	    BaseIterator_;

public:
	typedef std::bidirectional_iterator_tag iterator_category;
	typedef T value_type;
	typedef typename BaseIterator_::difference_type difference_type;
	typedef typename ft::conditional<is_const, const T&, T&>::type reference;
	typedef typename ft::conditional<is_const, const T*, T*>::type pointer;

	Iterator_();
	explicit Iterator_(BaseIterator_ it);

	template <bool other_is_const>
	// NOLINTNEXTLINE(google-explicit-constructor)
	Iterator_(
	    typename ft::enable_if<is_const && !other_is_const,
	                           const Iterator_<other_is_const>&>::type other);

	BaseIterator_ base() const;

	reference operator*() const;
	pointer operator->() const;

	Iterator_& operator++();
	Iterator_ operator++(int);

	Iterator_& operator--();
	Iterator_ operator--(int);

	template <bool other_is_const>
	bool operator==(const Iterator_<other_is_const>& other) const;

	template <bool other_is_const>
	bool operator!=(const Iterator_<other_is_const>& other) const;

private:
	BaseIterator_ _it;
};

#include "MergeInsertionList.tpp" // IWYU pragma: export
