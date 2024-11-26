#include "List.hpp"
#include <cstddef>

List::List() : _head(NULL), _tail(NULL) {}

List::List(void* content) : _head(new Node(content)), _tail(this->_head) {}

List::List(const List& other) : _head(NULL), _tail(NULL)
{
	for (Node* cur = other._head; cur != NULL; cur = cur->next) {
		this->push_back(cur->content);
	}
}

List::~List()
{
	this->clear();
}

List& List::operator=(List other)
{
	this->swap(other);
	return *this;
}

void List::push_front(void* content)
{
	Node* new_node = new Node(content);

	new_node->next = this->_head;
	this->_head = new_node;
	if (this->_tail == NULL) {
		this->_tail = new_node;
	}
}

void List::push_back(void* content)
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

void List::swap(List& other)
{
	Node* tmp = this->_head;
	this->_head = other._head;
	other._head = tmp;

	tmp = this->_tail;
	this->_tail = other._tail;
	other._tail = tmp;
}

void List::clear()
{
	while (Node* cur = this->_head) {
		this->_head = this->_head->next;
		delete cur;
	}
}

List::Node::Node(void* content) : content(content), next(NULL) {}
