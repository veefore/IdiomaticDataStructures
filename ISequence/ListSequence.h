
#include "C:\Users\nolme\Repositories\vigilant-potato\Exception\Exception\IndexException.h"
#include "List.h"
#include "Sequence.h"
#include "ListSequenceIterator.h"

#ifndef __LISTSEQUENCE__H__
#define __LISTSEQUENCE__H__

using namespace std;

template <typename TElement>
class ListSequence : public Sequence<TElement> {
	
	List<TElement> *list;

	template <typename TElement>
	friend class SortedSequence;

public:

	ListSequence(int length = 0) : Sequence<TElement>(length), list(new List<TElement>(length)) {};

	ListSequence(List<TElement> *new_list) : Sequence<TElement>(new_list->get_size()), list(new_list) {};

	ListSequence(const Sequence<TElement> *seq) : Sequence<TElement>(0) {
		TElement *array = seq->GetArray();
		list = new List<TElement>;
		for (int i = 0; i < seq->getLength(); i++) {
			this->Append(array[i]);
		}
	}

	ListSequence(const ListSequence<TElement> &new_list) : Sequence<TElement>(new_list) {
		list = new List<TElement>(new_list);
	}

	~ListSequence() { delete list; }

	bool isSorted(bool (*lessThan)(const TElement &el1, const TElement &el2) = [](const TElement &el1, const TElement &el2) {
		return el1 < el2;
	});

	TElement Get(int index) const;

	TElement GetFirst() { return Get(0); }

	TElement GetLast() { return Get(this->Length - 1); }

	void Append(const TElement & item);

	void Prepend(const TElement & item);

	void InsertAt(const TElement & item, int index);

	void Remove(const TElement & item);

	Sequence<TElement> *GetSubsequence(int startIndex, int endIndex);

	void Set(const TElement &item, int index);

	void Swap(int i, int j);

	void RemoveFrom(int index);

	TElement *GetArray() const {
		return list->get_array();
	}

	void Print() const {
		list->print();
	}

	int UpperBound(const TElement &value, bool(*lessThan)(const TElement &el1, const TElement &el2) = [](const TElement *el1, const TElement &el2) {
		return el1 < el2;
	}) const;

	ListSequenceIterator<TElement> begin() {
		return ListSequenceIterator<TElement>(list->get_head());
	}

	ListSequenceIterator<TElement> end() {
		return ListSequenceIterator<TElement>(list->get_tail());
	}

};

template <typename TElement>
void ListSequence<TElement>::Append(const TElement &item) {
	list->add_node_at_end(item);
	this->Length++;
}

template <typename TElement>
void ListSequence<TElement>::Prepend(const TElement &item) {
	list->add_node(item);
	this->Length++;
}

template <typename TElement>
void ListSequence<TElement>::InsertAt(const TElement &item, int index) {
	if (index < 0 || index > this->Length)
		throw IndexException("Index passed to ListSequence<>::InsertAt() is out of boundaries.", index);
	if (index == this->Length) {
		this->Append(item);
	}
	else {
		list->add_node(item, index);
		this->Length++;
	}
}

template <typename TElement>
void ListSequence<TElement>::Set(const TElement &item, int index) {
	list->set_element(item, index);
}

template <typename TElement>
void ListSequence<TElement>::Remove(const TElement &item) {
	int index = list->search(item);
	if (index >= 0) {
		list->remove_node(index);
		this->Length--;
	}
}

template <typename TElement>
Sequence<TElement> *ListSequence<TElement>::GetSubsequence(int startIndex, int endIndex) {
	if (startIndex < 0 || startIndex >= this->Length)
		throw IndexException("StartIndex passed to GetSubsequence() is out of boundaries.", startIndex);
	if (endIndex < 0 || endIndex >= this->Length)
		throw IndexException("EndIndex passed to GetSubsequence() is out of boundaries.", endIndex);
	if (startIndex > endIndex)
		throw IndexException("startIndex is bigger than endIndex in function GetSubsequence().", 0);
	List<TElement> *new_list = list->get_sublist(startIndex, endIndex);
	ListSequence<TElement> *seq = new ListSequence<TElement>(new_list);
	return seq;
}

template <typename TElement>
TElement ListSequence<TElement>::Get(int index) const {
	if (index < 0 || index >= this->Length)
		throw IndexException("Index passed to Get() is out of boundaries.", index);
	return list->get_element(index);
}

template <typename TElement>
void ListSequence<TElement>::Swap(int i, int j) {
	TElement temp = list->get_element(i);
	list->set_element(list->get_element(j), i);
	list->set_element(temp, j);
}

template <typename TElement>
void ListSequence<TElement>::RemoveFrom(int index) {
	list->remove_node(index);
	this->Length--;
}

template <typename TElement>
bool ListSequence<TElement>::isSorted(bool (*lessThan)(const TElement &el1, const TElement &el2)) {
	return list->isSorted(lessThan);
}

template <typename TElement>
int ListSequence<TElement>::UpperBound(const TElement &value, bool(*lessThan)(const TElement &el1, const TElement &el2)) const {
	return list->upper_bound(value, lessThan);
}


#endif