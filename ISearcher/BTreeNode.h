#include "C:\Users\nolme\Repositories\vigilant-potato\KeyNode.h" //KeyNode
#include "C:\Users\nolme\Repositories\vigilant-potato\Exception\Exception\BadExecutionException.h"
#include "C:\Users\nolme\Repositories\vigilant-potato\Exception\Exception\IndexException.h"
#include "C:\Users\nolme\Repositories\laboratory_projects\Semester_3\lab1\lab1\Sequence.h"

#ifndef __BTREENODE__H__
#define __BTREENODE__H__

using namespace std;

template <typename TKey, typename TElement, unsigned int minDegree = 2> //minDegree = the minimum amount of children. 2-3-4 minDegree = 2
class BTreeNode {
	Sequence<KeyNode<TKey, TElement> *> *keys;
	Sequence<BTreeNode<TKey, TElement, minDegree> *> *children;
	bool isLeaf;

public:
	BTreeNode() : keys(nullptr), children(nullptr), isLeaf(true) {}
	
	BTreeNode(Sequence<KeyNode<TKey, TElement> *> *keys, Sequence<BTreeNode<TKey, TElement, minDegree> *> *children, bool isLeaf = true)
		: keys(keys), children(children), isLeaf(isLeaf) {
		children->Append(nullptr);
	}

	BTreeNode(const BTreeNode<TKey, TElement, minDegree> &node)
		: keys(node.keys), children(node.children), isLeaf(node.isLeaf) {}

	~BTreeNode();

	void setIsLeaf(bool isLeaf);

	bool getIsLeaf() const;

	void constructKeys(Sequence<KeyNode<TKey, TElement> *> *seq);

	void constructChildren(Sequence<BTreeNode<TKey, TElement, minDegree> *> *seq);

	void addKeyNode(KeyNode<TKey, TElement> *keyNode);

	KeyNode<TKey, TElement> *setKeyNode(KeyNode<TKey, TElement> *keyNode, int index); // only allowed for existent keynodes, indexation starts at zero
	
	KeyNode<TKey, TElement> *getKeyNode(int index);

	KeyNode<TKey, TElement> *removeKeyNode(int index);

	BTreeNode<TKey, TElement, minDegree> *setChild(BTreeNode<TKey, TElement, minDegree> *child, int index);

	BTreeNode<TKey, TElement, minDegree> *getChild(int index);
	
	void clearSubtree();

	int keyCount();
	
	int childCount();	

	void insertKeyNode(KeyNode<TKey, TElement> *keyNode, int index);
};

template <typename TKey, typename TElement, unsigned int minDegree>
void BTreeNode<TKey, TElement, minDegree>::setIsLeaf(bool isLeaf) {
	this->isLeaf = isLeaf;
}

template <typename TKey, typename TElement, unsigned int minDegree>
bool BTreeNode<TKey, TElement, minDegree>::getIsLeaf() const {
	return isLeaf;
}

template <typename TKey, typename TElement, unsigned int minDegree>
void BTreeNode<TKey, TElement, minDegree>::constructKeys(Sequence<KeyNode<TKey, TElement> *> *seq) {
	if (keys != nullptr)
		throw BadExecutionException("BadExecutionException thrown from BTreeNode::constructKeys.", "Trying to construct keys, but the they're already constructed.");
	keys = seq;
}

template <typename TKey, typename TElement, unsigned int minDegree>
void BTreeNode<TKey, TElement, minDegree>::constructChildren(Sequence<BTreeNode<TKey, TElement, minDegree> *> *seq) {
	if (children != nullptr)
		throw BadExecutionException("BadExecutionException thrown from BTreeNode::constructChildren.", "Trying to construct children, but the they're already constructed.");
	children = seq;
}

template <typename TKey, typename TElement, unsigned int minDegree>
void BTreeNode<TKey, TElement, minDegree>::addKeyNode(KeyNode<TKey, TElement> *keyNode) {
	//add keynode (not allowed if amount of keynodes == minDegree * 2 - 1)
	//should automatically add uninitialized nodeSequence elements (== nullptr, preliminary)
	if (children->getLength() == minDegree * 2)
		throw BadExecutionException("BadExecutionException thrown from BTreeNode::addKeyNode.", "Trying to add a keyNode, but the keys are already full.");
	
	int index = keys->getLength();
	for (int i = 0; i < keys->getLength(); i++) {
		TKey key = keys->Get(i)->getKey();
		if (key >= keyNode->getKey()) {
			index = i;
			break;
		}
	}
	keys->InsertAt(keyNode, index);
	children->InsertAt(nullptr, index + 1);
}

template <typename TKey, typename TElement, unsigned int minDegree>
KeyNode<TKey, TElement> *BTreeNode<TKey, TElement, minDegree>::setKeyNode(KeyNode<TKey, TElement> *keyNode, int index) {
	KeyNode<TKey, TElement> *temp = keys->Get(index);
	keys->Set(keyNode, index);
	return temp;
}

template <typename TKey, typename TElement, unsigned int minDegree>
BTreeNode<TKey, TElement, minDegree>::~BTreeNode() {
	if (keys)
		delete keys;
	if (children)
		delete children;
}

template <typename TKey, typename TElement, unsigned int minDegree>
KeyNode<TKey, TElement> *BTreeNode<TKey, TElement, minDegree>::getKeyNode(int index){
	if (index < 0 || index >= keys->getLength())
		throw IndexException("IndexException thrown at BTreeNode<>::getKeyNode().", index);

	return keys->Get(index);
}

template <typename TKey, typename TElement, unsigned int minDegree>
KeyNode<TKey, TElement> *BTreeNode<TKey, TElement, minDegree>::removeKeyNode(int index) {
	if (index < 0 || index >= keys->getLength())
		throw IndexException("IndexException thrown at BTreeNode<>::removeKeyNode().", index);

	KeyNode<TKey, TElement> *temp = keys->Get(index);
	keys->RemoveFrom(index);
	if (index + 1< children->getLength())
		children->RemoveFrom(index + 1);
	return temp;
}

template <typename TKey, typename TElement, unsigned int minDegree>
BTreeNode<TKey, TElement, minDegree> *BTreeNode<TKey, TElement, minDegree>::setChild(BTreeNode<TKey, TElement, minDegree> *child, int index) {
	if (children->getLength() == 0)
		children->Append(nullptr);
	if (keys->getLength() == 0 && index != 0)
		throw BadExecutionException("BadExecutionException thrown at void BTreeNode<TKey, TElement, minDegree>::setChild(BTreeNode<TKey, TElement, minDegree> *child, int index).",
			"Trying to set a child, but there're no children existent.");
	if (children->getLength() < index || index < 0)
		throw IndexException("IndexException thrown at void BTreeNode<TKey, TElement, minDegree>::setChild(BTreeNode<TKey, TElement, minDegree> *child, int index)",
			index);

	BTreeNode<TKey, TElement, minDegree> *temp = nullptr;
	
	if (children->getLength() > index) {
		children->Set(child, index);
		temp = children->Get(index);
	}
	else
		children->Append(child);
	return temp;
}

template <typename TKey, typename TElement, unsigned int minDegree>
BTreeNode<TKey, TElement, minDegree> *BTreeNode<TKey, TElement, minDegree>::getChild(int index) {
	if (children->getLength() <= index)
		throw IndexException("IndexException thrown at const BTreeNode<TKey, TElement, minDegree> *BTreeNode<TKey, TElement, minDegree>::getChild(int index) const.",
			index);

	return children->Get(index);
}

template <typename TKey, typename TElement, unsigned int minDegree>
void BTreeNode<TKey, TElement, minDegree>::clearSubtree() {
	for (int i = children->getLength() - 1; i >= 0; i--) 
		if (auto bnode = children->Get(i))
			bnode->clearSubtree();

	for (int i = keys->getLength() - 1; i >= 0; i--) {
		KeyNode<TKey, TElement> *keyNode = this->removeKeyNode(i);
		delete keyNode;
	}
}

template <typename TKey, typename TElement, unsigned int minDegree>
int BTreeNode<TKey, TElement, minDegree>::keyCount() {
	return keys->getLength();
}

template <typename TKey, typename TElement, unsigned int minDegree>
int BTreeNode<TKey, TElement, minDegree>::childCount() {
	return children->getLength();
}

template <typename TKey, typename TElement, unsigned int minDegree>
void BTreeNode<TKey, TElement, minDegree>::insertKeyNode(KeyNode<TKey, TElement> *keyNode, int index) {
	if (keys->getLength() == minDegree * 2 - 1)
		throw BadExecutionException("BadExecutionException thrown at void BTreeNode<TKey, TElement, minDegree>::insertKeyNode(KeyNode<TKey, TElement> *keyNode, int index)",
			"Trying to insert a keyNode, but the keys are full.");
	if (index > keys->getLength() || index < 0) 
		throw IndexException("IndexException thrown at void BTreeNode<TKey, TElement, minDegree>::insertKeyNode(KeyNode<TKey, TElement> *keyNode, int index)",
			index);
	
	keys->InsertAt(keyNode, index);
	children->InsertAt(nullptr, index + 1);
}

#endif
