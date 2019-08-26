#include "stdafx.h"
#include "ISorter.h"

#ifndef __SHAKERSORT__H__
#define __SHAKERSORT__H__

template <typename T>
class ShakerSort : public ISorter<T> {
public:

	void sort(int size, function<T(int)> get, function<void(T, int)> set, function<void(int, int)> swap,
		bool(*lessThan)(const T &value1, const T &value2) = ISorter<T>::lessThan) {

		int left_bound = 0;
		int right_bound = size - 1;
		int last_swap = 0;
		while (true) {
			last_swap = -1;
			for (int i = left_bound; i <= right_bound - 1; i++) 
				if (lessThan(get(i + 1), get(i))) {
					swap(i + 1, i);
					last_swap = i;
				}
			if (last_swap != -1) 
				right_bound = last_swap;
			else 
				break;

			last_swap = -1;
			for (int i = right_bound-1; i >= left_bound; i--) 
				if (lessThan(get(i + 1), get(i))) {
					swap(i + 1, i);
					last_swap = i + 1;
				}
			if (last_swap != -1)
				left_bound = last_swap;
			else
				break;
		}
	}
	

};



#endif 