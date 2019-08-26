#include "stdafx.h"
#include "ISorter.h"

#ifndef __BINARYINSERTIONSORT__H__
#define __BINARYINSERTIONSORT__H__

template <typename T>
class BinaryInsertionSort : public ISorter<T> {
public:

	void sort(int size, function<T(int)> get, function<void(T, int)> set, function<void(int, int)> swap,
		bool(*lessThan)(const T &value1, const T &value2) = ISorter<T>::lessThan) {
		
		for (int i = 1; i < size; i++) {
			T value = get(i);
			int itr = i - 1;
			int l = 0;
			int r = i;
			int mid = (l + r) / 2;
			while (l <= r) {
				mid = (l + r) / 2;
				T mid_value = get(mid);
				if (lessThan(value, mid_value))
					r = mid - 1;
				else if (value == mid_value)
					break;
				else 
					l = mid + 1;
			}
			if (!lessThan(value, get(mid)) && mid > 0)
				mid--;
			while (itr > mid) {
				set(get(itr), itr + 1);
				itr--;
			}
			set(value, itr);
		}
	}
};

#endif