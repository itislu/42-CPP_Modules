#ifndef REFCOUNTEDLIST_TPP
#define REFCOUNTEDLIST_TPP

#ifndef REFCOUNTEDLIST_HPP
#include "RefCountedList.hpp"
#endif

#include <cstddef>
#include <iostream>

template <typename T>
RefCountedList<T*>::RefCountedList() : _head(), _tail()
{
}

template <typename T>
RefCountedList<T*>::RefCountedList(const RefCountedList& other) :
    _head(), _tail()
{
	for (Node* cur = other._head; cur != NULL; cur = cur->next) {
		this->push_back(cur->content);
	}
}

template <typename T>
RefCountedList<T*>::~RefCountedList()
{
	this->clear();
}

template <typename T>
RefCountedList<T*>& RefCountedList<T*>::operator=(RefCountedList other)
{
	this->swap(other);
	return *this;
}

template <typename T>
void RefCountedList<T*>::push_front(T* content)
{
	if (this->_increase_ref(content)) {
		return;
	}
	Node* new_node = new Node(content, this);
	new_node->next = this->_head;
	if (this->_head != NULL) {
		this->_head->prev = new_node;
	}
	this->_head = new_node;
	if (this->_tail == NULL) {
		this->_tail = new_node;
	}
}

template <typename T>
void RefCountedList<T*>::push_back(T* content)
{
	std::cout << "push_back " << content << '\n';

	if (this->_increase_ref(content)) {
		return;
	}
	Node* new_node = new Node(content, this);
	if (this->_head == NULL) {
		this->_head = new_node;
	}
	else {
		this->_tail->next = new_node;
	}
	new_node->prev = this->_tail;
	this->_tail = new_node;
}

template <typename T>
void RefCountedList<T*>::swap(RefCountedList& other)
{
	Node* tmp = this->_head;
	this->_head = other._head;
	other._head = tmp;

	tmp = this->_tail;
	this->_tail = other._tail;
	other._tail = tmp;
}

template <typename T>
T* RefCountedList<T*>::find(T* content)
{
	std::cout << "find " << content << '\n';

	for (Node* cur = this->_head; cur != NULL; cur = cur->next) {
		if (cur->content == content) {
			return cur->content;
		}
	}
	return NULL;
}

template <typename T>
void RefCountedList<T*>::remove(T* content)
{
	std::cout << "remove " << content << '\n';

	this->_decrease_ref(content);
}

template <typename T>
void RefCountedList<T*>::forget(T* content)
{
	std::cout << "forget " << content << '\n';

	delete this->_find_node(content);
}

template <typename T>
void RefCountedList<T*>::clear()
{
	int i = 0;
	std::cout << "Clearing RefCountedList" << '\n';
	while (this->_head != NULL) {
		std::cout << "Deleting node " << i++ << '\n';
		this->_drop_node(this->_head);
	}
}

template <typename T>
typename RefCountedList<T*>::Node* RefCountedList<T*>::_find_node(T* content)
{
	for (Node* cur = this->_head; cur != NULL; cur = cur->next) {
		if (cur->content == content) {
			return cur;
		}
	}
	return NULL;
}

template <typename T>
void RefCountedList<T*>::_drop_node(Node* node)
{
	if (node == NULL) {
		return;
	}
	const T* tmp = node->content;
	delete node;
	delete tmp;
}

template <typename T>
bool RefCountedList<T*>::_increase_ref(T* content)
{
	Node* hit = this->_find_node(content);
	if (hit == NULL) {
		return false;
	}
	++hit->refs;
	return true;
}

template <typename T>
bool RefCountedList<T*>::_decrease_ref(T* content)
{
	std::cout << "_decrease_ref " << content << '\n';

	Node* hit = this->_find_node(content);
	if (hit == NULL) {
		return false;
	}
	if (--hit->refs == 0) {
		this->_drop_node(hit);
	}
	return true;
}

template <typename T>
RefCountedList<T*>::Node::Node(T* content_, RefCountedList* parent_) :
    content(content_), refs(1), parent(parent_), next(), prev()
{
}

template <typename T>
RefCountedList<T*>::Node::~Node()
{
	if (this->parent != NULL) {
		if (this == this->parent->_head) {
			this->parent->_head = this->parent->_head->next;
		}
		if (this == this->parent->_tail) {
			this->parent->_tail = this->parent->_tail->prev;
		}
	}
	if (this->prev != NULL) {
		this->prev->next = this->next;
	}
	if (this->next != NULL) {
		this->next->prev = prev;
	}

	std::cout << "Node destructor containing " << this->content << '\n';
	// this->content->~T();
	// ::operator delete(this->content);
	// delete this->content;
}

#endif
