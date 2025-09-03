#pragma once

#include "sort.hpp"
#include <algorithm>
#include <list>
#include <string>

/* MergeInsertionSorter */

template <typename Compare /*= ft::less<> */>
const std::string& MergeInsertionSorter<Compare>::name()
{
	static const std::string name = "merge_insertion_sort()";
	return name;
}

template <typename Compare /*= ft::less<> */>
template <typename C>
void MergeInsertionSorter<Compare>::operator()(C& container)
{
	merge_insertion_sort(container, value_comp());
}

template <typename Compare /*= ft::less<> */>
typename MergeInsertionSorter<Compare>::value_compare
MergeInsertionSorter<Compare>::value_comp()
{
	return value_compare();
}

/* MergeInsertionListSorter */

template <typename Compare /*= ft::less<> */>
const std::string& MergeInsertionListSorter<Compare>::name()
{
	static const std::string name = "merge_insertion_sort_list()";
	return name;
}

template <typename Compare /*= ft::less<> */>
template <typename T>
void MergeInsertionListSorter<Compare>::operator()(std::list<T>& lst)
{
	merge_insertion_sort_list(lst, value_comp());
}

template <typename Compare /*= ft::less<> */>
typename MergeInsertionListSorter<Compare>::value_compare
MergeInsertionListSorter<Compare>::value_comp()
{
	return value_compare();
}

/* StandardSorter */

template <typename Compare /*= ft::less<> */>
const std::string& StandardSorter<Compare>::name()
{
	static const std::string name = "std::sort()";
	return name;
}

template <typename Compare /*= ft::less<> */>
template <typename C>
void StandardSorter<Compare>::operator()(C& container)
{
	std::sort(container.begin(), container.end(), value_comp());
}

template <typename Compare /*= ft::less<> */>
typename StandardSorter<Compare>::value_compare
StandardSorter<Compare>::value_comp()
{
	return value_compare();
}

/* StandardListSorter */

template <typename Compare /*= ft::less<> */>
const std::string& StandardListSorter<Compare>::name()
{
	static const std::string name = "std::list::sort()";
	return name;
}

template <typename Compare /*= ft::less<> */>
template <typename T>
void StandardListSorter<Compare>::operator()(std::list<T>& lst)
{
	lst.sort(value_comp());
}

template <typename Compare /*= ft::less<> */>
typename StandardListSorter<Compare>::value_compare
StandardListSorter<Compare>::value_comp()
{
	return value_compare();
}
