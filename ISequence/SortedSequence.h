#include "Sequence.h"
#include "C:\Users\nolme\Repositories\vigilant-potato\Exception\Exception\IndexException.h"

#ifndef __SORTEDSEQUENCE__H__
#define __SORTEDSEQUENCE__H__

template <typename TElement>
class SortedSequence : public Sequence<TElement> {
private:
	Sequence<TElement> *seq;
	bool(*lessThan)(const TElement &el1, const TElement &el2);

	TElement GetFirst() {}
	TElement GetLast() {}
	void Append(const TElement &item) {}
	void Prepend(const TElement &item) {}
	void Set(const TElement &item, int index) {}
	void Swap(int i, int j) {}
	void InsertAt(const TElement &item, int index) {}

	void InsertAt(int index, const TElement &item) {
		seq->InsertAt(index, item);
	}

	bool isSorted(bool(*lessThan)(const TElement &el1, const TElement &el2) = [](const TElement &el1, const TElement &el2) {
		return el1 < el2;
	}) {
		return true; 
	}

public:
	SortedSequence(Sequence<TElement> *seq, bool(*lessThan)(const TElement &el1, const TElement &el2) = [](const TElement &el1, const TElement &el2) {
		return el1 < el2;
	}) : seq(seq), lessThan(lessThan) {}

	~SortedSequence() {
		delete seq;
	}

	int getLength() const { return seq->getLength(); }

	bool getIsEmpty() const { return seq->getLength() == 0; }

	TElement *GetArray() const { return seq->GetArray(); }

	void Add(const TElement &element); 

	TElement Get(int index) const { return seq->Get(index);  }

	void Remove(const TElement &item); 

	Sequence<TElement> *GetSubsequence(int startIndex, int endIndex) {
		return seq->GetSubsequence(startIndex, endIndex);
	}

	/*virtual void FillWithRandom(int size, TElement max_value) {
		seq->FillWithRandom(size, max_value);
	}*/

	virtual void FillWithData(std::vector<TElement> &arr) {
		seq->FillWithData(arr);
	}

	virtual void FillWithData(TElement *arr, int size) {
		seq->FillWithData(arr, size);
	}

	void RemoveFrom(int index);

	void Print() const {
		seq->Print();
	}

	int IndexOf(const TElement &element);

	int UpperBound(const TElement &value, bool(*lessThan)(const TElement &el1, const TElement &el2) = [](const TElement *el1, const TElement &el2) {
		return el1 < el2;
	}) const; //might be reworked to return an iterator
};

template <typename TElement>
void SortedSequence<TElement>::RemoveFrom(int index) {
	if (index < 0 || index >= this->getLength())
		throw IndexException("Index out of array boundaries. SortedSequence<TElement>::RemoveFrom(int).", index);
	seq->RemoveFrom(index);
}

template <typename TElement>
void SortedSequence<TElement>::Add(const TElement &element) {
	int index = seq->UpperBound(element, lessThan);
	seq->InsertAt(element, index);
}

template <typename TElement>
int SortedSequence<TElement>::IndexOf(const TElement &element) {
	TElement *array = seq->GetArray();
	int size = seq->getLength();
	int left = 0;
	int right = size - 1;
	int mid = (left + right) / 2;

	while (left < right) {
		mid = (left + right) / 2;
		if (lessThan(array[mid], element))
			left = mid + 1;
		else if (lessThan(element, array[mid]))
			right = mid - 1;
		else
			return mid;
	}
	if (!lessThan(array[right], element) && !lessThan(element, array[right]))
		return right;
	else
		return -1;
}

template <typename TElement>
void SortedSequence<TElement>::Remove(const TElement &item) {
	int index = this->IndexOf(item);
	if (index == -1)
		return;
	this->RemoveFrom(index);

}

template <typename TElement> 
int SortedSequence<TElement>::UpperBound(const TElement &value, bool(*lessThan)(const TElement &el1, const TElement &el2)) const {
	return seq->UpperBound(value, lessThan);
}

#endif
