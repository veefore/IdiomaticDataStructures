
#include "Node.h"
#include <iostream>

#ifndef __LIST__H__
#define __LIST__H__


template <class T>
class List {
	Node<T> *head, *tail;
	int size;

public:
	List(const int &size = int(0));

	List(const List<T> &list);

	~List();

	void add_node(const T &element = T(0), const int &index = int(0));

	void remove_node(const int &index = int(0));

	T get_element(const int &index = int(0)) const;

	void set_element(const T &element, const int &index);

	inline int get_size() const;

	int search(const T &x) const;

	void add_node_at_end(const T &element);

	List<T> *get_sublist(int start, int end);

	bool isSorted(bool (*lessThan)(const T &el1, const T &el2) = [](const T &el1, const T &el2) {
		return el1 < el2;
	});

	T *get_array() {
		if (size == 0) return nullptr;
		T *arr = new T[size];
		Node<T> *cur = head;
		for (int i = 0; i < size; i++) {
			arr[i] = *cur->get_element();
			cur = cur->get_prev();
		}
		return arr;
	}

	void print() const {
		Node<T> *cur = head;
		while (cur != nullptr) {
			cout << *cur->get_element() << " ";
			cur = cur->get_prev();
		}
		cout << endl;
	}

	int upper_bound(const T &value, bool(*lessThan)(const T &el1, const T &el2) = [](const T &el1, const T &el2) {
		return el1 < el2;
	}) const;

	inline Node<T> *get_head() {
		return this->head;
	}

	inline Node<T> *get_tail() {
		return this->tail;
	}
};


template <class T>
List<T> *List<T>::get_sublist(int start, int end) {
	if (start < 0 || start >= size)
		throw IndexException("startIndex passed to List<>::get_sublist() is out of boundaries.", start);
	if (end < 0 || end >= size)
		throw IndexException("endIndex passed to List<>::get_sublist() is out of boundaries.", end);
	if (start > end)
		throw IndexException("startIndex is bigger than endIndex passed to List<>::get_sublist().", 0);
	List<T> *new_list = new List<T>();
	Node<T> *current = head->get_prev(start - 1);
	new_list->add_node(*current->get_element());
	for (int i = start + 1; i <= end; i++) {
		current = current->get_prev();
		new_list->add_node_at_end(*current->get_element());
	}
	return new_list;

}

template <class T>
bool List<T>::isSorted(bool(*lessThan)(const T &el1, const T &el2)) {
	Node<T> *cur = head;
	bool sorted = true;
	while (cur->get_next() != nullptr) {
		if (lessThan(*cur->get_next()->get_element(), *cur->get_element())) {
			sorted = false;
			break;
		}
		cur = cur->get_next();
	}
	return sorted;
}


template <class T>
List<T>::List(const int &size) {
	if (size < 0)
		throw "List<>::List() size parameter is less than 0";
	for (int i = 0; i < size; i++) {
		this->add_node();
	}
}

template <class T>
List<T>::List(const List<T> &list) {
	List(list.get_size());
	for (int i = 0; i < size; i++) {
		this->set_element(list->get_element(i), i);
	}
}

template <class T>
List<T>::~List() {
	if (size > 1) {
		Node<T> *current = head->get_prev();
		while (size > 2) {
			delete current->get_next();
			current = current->get_prev();
			size--;
		}
		delete current->get_next();
		delete current;
		return;
	}
	else if (tail != nullptr) delete head;
}

template <class T>
int List<T>::search(const T &x) const {
	Node<T> *node = head;
	if (node == nullptr) return -1;
	if (*node->get_element() == x) return 0;

	for (int i = 1; i < size; i++) {
		node = node->get_prev();
		if (node == nullptr) return -1;
		if (*node->get_element() == x) return i;	
	}
	return -1;
}

template <class T>
void List<T>::add_node(const T &element, const int &index) {
	
	if (index == 0) {
		if (size == 0) {
			head = new Node<T>((Node<T> *) nullptr, element);
			tail = head;
		}
		else {
			head->set_next(new Node<T>(head, element));
			head = head->get_next();
		}
	}
	else {
		Node<T> *current = new Node<T>(element);
		current->set_prev(head->get_prev(index - 1));
		current->set_next(current->get_prev()->get_next());
		current->get_next()->set_prev(current);
		current->get_prev()->set_next(current);
		if (current->get_next() == nullptr)
			head = current;
	}
	size++;
}

template <class T>
void List<T>::add_node_at_end(const T &element) {
	Node<T> *current = new Node<T>(element);
	current->set_next(tail);
	if (size > 0) {
		tail->set_prev(current);
	}
	else {
		head = current;
	}
	tail = current;
	size++;
}

template <class T>
int List<T>::get_size() const { //&
	return size; //&
}

template <class T>
void List<T>::remove_node(const int &index) {
	if (index < 0 || index >= size)
		throw IndexException("Index passed to List<>::remove_node() is out of boundaries.", index);
	Node<T> *current = head->get_prev(index - 1);
	if (current->get_prev() != nullptr)
		current->get_prev()->set_next(current->get_next());
	if (current->get_next() != nullptr)
		current->get_next()->set_prev(current->get_prev());
	if (current == head) head = current->get_prev();
	if (current == tail) tail = current->get_next();
	delete current;
	size--;
}

template <class T>
T List<T>::get_element(const int &index) const {
	if (index < 0 || index >= size)
		throw IndexException("Index passed to List<>::get_element() is out of boundaries.", index);
	return *(head->get_prev(index - 1)->get_element());
}

template <class T>
void List<T>::set_element(const T &element, const int &index) {
	if (index < 0 || index >= size)
		throw IndexException("Index passed to List<>::set_element() is out of boundaries.", index);
	head->get_prev(index - 1)->set_element(element);
}

template <class T>
int List<T>::upper_bound(const T &value, bool(*lessThan)(const T &el1, const T &el2)) const {
	Node<T> *cur = head;
	int i = 0;
	while (cur != nullptr) {
		if (lessThan(value, *cur->get_element()))
			break;
		i++;
		cur = cur->get_prev();
	}
	return i;
}

#endif