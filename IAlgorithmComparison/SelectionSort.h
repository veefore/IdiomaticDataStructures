#include "stdafx.h"
#include "ISorter.h"

#ifndef __SELECTIONSORT__H__
#define __SELECTIONSORT__H__

template <typename T>
class SelectionSort : public ISorter<T> {
public:

	void sort(int size, function<T(int)> get, function<void(T, int)> set, function<void(int, int)> swap,
		bool(*lessThan)(const T &value1, const T &value2) = ISorter<T>::lessThan) {
		//T *arr = new T[size];
		//for (int i = 0; i < size; i++)
			//arr[i] = get(i);

		for (int i = 0; i < size-1; i++) {
			int pos = i;
			for (int j = i + 1; j < size; j++) 
				if (lessThan(get(j), get(pos)))
					pos = j;
			
			if (pos != i) {
				swap(pos, i);
				//int temp = arr[pos];
				//arr[pos] = arr[i];
				//arr[i] = temp;
			}
		}

		//delete[] arr;
	}
};

#endif