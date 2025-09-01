#pragma once

#include "GroupIterator.hpp"
#include "libftpp/algorithm.hpp"
#include "libftpp/functional.hpp"
#include "libftpp/iterator.hpp"
#include "libftpp/type_traits.hpp"
#include "merge_insertion_sort.hpp"
#include <algorithm>
#include <iterator>

namespace detail_merge_insertion_sort {
template <typename C, typename Compare>
static void merge_insertion_sort_recursive(C& cont,
                                           C& buf,
                                           typename C::size_type group_size,
                                           Compare comp);
template <typename C, typename Compare>
static void
merge_to_pairs(C& cont, typename C::size_type group_size, Compare comp);
template <typename C, typename Compare>
static void split_and_insert_pairs(C& cont,
                                   C& buf,
                                   typename C::size_type pair_size,
                                   Compare comp);
template <typename It, typename Size, typename Compare>
static GroupIterator<It> binary_insertion(GroupIterator<It> group_it,
                                          Size insert_amount,
                                          GroupIterator<It> buf_begin,
                                          GroupIterator<It> buf_end,
                                          Compare comp);
template <typename It>
static void insert_by_shift_out(GroupIterator<It> group_it,
                                GroupIterator<It> insert_pos,
                                GroupIterator<It> buf_end);
} // namespace detail_merge_insertion_sort

template <typename C>
REQUIRES(ft::is_bidirectional_iterator<typename C::iterator>::value)
(void)merge_insertion_sort(C& container)
{
	merge_insertion_sort(container, ft::less<typename C::value_type>());
}

template <typename C, typename Compare>
REQUIRES(ft::is_bidirectional_iterator<typename C::iterator>::value)
(void)merge_insertion_sort(C& container, Compare comp)
{
	if (container.size() < 2) {
		return;
	}
	C buf(container.size());
	detail_merge_insertion_sort::merge_insertion_sort_recursive(
	    container, buf, 1, comp);
}

namespace detail_merge_insertion_sort {

template <typename C, typename Compare>
static void merge_insertion_sort_recursive(C& cont,
                                           C& buf,
                                           typename C::size_type group_size,
                                           Compare comp)
{
	const typename C::size_type pair_size = group_size * 2;
	if (pair_size > cont.size()) {
		return;
	}
	merge_to_pairs(cont, group_size, comp);
	merge_insertion_sort_recursive(cont, buf, pair_size, comp);
	if (cont.size() / group_size < 3) {
		return;
	}
	split_and_insert_pairs(cont, buf, pair_size, comp);
}

/**
 * "Merging" means ordering the groups in pairs, using 1 comparison for every
 * pair.
 * As a result of this function, a larger group iterator can now count each
 * ordered pair as one group.
 */
template <typename C, typename Compare>
static void
merge_to_pairs(C& cont, typename C::size_type group_size, Compare comp)
{
	typedef GroupIterator<typename C::iterator> GroupIt;
	const typename C::size_type pair_size = group_size * 2;

	for (GroupIt low(cont.begin(), group_size),
	     high = ++GroupIt(cont.begin(), group_size),
	     pairs_end = GroupIt::end(cont.begin(), cont.end(), pair_size);
	     low != pairs_end;
	     std::advance(low, 2), std::advance(high, 2)) {
		if (comp(*high, *low)) { //! Comparison here.
			iter_swap(low, high);
		}
	}
}

/**
 * Have a buffer of same size as the main container.
 * For every search range, first push the highs into the buffer, then insert the
 * lows. Push means `copy()`. Insert means `shift_right()` and `copy()`.
 * Repeat with the next search range.
 *
 * The search range is so that we maximize the amount of elements to insert with
 * the lowest amount of comparisons currently possible. It always doubles (plus
 * 1) due to the fact that the amount of comparisons in binary insertion is same
 * for 2^n and 2^(n+1)-1.
 *
 * At the very end, copy leftovers and swap the buffer with the main container.
 */
template <typename C, typename Compare>
static void split_and_insert_pairs(C& cont,
                                   C& buf,
                                   typename C::size_type pair_size,
                                   Compare comp)
{
	typedef typename C::iterator It;
	typedef typename C::size_type Size;
	typedef GroupIterator<It> GroupIt;

	const Size group_size = pair_size / 2;
	It buf_it = buf.begin();
	Size search_size = 0;
	Size max_search_size = 1;
	Size same_comp_size = 1;

	// First node is known to be lowest.
	buf_it = ft::copy_n(cont.begin(), group_size, buf_it);
	++search_size;

	GroupIt pair_it(ft::next(cont.begin(), group_size), pair_size);
	const GroupIt pairs_end =
	    GroupIt::end(pair_it.begin(), cont.end(), pair_size);
	while (pair_it != pairs_end) {
		same_comp_size *= 2;
		max_search_size += same_comp_size; // 3, 7, 15, 31, ...

		// Push highs to buf.
		Size insert_amount = 0;
		while (search_size < max_search_size && pair_it != pairs_end) {
			buf_it = std::copy(pair_it.begin(), pair_it.middle(), buf_it);
			++pair_it, ++search_size;
			++insert_amount;
		}

		// Insert lows into buf.
		buf_it = binary_insertion(--GroupIt(pair_it.begin(), group_size),
		                          insert_amount,
		                          GroupIt(buf.begin(), group_size),
		                          GroupIt(buf_it, group_size),
		                          comp)
		             .begin();
		search_size += insert_amount;
	}

	std::copy(pairs_end.begin(), cont.end(), buf_it);
	cont.swap(buf);
}

/**
 * Inserts every second group in decreasing order.
 * Insertion happens at the upper bound of any duplicates so less elements need
 * to be shifted to the right.
 */
template <typename It, typename Size, typename Compare>
static GroupIterator<It> binary_insertion(GroupIterator<It> group_it,
                                          Size insert_amount,
                                          GroupIterator<It> buf_begin,
                                          GroupIterator<It> buf_end,
                                          Compare comp)
{
	GroupIterator<It> search_end = buf_end;
	for (Size _ = 0; _ < insert_amount; ++_) {
		const GroupIterator<It> insert_pos =
		    std::upper_bound( //! Comparison here.
		        buf_begin,
		        search_end,
		        *group_it,
		        comp);
		if (insert_pos == search_end) {
			--search_end;
		}
		insert_by_shift_out(group_it, insert_pos, ++buf_end);
		std::advance(group_it, -2);
	}
	return buf_end;
}

/**
 * Makes way for a group, shifting everything from `insert_pos` to `buf_end` to
 * the right. What would get shifted past `buf_end` gets lost.
 */
template <typename It>
static void insert_by_shift_out(GroupIterator<It> group_it,
                                GroupIterator<It> insert_pos,
                                GroupIterator<It> buf_end)
{
	ft::shift_right(insert_pos.begin(), buf_end.begin(), group_it.size());
	std::copy(group_it.begin(), group_it.end(), insert_pos.begin());
}

} // namespace detail_merge_insertion_sort
