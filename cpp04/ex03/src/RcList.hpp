// NOLINTBEGIN(cppcoreguidelines-special-member-functions)

#ifndef RCLIST_HPP
#define RCLIST_HPP

#include <cstddef>

template <typename T>
class RcList;

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
	size_t size() const;
	void forget(T* content);
	void remove(T* content);
	void clear();

private:
	struct Node {
		Node(T* content_, RcList* parent_);
		~Node();

		T* content;
		size_t refs;
		Node* next;
		Node* prev;
		RcList* parent;
	};

	static void _drop_node(Node* node);

	Node* _find_node(const T* content) const;
	bool _increase_ref(const T* content);
	bool _decrease_ref(T* content);

	Node* _head;
	Node* _tail;
	size_t _size;
};

#ifndef RCLIST_TPP
#include "RcList.tpp"
#endif

#endif

// NOLINTEND(cppcoreguidelines-special-member-functions)
