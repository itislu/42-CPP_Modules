// NOLINTBEGIN(cppcoreguidelines-special-member-functions)

#ifndef REFCOUNTEDLIST_HPP
#define REFCOUNTEDLIST_HPP

template <typename T>
class RefCountedList;

// TODO: Rename to RcList
// TODO: I could just make a Rc class and this could then be a normal linked list
template <typename T>
class RefCountedList<T*> {
public:
	RefCountedList();
	RefCountedList(const RefCountedList& other);
	~RefCountedList();

	RefCountedList& operator=(RefCountedList other);

	// TODO: Consider that many methods can be made static
	void push_front(T* content);
	void push_back(T* content);
	void swap(RefCountedList& other);
	T* find(T* content);
	void remove(T* content);
	void forget(T* content);
	void clear();

private:
	struct Node {
		Node(T* content_, RefCountedList* parent_);
		~Node();

		T* content;
		int refs;
		RefCountedList* parent;
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

#ifndef REFCOUNTEDLIST_TPP
#include "RefCountedList.tpp"
#endif

#endif

// NOLINTEND(cppcoreguidelines-special-member-functions)
