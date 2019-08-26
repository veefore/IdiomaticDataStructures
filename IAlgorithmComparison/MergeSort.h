#include  "stdafx.h"
#include "ISorter.h"

#ifndef __MERGESORT__H__
#define __MERGESORT__H__

template <typename T>
class MergeSort : public ISorter<T> {

	void merge(int start, int end, function<T(int)> get, function<void(T, int)> set, bool(*lessThan)(const T &value1, const T &value2)) {
		int mid = (end + start) / 2;
		int lstart = start;
		int lend = mid;
		int rstart = mid + 1;
		int rend = end;

		T *arr = new T[end - start + 1];
		int lp = lstart, rp = rstart;
		int itr = 0;
		while (lp <= lend && rp <= rend) {
			T lvalue = get(lp);
			T rvalue = get(rp);
			if (lessThan(lvalue, rvalue)) {
				arr[itr] = lvalue;
				lp++;
			}
			else {
				arr[itr] = rvalue;
				rp++;
			}
			itr++;
		}
		while (lp <= lend)
			arr[itr++] = get(lp++);

		while (rp <= rend)
			arr[itr++] = get(rp++);

		for (int i = start; i <= end; i++)
			set(arr[i - start], i);
	}

	void mergesort(int start, int end, function<T(int)> get, function<void(T, int)> set, bool(*lessThan)(const T &value1, const T &value2)) {
		if (end - start <= 0)
			return;
		int mid = (end + start) / 2;
		mergesort(start, mid, get, set, lessThan);
		mergesort(mid + 1, end, get, set, lessThan);
		merge(start, end, get, set, lessThan);
	}
	

public:

	void sort(int size, function<T(int)> get, function<void(T, int)> set, function<void(int, int)> swap,
		bool(*lessThan)(const T &value1, const T &value2) = ISorter<T>::lessThan) {

		mergesort(0, size - 1, get, set, lessThan);
	
	
	
	
	}

};

#endif