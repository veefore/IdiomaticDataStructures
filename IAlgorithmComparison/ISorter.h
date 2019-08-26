#include "stdafx.h"
#include "C:\Users\nolme\Repositories\laboratory_projects\Semester_3\lab1\lab1\Sequence.h"
#include <string>
#include <functional>
#include <vector>


#ifndef __ISORTER__H__
#define __ISORTER__H__


using namespace std;


template <typename T>
class ISorter {
	
protected:

	static bool lessThan(const T &value1, const T &value2) {
		return value1 < value2;
	}	
	
	static function<T(int)> seq_get(Sequence<T> *seq) {
		return std::bind(&Sequence<T>::Get, seq, placeholders::_1);
	}

	static function<void(T, int)> seq_set(Sequence<T> *seq) {
		return std::bind(&Sequence<T>::Set, seq, placeholders::_1, placeholders::_2);
	}

	static function<void(int, int)> seq_swap(Sequence<T> *seq) {
		return std::bind(&Sequence<T>::Swap, seq, placeholders::_1, placeholders::_2);
	}

	static function<T(int)> vec_get(vector<int> *vec) {
		return [vec](int index) {
			return (*vec)[index];
		};
	}

	static function<void(T, int)> vec_set(vector<T> *vec) {
		return bind([vec](T value, int index) {
			(*vec)[index] = value;
		}, placeholders::_1, placeholders::_2);
	}
	
	static function<void(int, int)> vec_swap(vector<T> *vec) {
		return [vec](int i, int j) {
			T temp = (*vec)[i];
			(*vec)[i] = (*vec)[j];
			(*vec)[j] = temp;
		};
	}

	static function<T(int)> arr_get(int arr[]) {
		return [arr](int index) {
			return arr[index];
		};
	}

	static function<void(T, int)> arr_set(int arr[]) {
		return [arr](T value, int index) {
			arr[index] = value;
		};
	}

	static function<void(int, int)> arr_swap(int arr[]) {
		return [arr](int i, int j) {
			T temp = arr[i];
			arr[i] = arr[j];
			arr[j] = temp;
		};
	}

public:
	virtual void sort(int size, function<T(int)> get, function<void(T, int)> set, function<void(int, int)> swap,
		bool(*lessThan)(const T &value1, const T &value2) = ISorter<T>::lessThan) = 0;

	virtual Sequence<T> *Sort(Sequence<T> *seq, bool(*lessThan)(const T &value1, const T &value2) = ISorter<T>::lessThan) {

		sort(seq->getLength(), this->seq_get(seq), this->seq_set(seq), this->seq_swap(seq), lessThan);

		return seq;
	}

	virtual T *Sort(T arr[], int size, bool(*lessThan)(const T &value1, const T &value2) = ISorter<T>::lessThan) {

		sort(size, this->arr_get(arr), this->arr_set(arr), this->arr_swap(arr), lessThan);

		return arr;
	}

	virtual vector<T> *Sort(vector<T> *vec, bool(*lessThan)(const T &value1, const T &value2) = ISorter<T>::lessThan) {

		sort((int)vec->size(), this->vec_get(vec), this->vec_set(vec), this->vec_swap(vec), lessThan);
		
		return vec;
	}

};

#endif