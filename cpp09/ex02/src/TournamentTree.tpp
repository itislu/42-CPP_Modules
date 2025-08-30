#pragma once

#include "TournamentTree.hpp"
#include <algorithm>
#include <cassert>
#include <list>

template <typename T>
TournamentTree<T>::TournamentTree(const value_type& pos)
    : _winner(pos),
      _size(1)
{}

template <typename T>
TournamentTree<T>::TournamentTree(const TournamentTree& other)
    : _losers(other._losers),
      _winner(other._winner),
      _size(other._size)
{}

template <typename T>
TournamentTree<T>& TournamentTree<T>::operator=(TournamentTree other)
{
	swap(other);
	return *this;
}

template <typename T>
TournamentTree<T>::~TournamentTree()
{}

template <typename T>
bool TournamentTree<T>::operator<(const TournamentTree& other) const
{
	return *_winner < *other._winner;
}

template <typename T>
void TournamentTree<T>::merge(std::list<TournamentTree>& src_lst,
                              iterator src_pos)
{
	if (*this < *src_pos) {
		swap(*src_pos);
	}
	_losers.splice(_losers.begin(), src_lst, src_pos);
	_size += src_pos->size();
}

template <typename T>
void TournamentTree<T>::split(std::list<TournamentTree>& dest_lst,
                              iterator dest_pos)
{
	assert(!_losers.empty());

	iterator prev_loser = _losers.begin();
	dest_lst.splice(dest_pos, _losers, prev_loser);
	_size -= prev_loser->size();
}

template <typename T>
void TournamentTree<T>::swap(TournamentTree& other)
{
	using std::swap;
	swap(_losers, other._losers);
	swap(_winner, other._winner);
	swap(_size, other._size);
}

template <typename T>
typename TournamentTree<T>::const_reference TournamentTree<T>::top() const
    throw()
{
	return _winner;
}

template <typename T>
typename TournamentTree<T>::size_type TournamentTree<T>::size() const throw()
{
	return _size;
}
