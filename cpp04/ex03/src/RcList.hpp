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

	void push_front(T* content);
	void push_back(T* content);
	void swap(RcList& other);
	T* find(const T* content) const;
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

	static void _drop_node(Node* node);

	Node* _find_node(const T* content) const;
	bool _increase_ref(const T* content);
	bool _decrease_ref(T* content);

	Node* _head;
	Node* _tail;
};

#ifndef RCLIST_TPP
#include "RcList.tpp"
#endif

#endif

// NOLINTEND(cppcoreguidelines-special-member-functions)
