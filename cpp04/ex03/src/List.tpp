#ifndef LIST_TPP
#define LIST_TPP

#ifndef LIST_HPP
#include "List.hpp"
#endif

#include <cstddef>

template <typename T>
List<T>::List() : _head(NULL), _tail(NULL)
{
}

template <typename T>
List<T>::List(const List& other) : _head(NULL), _tail(NULL)
{
	for (Node* cur = other._head; cur != NULL; cur = cur->next) {
		this->push_back(cur->content);
	}
}

template <typename T>
List<T>::~List()
{
	this->clear();
}

template <typename T>
List<T>& List<T>::operator=(List other)
{
	this->swap(other);
	return *this;
}

template <typename T>
void List<T>::push_front(T* content)
{
	Node* new_node = new Node(content);

	new_node->next = this->_head;
	this->_head = new_node;
	if (this->_tail == NULL) {
		this->_tail = new_node;
	}
}

template <typename T>
void List<T>::push_back(T* content)
{
	Node* new_node = new Node(content);

	if (this->_head == NULL) {
		this->_head = new_node;
	}
	else {
		this->_tail->next = new_node;
	}
	this->_tail = new_node;
}

template <typename T>
void List<T>::swap(List& other)
{
	Node* tmp = this->_head;
	this->_head = other._head;
	other._head = tmp;

	tmp = this->_tail;
	this->_tail = other._tail;
	other._tail = tmp;
}

template <typename T>
void List<T>::clear()
{
	while (this->_head != NULL) {
		Node* cur = this->_head;
		this->_head = this->_head->next;
		delete cur->content;
		delete cur;
	}
}

template <typename T>
List<T>::Node::Node(T* content) : content(content), next(NULL)
{
}

#endif
