
#include <ctime>
#include <vector>
#include <functional>

#ifndef __SEQUENCE__H__
#define __SEQUENCE__H__

template <typename TElement>
class Sequence {
protected:
	int Length;

public:
	Sequence(int length = 0) : Length(length) {};

	Sequence(const Sequence<TElement> &original_seq) {
		this->Length = original_seq.getLength();
	}

	virtual bool isSorted(bool (*lessThan)(const TElement &el1, const TElement &el2) = [](const TElement &el1, const TElement &el2) {
		return el1 < el2;
	}) = 0;

	int getLength() const { return Length; }

	bool getIsEmpty() const { return Length == 0; }

	virtual TElement *GetArray() const = 0;

	virtual TElement Get(int index) const = 0 ;

	TElement GetFirst() const { return Get(0); }

	TElement GetLast() const { return Get(this->Length - 1); }

	virtual void Append(const TElement &item) = 0;

	virtual void Prepend(const TElement &item) = 0;

	virtual void InsertAt(const TElement &item, int index) = 0;

	virtual void Remove(const TElement &item) = 0;

	virtual Sequence<TElement> *GetSubsequence(int startIndex, int endIndex) = 0;

	/*virtual void FillWithRandom(int size, TElement max_value) {
		srand((unsigned)time(0));
		for (int i = 0; i < size; i++) {
			TElement value = rand();
			this->Append(value);
		}
	} */

	virtual void FillWithData(std::vector<TElement> &arr) {
		int size = arr.size();
		for (int i = 0; i < size; i++)
			this->Append(arr[i]);
	}

	virtual void FillWithData(TElement *arr, int size) {
		for (int i = 0; i < size; i++)
			this->Append(arr[i]);
	}

	virtual void Set(const TElement &item, int index) = 0;

	virtual void Swap(int i, int j) = 0;

	virtual void RemoveFrom(int index) = 0;

	virtual void Print() const = 0;

	virtual int UpperBound(const TElement &value, bool(*lessThan)(const TElement &el1, const TElement &el2) = [](const TElement *el1, const TElement &el2) {
		return el1 < el2;
	}) const = 0; // Avoid if seq isn't sorted; returns index of the first element bigger than value.

};

#endif
