// NOLINTBEGIN(cppcoreguidelines-special-member-functions)

#ifndef RCLIST_HPP
#define RCLIST_HPP

template <typename T>
class RcList;

// TODO: I could just make a Rc class and this could then be a normal linked list
template <typename T>
class RcList<T*> {
public:
	RcList();
	RcList(const RcList& other);
	~RcList();

	RcList& operator=(RcList other);

	// TODO: Consider that many methods can be made static
	void push_front(T* content);
	void push_back(T* content);
	void swap(RcList& other);
	T* find(T* content);
	void remove(T* content);
	void forget(T* content);
	void clear();

private:
	struct Node {
		Node(T* content_, RcList* parent_);
		~Node();

		T* content;
		int refs;
		RcList* parent;
		Node* next;
		Node* prev;
	};

	Node* _find_node(T* content);
	void _drop_node(Node* node);
	bool _increase_ref(T* content);
	bool _decrease_ref(T* content);

	Node* _head;
	Node* _tail;
};

#ifndef RCLIST_TPP
#include "RcList.tpp"
#endif

#endif

// NOLINTEND(cppcoreguidelines-special-member-functions)
