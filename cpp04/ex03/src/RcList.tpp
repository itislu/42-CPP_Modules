#ifndef RCLIST_TPP
#define RCLIST_TPP

#ifndef RCLIST_HPP
#include "RcList.hpp"
#endif

#include <cstddef>
#include <cstring>
#include <iostream>

template <typename T>
RcList<T*>::RcList() : _head(), _tail(), _size()
{
}

template <typename T>
RcList<T*>::RcList(const RcList& other) : _head(), _tail(), _size()
{
	for (Node* cur = other._head; cur != NULL; cur = cur->next) {
		this->push_back(cur->content);
	}
}

template <typename T>
RcList<T*>::~RcList()
{
	this->clear();
}

template <typename T>
RcList<T*>& RcList<T*>::operator=(RcList other)
{
	this->swap(other);
	return *this;
}

template <typename T>
void RcList<T*>::push_front(T* content)
{
	if (this->_increase_ref(content)) {
		return;
	}
	Node* new_node = new Node(content);
	new_node->next = this->_head;
	if (this->_head != NULL) {
		this->_head->prev = new_node;
	}
	this->_head = new_node;
	if (this->_tail == NULL) {
		this->_tail = new_node;
	}
	++this->_size;
}

template <typename T>
void RcList<T*>::push_back(T* content)
{
	std::cerr << "push_back " << content << '\n';

	if (this->_increase_ref(content)) {
		return;
	}
	Node* new_node = new Node(content);
	if (this->_head == NULL) {
		this->_head = new_node;
	}
	else {
		this->_tail->next = new_node;
	}
	new_node->prev = this->_tail;
	this->_tail = new_node;
	++this->_size;
}

template <typename T>
void RcList<T*>::swap(RcList& other)
{
	char tmp[sizeof(RcList)];

	memcpy(static_cast<void*>(tmp), static_cast<void*>(this), sizeof(RcList));
	memcpy(
	    static_cast<void*>(this), static_cast<void*>(&other), sizeof(RcList));
	memcpy(static_cast<void*>(&other), static_cast<void*>(tmp), sizeof(RcList));
}

template <typename T>
size_t RcList<T*>::size() const
{
	return this->_size;
}

template <typename T>
void RcList<T*>::forget(T* content)
{
	std::cerr << "forget " << content << '\n';

	this->_drop_node(this->_find_node(content));
}

template <typename T>
void RcList<T*>::remove(T* content)
{
	std::cerr << "remove " << content << '\n';

	this->_decrease_ref(content);
}

template <typename T>
void RcList<T*>::clear()
{
	std::cerr << "Clearing RcList" << '\n';
	size_t i = 0;

	while (this->_head != NULL) {
		std::cerr << "Deleting node " << i++ << '\n';
		this->_clean_node(this->_head);
	}
}

template <typename T>
bool RcList<T*>::_increase_ref(const T* content)
{
	Node* hit = this->_find_node(content);
	if (hit == NULL) {
		return false;
	}
	++hit->refs;
	return true;
}

template <typename T>
bool RcList<T*>::_decrease_ref(T* content)
{
	std::cerr << "_decrease_ref " << content << '\n';

	Node* hit = this->_find_node(content);
	if (hit == NULL) {
		return false;
	}
	if (--hit->refs == 0) {
		this->_clean_node(hit);
	}
	return true;
}

template <typename T>
typename RcList<T*>::Node* RcList<T*>::_find_node(const T* content) const
{
	for (Node* cur = this->_head; cur != NULL; cur = cur->next) {
		if (cur->content == content) {
			return cur;
		}
	}
	return NULL;
}

template <typename T>
T* RcList<T*>::_drop_node(Node* node)
{
	if (node == NULL) {
		return NULL;
	}
	if (node == this->_head) {
		this->_head = this->_head->next;
	}
	if (node == this->_tail) {
		this->_tail = this->_tail->prev;
	}
	T* content = node->content;
	delete node;
	--this->_size;
	return content;
}

template <typename T>
void RcList<T*>::_clean_node(Node* node)
{
	delete this->_drop_node(node);
}

template <typename T>
RcList<T*>::Node::Node(T* content_) : content(content_), refs(1), next(), prev()
{
}

template <typename T>
RcList<T*>::Node::~Node()
{
	std::cerr << "Node destructor containing " << this->content << '\n';

	if (this->prev != NULL) {
		this->prev->next = this->next;
	}
	if (this->next != NULL) {
		this->next->prev = prev;
	}
}

#endif
