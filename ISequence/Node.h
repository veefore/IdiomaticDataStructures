


#ifndef __NODE__H__
#define __NODE__H__

template <class T>
class Node {
	T *element;
	Node<T> *prev, *next;


public:
	Node(Node<T> *prev = nullptr, const T &elem = T(0), Node<T> *next = nullptr);

	Node(const T &elem);

	~Node();

	Node<T> *get_prev(const int &j = int(0));

	Node<T> *get_next(const int &j = int(0));

	inline const T *get_element() const;

	inline void set_prev(Node<T> *prev);

	inline void set_next(Node<T> *next);

	inline void set_element(const T &element);
};

template <class T>
Node<T>::Node(const T &elem) : element(new T(elem)), prev(0), next(0) {}

template <class T>
Node<T>::~Node() {
	delete element;
}

template <class T>
Node<T>::Node(Node<T> *prev, const T &elem, Node<T> *next) : element(new T(elem)) {
	this->prev = prev;
	this->next = next;
}

template <class T>
Node<T> *Node<T>::get_prev(const int &j) {
	if (j == -1) return this;
	Node<T> *node = this->prev;
	for (int i = 0; i < j; i++)
		node = node->prev;
	return node;
}

template <class T>
Node<T> *Node<T>::get_next(const int &j) {
	if (j == -1) return this;
	Node<T> *node = this->next;
	for (int i = 0; i < j; i++)
		node = node->next;
	return node;
}

template <class T>
inline const T *Node<T>::get_element() const {
	return this->element;
}

template <class T>
inline void Node<T>::set_prev(Node<T> *prev) {
	this->prev = prev;
}

template <class T>
inline void Node<T>::set_next(Node<T> *next) {
	this->next = next;
}

template <class T>
inline void Node<T>::set_element(const T &element) {
	*this->element = element;
}

#endif