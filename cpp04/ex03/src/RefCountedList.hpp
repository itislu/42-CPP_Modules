// NOLINTBEGIN(cppcoreguidelines-special-member-functions)

#ifndef REFCOUNTEDLIST_HPP
#define REFCOUNTEDLIST_HPP

template <typename T>
class RefCountedList;

template <typename T>
class RefCountedList<T*> {
public:
	RefCountedList();
	RefCountedList(const RefCountedList& other);
	~RefCountedList();

	RefCountedList& operator=(RefCountedList other);

	void push_front(T* content);
	void push_back(T* content);
	void swap(RefCountedList& other);
	T* find(T* content);
	void remove(T* content);
	void clear();

private:
	struct Node {
		Node(T* content, RefCountedList* parent);
		~Node();

		T* content;
		int refs;
		Node* next;
		Node* prev;
		RefCountedList* parent;
	};

	Node* _find_node(T* content);
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
