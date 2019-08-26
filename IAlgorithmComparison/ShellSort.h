#include "stdafx.h"
#include "ISorter.h"

#ifndef __SHELLSORT__H__
#define __SHELLSORT__H__

template <typename T>
class ShellSort : public ISorter<T> {
	
	int (*iterate_gap)(int &gap, int k);

public:

	ShellSort(int (*iterate_gap)(int &gap, int k) = [](int &gap, int k = 1) {
		gap /= 2;
		return 1;
	}) : iterate_gap(iterate_gap) {}

	void sort(int size, function<T(int)> get, function<void(T, int)> set, function<void(int, int)> swap,
		bool(*lessThan)(const T &value1, const T &value2) = ISorter<T>::lessThan) {

		int k = 1;
		for (int gap = size / 2; gap > 0; k = iterate_gap(gap, k)) {
			for (int i = gap; i < size; i++) {
				T temp = get(i);
				int j = i;
				for (T value; j >= gap && lessThan(temp, (value = get(j-gap))); j -= gap)
					set(value, j);

				set(temp, j);
			}
		}
	}

};

#endif