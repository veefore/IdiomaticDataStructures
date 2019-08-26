#include "SequenceIterator.h"
#include "ArrayList.h"

#ifndef __ARRAYSEQUENCEITERATOR__H__
#define __ARRAYSEQUENCEITERATOR__H__


template <typename TElement>
class ArraySequenceIterator : public SequenceIterator<TElement, ArraySequenceIterator> {
	ArrayList<TElement> *arr;
	int index;

public:
	ArraySequenceIterator(ArrayList<TElement> *arr, int index);

	ArraySequenceIterator(const ArraySequenceIterator<TElement> &itr);
	
	bool operator==(const ArraySequenceIterator &itr) const;

	TElement &operator*();

	ArraySequenceIterator<TElement> &operator+(int addend);

	ArraySequenceIterator<TElement> &operator-(int subtrahend);

	int operator-(const ArraySequenceIterator<TElement> &itr);

	bool operator<(const ArraySequenceIterator<TElement> &itr) const;

	bool operator>(const ArraySequenceIterator<TElement> &itr) const;
	//
	ArraySequenceIterator<TElement> &operator++();

	ArraySequenceIterator<TElement> operator++(int);

	ArraySequenceIterator<TElement> &operator--();

	ArraySequenceIterator<TElement> operator--(int);

	bool operator<=(const ArraySequenceIterator<TElement> &itr) const;

	bool operator>=(const ArraySequenceIterator<TElement> &itr) const;

	ArraySequenceIterator<TElement> &operator+=(int addend);

	ArraySequenceIterator<TElement> &operator-=(int subtrahend);

	bool operator!=(const ArraySequenceIterator<TElement> &itr) const;

	TElement &operator[](int offset);

	//ArraySequenceIterator<TElement> &operator= (const ArraySequenceIterator<TElement> &itr);
};

template <typename TElement>
ArraySequenceIterator<TElement>::ArraySequenceIterator(ArrayList<TElement> *arr, int index) {
	this->index = index;
	this->arr = arr;
}

template <typename TElement>
ArraySequenceIterator<TElement>::ArraySequenceIterator(const ArraySequenceIterator<TElement> &itr) {
	arr = itr.arr;
	index = itr.index;
}

template <typename TElement>
bool ArraySequenceIterator<TElement>::operator==(const ArraySequenceIterator<TElement> &itr) const {
	return (this->arr == itr.arr && this->index == itr.index);
}

template <typename TElement>
TElement &ArraySequenceIterator<TElement>::operator*() {
	return arr->at(index);
}

template <typename TElement>
ArraySequenceIterator<TElement> &ArraySequenceIterator<TElement>::operator+(int addend) {
	index += addend;
	return *this;
}

template <typename TElement>
ArraySequenceIterator<TElement> &ArraySequenceIterator<TElement>::operator-(int subtrahend) {
	index -= subtrahend;
	return *this;
}

template <typename TElement>
int ArraySequenceIterator<TElement>::operator-(const ArraySequenceIterator<TElement> &itr) {
	int value = itr.index - this->index;
	return value >= 0 ? value : -1;
}

template <typename TElement>
bool ArraySequenceIterator<TElement>::operator<(const ArraySequenceIterator<TElement> &itr) const {
	return (this->index < itr.index);
}

template <typename TElement>
bool ArraySequenceIterator<TElement>::operator>(const ArraySequenceIterator<TElement> &itr) const {
	return (this->index > itr.index);
}


template <typename TElement>
ArraySequenceIterator<TElement> &operator+(int addend, ArraySequenceIterator<TElement> &itr) {
	return itr + addend;
}

template <typename TElement>
int operator-(ArraySequenceIterator<TElement> &itr1, ArraySequenceIterator<TElement> &itr2) {
	return itr1 - itr2;
}

template <typename TElement>
ArraySequenceIterator<TElement> &ArraySequenceIterator<TElement>::operator++() {
	return this->operator+(1);
}

template <typename TElement>
ArraySequenceIterator<TElement> ArraySequenceIterator<TElement>::operator++(int) {
	ArraySequenceIterator<TElement> temp(*this);
	this->operator++();
	return temp;
}

template <typename TElement>
ArraySequenceIterator<TElement> &ArraySequenceIterator<TElement>::operator--() {
	return this->operator-(1);
}

template <typename TElement>
ArraySequenceIterator<TElement> ArraySequenceIterator<TElement>::operator--(int) {
	ArraySequenceIterator<TElement> temp(*this);
	this->operator--();
	return temp;
}

template <typename TElement>
bool ArraySequenceIterator<TElement>::operator!=(const ArraySequenceIterator<TElement> &itr) const {
	return !(this->operator==(itr));
}

template <typename TElement>
bool ArraySequenceIterator<TElement>::operator<=(const ArraySequenceIterator<TElement> &itr) const {
	return (this->operator==(itr) || this->operator<(itr));
}

template <typename TElement>
bool ArraySequenceIterator<TElement>::operator>=(const ArraySequenceIterator<TElement> &itr) const {
	return (this->operator==(itr) || this->operator>(itr));
}

template <typename TElement>
ArraySequenceIterator<TElement> &ArraySequenceIterator<TElement>::operator+=(int addend) {
	this->operator+(addend);
	return *this;
}

template <typename TElement>
ArraySequenceIterator<TElement> &ArraySequenceIterator<TElement>::operator-=(int subtrahend) {
	this->operator-(subtrahend);
	return *this;
}

template <typename TElement>
TElement &ArraySequenceIterator<TElement>::operator[](int offset) {
	ArraySequenceIterator<TElement> temp(*this);
	temp += offset;
	return *temp;
}

//template <typename TElement>
//ArraySequenceIterator<TElement> &ArraySequenceIterator<TElement>::operator= (const ArraySequenceIterator<TElement> &itr) {
//	this->arr = itr.arr;
//	this->index = itr.index;
//}

#endif
