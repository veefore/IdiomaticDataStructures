#include "SequenceIterator.h"
#include "List.h"

#ifndef __LISTSEQUENCEITERATOR__H__
#define __LISTSEQUENCEITERATOR__H__


template <typename TElement>
class ListSequenceIterator : public SequenceIterator<TElement, ListSequenceIterator> {
	Node<TElement> *cur_node;

public:
	ListSequenceIterator(Node<TElement> *node);;

	ListSequenceIterator(const ListSequenceIterator<TElement> &itr);

	bool operator==(const ListSequenceIterator &itr) const;

	TElement &operator*();

	ListSequenceIterator<TElement> &operator+(int addend);

	ListSequenceIterator<TElement> &operator-(int subtrahend);

	int operator-(const ListSequenceIterator<TElement> &itr);

	bool operator<(const ListSequenceIterator<TElement> &itr) const;

	bool operator>(const ListSequenceIterator<TElement> &itr) const;

	ListSequenceIterator<TElement> &operator++();

	ListSequenceIterator<TElement> operator++(int);

	ListSequenceIterator<TElement> &operator--();

	ListSequenceIterator<TElement> operator--(int);

	bool operator<=(const ListSequenceIterator<TElement> &itr) const;

	bool operator>=(const ListSequenceIterator<TElement> &itr) const;

	ListSequenceIterator<TElement> &operator+=(int addend);

	ListSequenceIterator<TElement> &operator-=(int subtrahend);

	bool operator!=(const ListSequenceIterator<TElement> &itr) const;

	TElement &operator[](int offset);

	//ListSequenceIterator<TElement> &ListSequenceIterator<TElement>::operator= (const ListSequenceIterator<TElement> &itr);

};

template <typename TElement>
ListSequenceIterator<TElement>::ListSequenceIterator(Node<TElement> *node) {
	this->cur_node = node;
}

template <typename TElement>
ListSequenceIterator<TElement>::ListSequenceIterator(const ListSequenceIterator<TElement> &itr) {
	this->cur_node = itr.cur_node;
}

template <typename TElement>
bool ListSequenceIterator<TElement>::operator==(const ListSequenceIterator<TElement> &itr) const {
	return (this->cur_node == itr.cur_node);
}

template <typename TElement>
TElement &ListSequenceIterator<TElement>::operator*() {
	return const_cast<TElement &>(*cur_node->get_element());
}

template <typename TElement>
ListSequenceIterator<TElement> &ListSequenceIterator<TElement>::operator+(int addend) {
	cur_node = cur_node->get_prev(addend - 1);
	return *this;
}

template <typename TElement>
ListSequenceIterator<TElement> &ListSequenceIterator<TElement>::operator-(int subtrahend) {
	cur_node->get_next(subtrahend - 1);
	return *this;
}

template <typename TElement>
int ListSequenceIterator<TElement>::operator-(const ListSequenceIterator<TElement> &itr) {
	int counter = 0;
	Node<TElement> *node1, *node2;
	node1 = cur_node;
	node2 = itr.cur_node;
	while (node1 != node2 && node1 != nullptr) {
		node1 = node1->get_next();
		counter++;
	}
	if (node1 == nullptr || counter < 0)
		return -1;
	return counter;
}

template <typename TElement>
bool ListSequenceIterator<TElement>::operator<(const ListSequenceIterator<TElement> &itr) const {
	if (this->cur_node == itr.cur_node || itr.cur_node == nullptr || this->cur_node == nullptr)
		return false; 

	Node<TElement> *node1, *node2;
	node1 = cur_node;
	node2 = itr.cur_node;
	while (node1 != node2 && node2 != nullptr)
		node2 = node2->get_next();
	if (node2 == node1)
		return true;
	return false;
}

template <typename TElement>
bool ListSequenceIterator<TElement>::operator>(const ListSequenceIterator<TElement> &itr) const {
	return itr < (*this);
}


template <typename TElement>
ListSequenceIterator<TElement> &operator+(int addend, ListSequenceIterator<TElement> &itr) {
	return itr + addend;
}

template <typename TElement>
int operator-(ListSequenceIterator<TElement> &itr1, ListSequenceIterator<TElement> &itr2) {
	return itr1 - itr2;
}


template <typename TElement>
ListSequenceIterator<TElement> &ListSequenceIterator<TElement>::operator++() {
	return this->operator+(1);
}

template <typename TElement>
ListSequenceIterator<TElement> ListSequenceIterator<TElement>::operator++(int) {
	ListSequenceIterator<TElement> temp(*this);
	this->operator++();
	return temp;
}

template <typename TElement>
ListSequenceIterator<TElement> &ListSequenceIterator<TElement>::operator--() {
	return this->operator-(1);
}

template <typename TElement>
ListSequenceIterator<TElement> ListSequenceIterator<TElement>::operator--(int) {
	ListSequenceIterator<TElement> temp(*this);
	this->operator--();
	return temp;
}

template <typename TElement>
bool ListSequenceIterator<TElement>::operator!=(const ListSequenceIterator<TElement> &itr) const {
	return !(this->operator==(itr));
}

template <typename TElement>
bool ListSequenceIterator<TElement>::operator<=(const ListSequenceIterator<TElement> &itr) const {
	return (this->operator==(itr) || this->operator<(itr));
}

template <typename TElement>
bool ListSequenceIterator<TElement>::operator>=(const ListSequenceIterator<TElement> &itr) const {
	return (this->operator==(itr) || this->operator>(itr));
}

template <typename TElement>
ListSequenceIterator<TElement> &ListSequenceIterator<TElement>::operator+=(int addend) {
	this->operator+(addend);
	return *this;
}

template <typename TElement>
ListSequenceIterator<TElement> &ListSequenceIterator<TElement>::operator-=(int subtrahend) {
	this->operator-(subtrahend);
	return *this;
}

template <typename TElement>
TElement &ListSequenceIterator<TElement>::operator[](int offset) {
	ListSequenceIterator<TElement> temp(*this);
	temp += offset;
	return *temp;
}

//template <typename TElement>
//ListSequenceIterator<TElement> &ListSequenceIterator<TElement>::operator= (const ListSequenceIterator<TElement> &itr) {
//	this.cur_node = itr.cur_node;
//}

#endif