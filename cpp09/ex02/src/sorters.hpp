#pragma once

#include "libftpp/functional.hpp"
#include "merge_insertion_sort.hpp"
#include <algorithm>
#include <list>
#include <string>

template <typename Compare = ft::less<> >
struct MergeInsertionSorter {
	typedef Compare value_compare;

	static const std::string& name()
	{
		static const std::string name = "merge_insertion_sort()";
		return name;
	}

	template <typename C>
	void operator()(C& container)
	{
		merge_insertion_sort(container, value_comp());
	}

	value_compare value_comp() { return value_compare(); }
};

template <typename Compare = ft::less<> >
struct MergeInsertionListSorter {
	typedef Compare value_compare;

	static const std::string& name()
	{
		static const std::string name = "merge_insertion_sort_list()";
		return name;
	}

	template <typename T>
	void operator()(std::list<T>& lst)
	{
		merge_insertion_sort_list(lst, value_comp());
	}

	value_compare value_comp() { return value_compare(); }
};

template <typename Compare = ft::less<> >
struct StandardSorter {
	typedef Compare value_compare;

	static const std::string& name()
	{
		static const std::string name = "std::sort()";
		return name;
	}

	template <typename C>
	void operator()(C& container)
	{
		std::sort(container.begin(), container.end(), value_comp());
	}

	value_compare value_comp() { return value_compare(); }
};

template <typename Compare = ft::less<> >
struct StandardListSorter {
	typedef Compare value_compare;

	static const std::string& name()
	{
		static const std::string name = "std::list::sort()";
		return name;
	}

	template <typename T>
	void operator()(std::list<T>& lst)
	{
		lst.sort(value_comp());
	}

	value_compare value_comp() { return value_compare(); }
};
