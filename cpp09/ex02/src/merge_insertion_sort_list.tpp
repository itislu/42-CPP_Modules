#pragma once

#include "PairTree.hpp"
#include "libftpp/algorithm.hpp"
#include "libftpp/iterator.hpp"
#include "merge_insertion_sort.hpp"
#include <list>

namespace detail_merge_insertion_sort_list {
template <typename T>
static void build_layered_main_chain(std::list<T>& lst,
                                     std::list<PairTree<T> >& main_chain);
template <typename T>
static void split_and_insert_pairs(std::list<PairTree<T> >& main_chain);
template <typename T, typename Size>
static void
binary_insertion(std::list<PairTree<T> >& pend_stack,
                 typename std::list<PairTree<T> >::iterator search_end,
                 Size search_size,
                 std::list<PairTree<T> >& main_chain);
template <typename T>
static void apply_sorted_main_chain(const std::list<PairTree<T> >& main_chain,
                                    std::list<T>& lst);
} // namespace detail_merge_insertion_sort_list

/**
 * There are 3 points of optimization for `std::list` in this implementation:
 *
 * - Never copy the value type `T`.
 *   Instead, sort iterators to each node and in the end arrange the input list
 *   into the correct order in one iteration.
 *
 * - Reuse allocated nodes.
 *   Always use `splice()` to move nodes between lists.
 *
 * - Greatly reduce the amount of iterations over the list.
 *   This is achieved by building a tree structure out of the list. This trades
 *   memory consumption for logarithmic-time access to all points of interest
 *   for the binary insertion part of merge-insertion sort.
 */
template <typename T>
void merge_insertion_sort_list(std::list<T>& lst)
{
	if (lst.size() < 2) {
		return;
	}
	std::list<PairTree<T> > main_chain;
	detail_merge_insertion_sort_list::build_layered_main_chain(lst, main_chain);
	detail_merge_insertion_sort_list::split_and_insert_pairs(main_chain);
	detail_merge_insertion_sort_list::apply_sorted_main_chain(main_chain, lst);
}

namespace detail_merge_insertion_sort_list {

/**
 * In a single iteration over the given list create pairs of increasing size.
 * While iterating, pairs keep getting merged into larger pairs whose sizes
 * double (4, 8, 16, etc). The pairs are ordered always by their last element.
 *
 * main_chain:
 * 1       ->     1
 * 1 1     ->     2
 * 1 2     ->   1 2
 * 1 1 2   ->     4
 * 1 4     ->   1 4
 * 1 1 4   ->   2 4
 * N = pair size
 */
template <typename T>
static void build_layered_main_chain(std::list<T>& lst,
                                     std::list<PairTree<T> >& main_chain)
{
	typedef typename std::list<T>::iterator ListIt;
	typedef typename std::list<PairTree<T> >::iterator PairsIt;

	for (ListIt it = lst.begin(), end = lst.end(); it != end; ++it) {
		// Use main_chain as a stack.
		// Biggest pair at the bottom. Build up current pair with the top.
		PairsIt next = main_chain.begin();
		main_chain.push_front(PairTree<T>(it));
		while (next != main_chain.end()
		       && main_chain.front().size() == next->size()) {
			main_chain.front().insert(main_chain, next++);
		}
	}
	main_chain.reverse(); // Move leftovers to the back in decreasing pair size.
}

/**
 * Alternate between splitting the lower of the pairs in the main chain into a
 * pending stack and inserting them back in correct order.
 *
 * The interval is so that the search size for insertion always exactly doubles.
 * This is due to the fact that the amount of comparisons in binary insertion is
 * same for 2^n and 2^(n+1)-1.
 *
 * Repeat until all pairs are fully split up.
 */
template <typename T>
static void split_and_insert_pairs(std::list<PairTree<T> >& main_chain)
{
	typedef typename std::list<PairTree<T> >::iterator PairsIt;
	typedef typename std::list<PairTree<T> >::size_type Size;

	std::list<PairTree<T> > pend_stack;
	PairsIt layer_end = ft::next(main_chain.begin());

	for (Size pair_size = main_chain.front().size(); pair_size > 1;
	     pair_size /= 2) {
		Size search_size = 0;
		Size max_search_size = 1;
		Size same_comp_size = 1;
		PairsIt pair_it = main_chain.begin();

		// First node is known to be lowest.
		pair_it->split(main_chain, pair_it);
		++search_size;

		while (pair_it != layer_end) {
			same_comp_size *= 2;
			max_search_size += same_comp_size; // 3, 7, 15, 31, ...

			// Split lows into pend_stack.
			while (search_size < max_search_size) {
				++pair_it, ++search_size;
				if (pair_it == layer_end) {
					// Check for leftover without a pair.
					if (pair_it != main_chain.end()
					    && pair_it->size() == pair_size / 2) {
						pend_stack.splice(
						    pend_stack.begin(), main_chain, pair_it++);
						layer_end = pair_it;
					}
					break;
				}
				pair_it->split(pend_stack, pend_stack.begin());
			}

			// Binary insertion.
			const Size insert_amount = pend_stack.size();
			binary_insertion(pend_stack, pair_it, search_size, main_chain);
			search_size += insert_amount;
		}
	}
}

/**
 * Search size normally stays constant (max_search_size) due to the partial
 * order achieved by the pairwise sorting in the beginning of the algorithm and
 * because the pend_stack elements get inserted in decreasing order.
 * But if the new element gets inserted after the next pend_stack's higher pair,
 * that higher pair will be two elements apart from the current pend_stack's
 * higher pair.
 * Insertion happens at the upper bound of any duplicates to allow for more such
 * search size decreases.
 */
template <typename T, typename Size>
static void
binary_insertion(std::list<PairTree<T> >& pend_stack,
                 typename std::list<PairTree<T> >::iterator search_end,
                 Size search_size,
                 std::list<PairTree<T> >& main_chain)
{
	typedef typename std::list<PairTree<T> >::iterator PairsIt;

	while (!pend_stack.empty()) {
		const PairsIt insert_pos = ft::upper_bound(
		    main_chain.begin(), search_size, pend_stack.front());
		if (insert_pos == search_end) {
			--search_size;
		}
		--search_end;
		main_chain.splice(insert_pos, pend_stack, pend_stack.begin());
	}
}

template <typename T>
static void apply_sorted_main_chain(const std::list<PairTree<T> >& main_chain,
                                    std::list<T>& lst)
{
	typedef typename std::list<T>::iterator ListIt;
	typedef typename std::list<PairTree<T> >::const_iterator ConstPairsIt;

	ListIt insert_pos = lst.begin();
	for (ConstPairsIt node = main_chain.begin(); node != main_chain.end();
	     ++node) {
		ListIt cur = node->last();
		if (cur == insert_pos) {
			++insert_pos;
			continue;
		}
		lst.splice(insert_pos, lst, cur);
	}
}

} // namespace detail_merge_insertion_sort_list
