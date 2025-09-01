#pragma once

#include "TournamentTree.hpp"
#include "libftpp/algorithm.hpp"
#include <cassert>
#include <list>

template <typename T, typename Compare /*= ft::less<T> */>
TournamentTree<T, Compare>::TournamentTree(const T& pos,
                                           const Compare& comp /*= Compare()*/)
    : _winner(pos),
      _size(1),
      _comp(comp)
{}

template <typename T, typename Compare /*= ft::less<T> */>
TournamentTree<T, Compare>::TournamentTree(const TournamentTree& other)
    : _losers(other._losers),
      _winner(other._winner),
      _size(other._size),
      _comp(other._comp)
{}

template <typename T, typename Compare /*= ft::less<T> */>
TournamentTree<T, Compare>&
TournamentTree<T, Compare>::operator=(TournamentTree other)
{
	swap(other);
	return *this;
}

template <typename T, typename Compare /*= ft::less<T> */>
TournamentTree<T, Compare>::~TournamentTree()
{}

template <typename T, typename Compare /*= ft::less<T> */>
void TournamentTree<T, Compare>::merge(std::list<TournamentTree>& src_lst,
                                       iterator src_pos)
{
	if (_comp(*this->_winner, *src_pos->_winner)) {
		swap(*src_pos);
	}
	_losers.splice(_losers.begin(), src_lst, src_pos);
	_size += src_pos->size();
}

template <typename T, typename Compare /*= ft::less<T> */>
void TournamentTree<T, Compare>::split(std::list<TournamentTree>& dest_lst,
                                       iterator dest_pos)
{
	assert(!_losers.empty());

	iterator prev_loser = _losers.begin();
	dest_lst.splice(dest_pos, _losers, prev_loser);
	_size -= prev_loser->size();
}

template <typename T, typename Compare /*= ft::less<T> */>
void TournamentTree<T, Compare>::swap(TournamentTree& other)
{
	// Use ft::swap to prevent ambiguities caused by ADL.
	ft::swap(_losers, other._losers);
	ft::swap(_winner, other._winner);
	ft::swap(_size, other._size);
	ft::swap(_comp, other._comp);
}

template <typename T, typename Compare /*= ft::less<T> */>
typename TournamentTree<T, Compare>::const_reference
TournamentTree<T, Compare>::top() const throw()
{
	return _winner;
}

template <typename T, typename Compare /*= ft::less<T> */>
typename TournamentTree<T, Compare>::size_type
TournamentTree<T, Compare>::size() const throw()
{
	return _size;
}

template <typename T, typename Compare /*= ft::less<T> */>
typename TournamentTree<T, Compare>::value_compare
TournamentTree<T, Compare>::value_comp() const
{
	return _comp;
}
