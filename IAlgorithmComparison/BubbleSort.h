#include "stdafx.h"
#include "ISorter.h"

#ifndef __BUBBLESORT__H__
#define __BUBBLESORT__H__

template <typename T>
class BubbleSort : public ISorter<T> {
public:

	void sort(int size, function<T(int)> get, function<void(T, int)> set, function<void(int, int)> swap, 
		bool(*lessThan)(const T &value1, const T &value2) = ISorter<T>::lessThan) {
		
		bool flag = false;
		for (int j = size - 1; j > 0; j--) {
			int last_swapped = -1;
			for (int i = 0; i < j; i++) {
				if (lessThan(get(i + 1), get(i))) {
					swap(i + 1, i);
					last_swapped = i;
				}
			}
			if (last_swapped != -1) 
				j = last_swapped + 1;
			else
				break;
		}
	}

};


#endif