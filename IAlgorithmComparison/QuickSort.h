#include "stdafx.h"
#include "ISorter.h"

#ifndef __QUICKSORT__H__
#define __QUICKSORT__H__

template <typename T>
class QuickSort : public ISorter<T> {

	void quicksort(int start, int end, function<T(int)> get, function<void(T, int)> set, function<void(int, int)> swap,
		bool(*lessThan)(const T &value1, const T &value2)) {
		
		if (start < 0 || start >= end)
			return;
		
		T pivot = get((start + end) / 2);
		int lp = start;
		int rp = end;
		while (lp <= rp) {
			while (lessThan(get(lp), pivot))
				lp++;

			while (lessThan(pivot, get(rp)))
				rp--;
			
			if (lp <= rp) {
				swap(lp, rp);
				lp++;
				rp--;
			}
		}
		
		quicksort(start, lp-1, get, set, swap, lessThan);
		quicksort(lp, end, get, set, swap, lessThan);
	}

public:

	void sort(int size, function<T(int)> get, function<void(T, int)> set, function<void(int, int)> swap,
		bool(*lessThan)(const T &value1, const T &value2) = ISorter<T>::lessThan) {

		quicksort(0, size - 1, get, set, swap, lessThan);
	}

};


#endif __QUICKSORT__H__
