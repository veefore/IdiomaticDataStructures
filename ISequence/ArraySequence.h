
#include "C:\Users\nolme\Repositories\vigilant-potato\Exception\Exception\IndexException.h"
#include "Sequence.h"
#include "ArrayList.h"
#include <functional>
#include <iostream>
#include "ArraySequenceIterator.h"

#ifndef __ARRAYSEQUENCE__H__
#define __ARRAYSEQUENCE__H__

using namespace std;

template <typename TElement>
class ArraySequence : public Sequence<TElement> {	
	ArrayList<TElement> *array;

	template <typename TElement>
	friend class SortedSequence;
public:

	ArraySequence(int length = 0) : Sequence<TElement>(length), array(new ArrayList<TElement>(length > 0 ? length : 1)) {};

	ArraySequence(const ArraySequence<TElement> &original_seq) : Sequence<TElement>(original_seq) {
		array = new ArrayList<TElement>(original_seq->GetArray());
	}

	ArraySequence(const Sequence<TElement> *seq) : Sequence<TElement>(*seq) {
		array = new ArrayList<TElement>(1);
		TElement *arr = seq->GetArray();
		for (int i = 0; i < seq->getLength(); i++) {
			this->Append(arr[i]);
		}
		this->Length = seq->getLength();
	}

	~ArraySequence() { delete array; }

	bool isSorted(bool (*lessThan)(const TElement &el1, const TElement &el2) = [](const TElement &el1, const TElement &el2) {
		return el1 < el2;
	});

	TElement Get(int index) const;

	TElement GetFirst() { return Get(0); }

	TElement GetLast() { return Get(this->Length - 1); }

	void Append(const TElement &item);

	void Prepend(const TElement &item);

	void InsertAt(const TElement &item, int index);

	void Remove(const TElement &item);

	Sequence<TElement> *GetSubsequence(int startIndex, int endIndex);

	void Set(const TElement &item, int index) ;

	void Swap(int i, int j);

	void RemoveFrom(int index);

	TElement *GetArray() const {
		return array->get_array();
	}

	void Print() const;

	int UpperBound(const TElement &value, bool(*lessThan)(const TElement &el1, const TElement &el2) = [](const TElement *el1, const TElement &el2) {
		return el1 < el2;
	}) const {
		return array->upper_bound(value, lessThan);
	}

	ArraySequenceIterator<TElement> begin() {
		return ArraySequenceIterator<TElement>(array, 0);
	}

	ArraySequenceIterator<TElement> end() {
		return ArraySequenceIterator<TElement>(array, this->getLength() - 1);
	}


};

template <typename TElement>
void ArraySequence<TElement>::Append(const TElement &item) {
	array->push_back(item);
	this->Length++;
}

template <typename TElement>
void ArraySequence<TElement>::Prepend(const TElement &item) {
	array->push_front(item);
	this->Length++;
}

template <typename TElement>
void ArraySequence<TElement>::InsertAt(const TElement &item, int index) {
	if (index < 0 || index > this->Length)
		throw IndexException("Index passed to InsertAt() is out of boundaries.", index);
	if (index == this->Length) {
		this->Append(item);
		return;
	}
	array->insert_at(index, item);
	this->Length++;
}

template <typename TElement>
void ArraySequence<TElement>::Set(const TElement &item, int index) {
	if (index < 0 || index >= this->Length)
		throw IndexException("Index passed to Set() is out of boundaries.", index);
	array->at(index) = item;
}

template <typename TElement>
void ArraySequence<TElement>::Remove(const TElement &item) {
	for (int i = 0; i < this->Length; i++) {
		if (array->at(i) == item) {
			array->remove(i);
			this->Length--;
			return;
		}
	}
}

template <typename TElement>
Sequence<TElement> *ArraySequence<TElement>::GetSubsequence(int startIndex, int endIndex) {
	if (startIndex < 0 || startIndex >= this->Length)
		throw IndexException("StartIndex passed to GetSubsequence() is out of boundaries.", startIndex);
	if (endIndex < 0 || endIndex >= this->Length)
		throw IndexException("EndIndex passed to GetSubsequence() is out of boundaries.", endIndex);
	if (startIndex > endIndex)
		throw IndexException("startIndex is bigger than endIndex in function GetSubsequence().", 0);
	ArraySequence<TElement> *seq = new ArraySequence<TElement>();
	for (int i = startIndex; i <= endIndex; i++)
		seq->Append(array->at(i));
	return seq;
}

template <typename TElement>
TElement ArraySequence<TElement>::Get(int index) const {
	if (index < 0 || index >= this->Length)
		throw IndexException("Index passed to Get() is out of boundaries.", index);
	return array->at(index);
}

template <typename TElement>
void ArraySequence<TElement>::Swap(int i, int j) {
	TElement temp = array->at(i);
	array->at(i) = array->at(j);
	array->at(j) = temp;
}

template <typename TElement>
void ArraySequence<TElement>::RemoveFrom(int index) {
	array->remove(index);
	this->Length--;
}

template <typename TElement>
bool ArraySequence<TElement>::isSorted(bool (*lessThan)(const TElement &el1, const TElement &el2)) {
	return array->isSorted(lessThan);
}

template <typename TElement>
void ArraySequence<TElement>::Print() const {
	for (int i = 0; i < this->Length; i++)
		cout << this->Get(i) << " ";
	cout << endl;
}



#endif