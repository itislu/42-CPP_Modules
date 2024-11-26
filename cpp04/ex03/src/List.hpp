#ifndef LIST_HPP
#define LIST_HPP

template <typename T>
class List {
public:
	List();
	List(const List& other);
	~List();

	List& operator=(List other);

	void push_front(T* content);
	void push_back(T* content);
	void swap(List& other);
	void clear();

private:
	struct Node {
		Node(T* content);

		T* content;
		Node* next;
	};

	Node* _head;
	Node* _tail;
};

#ifndef LIST_TPP
#include "List.tpp"
#endif

#endif
