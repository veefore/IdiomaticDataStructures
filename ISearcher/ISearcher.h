#ifndef __ISEARCHER__H__
#define __ISEARCHER__H__

template <typename TObject>
class ISearcher {
public:
	
	virtual int Search(const TObject &value) const = 0;
};


#endif
