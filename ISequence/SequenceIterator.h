

#ifndef __SEQUENCEITERATOR__H__
#define __SEQUENCEITERATOR__H__

template <typename TElement, template <typename T> typename TInheritor>
class SequenceIterator {

public:

	virtual TInheritor<TElement> &operator++() = 0;

	virtual TInheritor<TElement> operator++(int) = 0;

	virtual TInheritor<TElement> &operator--() = 0;

	virtual TInheritor<TElement> operator--(int) = 0;

	virtual TInheritor<TElement> &operator+(int addend) = 0;

	virtual TInheritor<TElement> &operator-(int subtrahend) = 0;

	virtual int operator-(const TInheritor<TElement> &itr) = 0;

	virtual bool operator<(const TInheritor<TElement> &itr) const = 0;

	virtual bool operator<=(const TInheritor<TElement> &itr) const = 0;

	virtual bool operator>(const TInheritor<TElement> &itr) const = 0;

	virtual bool operator>=(const TInheritor<TElement> &itr) const = 0;

	virtual TInheritor<TElement> &operator+=(int addend) = 0;

	virtual TInheritor<TElement> &operator-=(int subtrahend) = 0;
	
	virtual bool operator==(const TInheritor<TElement> &itr) const = 0;

	virtual bool operator!=(const TInheritor<TElement> &itr) const = 0;

	virtual TElement &operator*() = 0;

	virtual TElement &operator[](int offset) = 0;

	//virtual TInheritor<TElement> &operator= (const TInheritor<TElement> &itr) = 0;

};

#endif