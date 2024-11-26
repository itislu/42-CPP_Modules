#ifndef LIST_HPP
#define LIST_HPP

class List {
public:
	List();
	List(void *content);
	List(const List& other);
	~List();

	List& operator=(List other);

	void push_front(void* content);
	void push_back(void* content);
	void swap(List& other);
	void clear();

private:
	struct Node {
		Node(void *content);

		void* content;
		Node* next;
	};

	Node* _head;
	Node* _tail;
};

#endif
