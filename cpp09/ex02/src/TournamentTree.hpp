#pragma once

#include <list>

/**
 * @brief A very minimal implementation of a tournament tree
 *
 * Elements are compared with `<` and the highest value will be at the top.
 *
 * Example structure for a tree of size 8:
 *                           e4
 *                           |
 *             +-------------+-------------+
 *             |                           |
 *             e4                          e6(L0)
 *             |                           |
 *      +------+------+             +------+------+
 *      |             |             |             |
 *      e2(L1)        e4            e6            e7
 *      |             |             |             |
 *  +---+---+     +---+---+     +---+---+     +---+---+
 *  |       |     |       |     |       |     |       |
 *  e1      e2    e3(L2)  e4    e5      e6    e7      e8
 *
 * The tree stores the overall winner (e.g., e4) and a list of the subtrees it
 * has directly beaten (L_).
 */
template <typename T>
class TournamentTree {
public:
	typedef T value_type;
	typedef typename std::list<TournamentTree>::size_type size_type;
	typedef typename std::list<TournamentTree>::difference_type difference_type;
	typedef value_type& reference;
	typedef const value_type& const_reference;
	typedef value_type* pointer;
	typedef const value_type* const_pointer;
	typedef typename std::list<TournamentTree>::iterator iterator;

	explicit TournamentTree(const value_type& pos);
	TournamentTree(const TournamentTree& other);
	TournamentTree& operator=(TournamentTree other);
	~TournamentTree();

	bool operator<(const TournamentTree& other) const;

	/**
	 * @brief Compare the winner of another tree and move it to 1st or 2nd place
	 */
	void merge(std::list<TournamentTree>& src_lst, iterator src_pos);
	/**
	 * @brief Move the losing subtree into a provided list
	 */
	void split(std::list<TournamentTree>& dest_lst, iterator dest_pos);
	void swap(TournamentTree& other);

	const_reference top() const throw();
	size_type size() const throw();

private:
	TournamentTree();

	std::list<TournamentTree> _losers; // Front is first child.
	value_type _winner;
	size_type _size;
};

#include "TournamentTree.tpp" // IWYU pragma: export
