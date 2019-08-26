

#ifndef __ARRAYLIST__H__
#define __ARRAYLIST__H__

template <typename TElement>
class ArrayList {

	TElement *array;

	int size, capacity;

	void reallocate(int new_capacity = -1) {
		if (new_capacity == -1)
			new_capacity = 2 * capacity;
		capacity = new_capacity;
		TElement *new_array = new TElement[capacity];
		for (int i = 0; i < size; i++)
			new_array[i] = array[i];
		delete[] array;
		array = new_array;
	}

public:
	
	ArrayList(int capacity = 1) : size(0), capacity(capacity), array(new TElement[capacity]) {}

	ArrayList(const ArrayList &original_arrlist) {
		size = 0;
		capacity = original_arrlist->get_size();
		reallocate(capacity);
		size = original_arrlist->get_size();
		for (int i = 0; i < size; i++) 
			array[i] = original_arrlist.at(i);
	}

	~ArrayList() { delete[] array; }

	void push_back(const TElement &element);

	void push_front(const TElement &element);

	void remove(int idx);

	TElement &at(int idx);

	void insert_at(int idx, const TElement &element);

	inline int get_size() const {
		return size;
	}

	TElement *get_array() {
		return array;
	}

	bool isSorted(bool(*lessThan)(const TElement &el1, const TElement &el2) = [](const TElement &el1, const TElement &el2) {
		return el1 < el2;
	});

	int upper_bound(const TElement &value, bool(*lessThan)(const TElement &el1, const TElement &el2) = [](const TElement &el1, const TElement &el2) {
		return el1 < el2;
	});
};

template <class TElement>
void ArrayList<TElement>::push_back(const TElement &element) {
	if (size == capacity)
		reallocate();
	array[size] = element;
	size++;
}

template <class TElement>
void ArrayList<TElement>::push_front(const TElement &element) {
	this->push_back(0);
	for (int i = size - 1; i > 0; i--) {
		array[i] = array[i - 1];
	}
	array[0] = element;
}

template <class TElement>
void ArrayList<TElement>::remove(int idx) {
	if (idx < 0 || idx >= size)
		throw IndexException("Index passed to ArrayList<>::remove() is out of boundaries.", idx);
	for (int j = idx; j < size - 1; j++)
		array[j] = array[j + 1];
	size--;
}

template <class TElement>
TElement &ArrayList<TElement>::at(int idx) {
	if (idx < 0 || idx >= size)
		throw IndexException("Index passed to ArrayList<>::at() is out of boundaries.", idx);
	return array[idx];
}

template <class TElement>
void ArrayList<TElement>::insert_at(int idx, const TElement &element) {
	if (idx < 0 || idx >= size)
		throw IndexException("Index passed to ArrayList<>::insert_at() is out of boundaries.", idx);
	this->push_back(array[size - 1]);
	for (int i = size - 1; i > idx; i--) {
		array[i] = array[i - 1];
	}
	array[idx] = element;
}

template <class TElement>
bool ArrayList<TElement>::isSorted(bool(*lessThan)(const TElement &el1, const TElement &el2)) {
	bool sorted = true;
	for (int i = 1; i < size && sorted; i++)
		if (lessThan(array[i], array[i - 1]))
			sorted = false;
	return sorted;
}

template <class TElement>
int ArrayList<TElement>::upper_bound(const TElement &value, bool(*lessThan)(const TElement &el1, const TElement &el2)) {
	for (int i = 0; i < size; i++) {
		if (lessThan(value, array[i]))
			return i;
	}
	return size;
}


#endif