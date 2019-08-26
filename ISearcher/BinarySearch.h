#include "ISearcher.h"
#include "C:\Users\nolme\Repositories\vigilant-potato\Exception\Exception\BadExecutionException.h"
#include "C:\Users\nolme\Repositories\vigilant-potato\Exception\Exception\InvalidArgumentException.h"
#include <functional>



#ifndef __BINARYSEARCH__H__
#define __BINARYSEARCH__H__

template <typename TObject>
class Sequence;

int fib_number(unsigned int n) {
	if (n == 0)
		return 0;
	if (n == 1)
		return 1;
	return fib_number(n - 1) + fib_number(n - 2);
}

template <typename TObject>
class BinarySearch : public ISearcher<TObject> {
	std::function<TObject(int)> get; //assumes that indexation starts at 0
	std::function<bool(const TObject &el1, const TObject &el2)> lessThan;
	std::function<bool(const TObject &el1, const TObject &el2)> areEqual;
	int size;

public:
	BinarySearch() : ISearcher<TObject>(), size(-1) {}

	BinarySearch(int size, std::function<TObject(int)> get,
		std::function<bool(const TObject &el1, const TObject &el2)> areEqual = [](const TObject &el1, const TObject &el2) {
		return el1 == el2;
	},
		std::function<bool(const TObject &el1, const TObject &el2)> lessThan = [](const TObject &el1, const TObject &el2) {
		return el1 < el2;
	}) : ISearcher<TObject>(), size(size), get(get), lessThan(lessThan), areEqual(areEqual) {
		if (size < 0)
			throw InvalidArgumentException("InvalidArgumentException thrown at BinarySearch::BinarySearch(int, get(), areEqual(), lessThan()).",
				"Size argument passed is smaller than zero.");
	} //default initialization is bad because it makes it necessary to define == and <

	inline void SetGet(std::function<TObject(int)> get) {
		this->get = get;
	}

	inline int GetSize() const {
		return size;
	}

	inline void SetSize(int size) {
		this->size = size;
	}

	inline void SetAreEqual(std::function<bool(const TObject &el1, const TObject &el2)> areEqual) {
		this->areEqual = areEqual;
	}

	inline void SetLessThan(std::function<bool(const TObject &el1, const TObject &el2)> lessThan) {
		this->lessThan = lessThan;
	}

	bool IsInitialized() const; //is init if all of the functions are set and size != -1

	int Search(const TObject &value) const {
		return this->Search(value, 1, 1);
	}

	int Search(const TObject &value, unsigned int proportion_el1, unsigned int proportion_el2) const;

	int Search(const TObject &value, unsigned int fibonacci_number) const {
		return this->Search(value, fib_number(fibonacci_number), fib_number(fibonacci_number + 1)); //TODO: optimazation
	} //fib[0] = 0, fib[1] = fib[2] = 1

};


template <typename TObject>
int BinarySearch<TObject>::Search(const TObject &value, unsigned int proportion_el1, unsigned int proportion_el2) const {
	if (!this->IsInitialized())
		throw BadExecutionException("BadExecutionException thrown from BinarySearch<TObject>::Search(const TObject &, uint prop1, uint prop2).",
			"BinarySearch object isn't initialized properly. Set the get(), areEqual(), lessThan() functions through corresponding methods (SetFuncName()).\nInitialization status can be checked through isInitialized() function.");

	if (proportion_el1 == 0 || proportion_el2 == 0) {
		throw InvalidArgumentException("InvalidArgumentException thrown at BinarySearch<TObject>::Search(const TObject &, uint prop1, uint prop2).", 
			"One or both of the uint proportion parameters passed is or are equal to zero.");
	}


	int left = 0;
	int right = this->size - 1;
	int partition = left + (right - left) * proportion_el1 / (proportion_el1 + proportion_el2);
	
	while (left < right) {
		partition = left + (right - left) * proportion_el1 / (proportion_el1 + proportion_el2);
		TObject value_partition = get(partition);
		if (areEqual(value_partition, value))
			return partition;
		else if (lessThan(value_partition, value))
			left = partition + 1;
		else
			right = partition - 1;
	}

	if (areEqual(get(right), value))
		return right;
	else
		return -1;

}


template <typename TObject>
bool BinarySearch<TObject>::IsInitialized() const {
	bool flag = true;
	if (size == -1)
		flag = false;
	if (lessThan == nullptr)
		flag = false;
	if (areEqual == nullptr)
		flag = false;
	if (get == nullptr)
		flag = false;
	return flag;
}
#endif
