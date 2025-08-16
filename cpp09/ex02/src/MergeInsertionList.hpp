#pragma once

#include <list>
#include <memory>

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
public:
	class Run;

	typedef typename std::list<Run>::value_type value_type;
	typedef typename std::list<Run>::size_type size_type;
	typedef typename std::list<Run>::difference_type difference_type;
	typedef typename std::list<Run>::reference reference;
	typedef typename std::list<Run>::const_reference const_reference;
	typedef typename std::list<Run>::pointer pointer;
	typedef typename std::list<Run>::const_pointer const_pointer;
	typedef typename std::list<Run>::iterator iterator;
	typedef typename std::list<Run>::const_iterator const_iterator;

	/**
	 * @param lst Ownership of the input list is taken.
	 */
	explicit MergeInsertionList(std::auto_ptr<std::list<T> > lst);
	~MergeInsertionList();

	void half_skip_size();

	iterator begin();
	const_iterator begin() const;
	iterator end();
	const_iterator end() const;

private:
	MergeInsertionList();
	MergeInsertionList(const MergeInsertionList& other);
	MergeInsertionList& operator=(const MergeInsertionList& other);

	void _sort_pair(typename std::list<T>::iterator left,
	                typename std::list<T>::iterator right);

	std::auto_ptr<std::list<T> > _lst_base;
	std::list<Run> _lst;
	iterator _end;
	typename std::list<T>::size_type _skip_size;
};

template <typename T>
class MergeInsertionList<T>::Run {
public:
	explicit Run(typename std::list<T>::iterator pos);

	operator const T&() const; // NOLINT(google-explicit-constructor)

	void grow(std::list<Run>& node);
	void split(std::list<Run>& lst, typename std::list<Run>::iterator this_it);
	void sort_pair(Run& other,
	               typename std::list<T>::iterator begin,
	               std::list<T>& lst);
	void swap(Run& other);

	typename std::list<T>::iterator& pos() throw();
	const typename std::list<T>::iterator& pos() const throw();
	typename std::list<T>::size_type& size() throw();
	const typename std::list<T>::size_type& size() const throw();

private:
	std::list<Run> _halfs; // Front is top of stack.
	typename std::list<T>::iterator _pos;
	typename std::list<T>::size_type _size;
};

#include "MergeInsertionList.tpp" // IWYU pragma: export
