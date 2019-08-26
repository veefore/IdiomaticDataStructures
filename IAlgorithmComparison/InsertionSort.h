#include "stdafx.h"
#include "ISorter.h"

#ifndef __INSERTIONSORT__H__
#define __INSERTIONSORT__H__


template <typename T>
class InsertionSort : public ISorter<T> {
public:

	void sort(int size, function<T(int)> get, function<void(T, int)> set, function<void(int, int)> swap,
		bool(*lessThan)(const T &value1, const T &value2) = ISorter<T>::lessThan) {
		for (int i = 1; i < size; i++) {
			T value = get(i);
			int itr = i-1;
			while (itr >= 0 && lessThan(value, get(itr))) {
				set(get(itr), itr + 1);
				itr--;
			}
			set(value, itr+1);
		}
	}

};


#endif