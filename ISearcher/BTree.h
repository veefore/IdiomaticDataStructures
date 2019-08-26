#include "BTreeNode.h"
#include <functional>
#include <fstream>
#include <string>
#include "C:\Users\nolme\Repositories\vigilant-potato\Exception\Exception\InvalidArgumentException.h"

#ifndef __BTREE__H__
#define __BTREE__H__

using namespace std;

template <typename TKey, typename TElement, unsigned int minDegree = 2>
class BTree {
	function<Sequence<KeyNode<TKey, TElement> *> *()> keyNodeSeqConstructor;
	function<Sequence<BTreeNode<TKey, TElement, minDegree> *> *()> BTreeNodeSeqConstructor;
	BTreeNode<TKey, TElement, minDegree> *root;
	int size;

	//add comparison function?///////

	BTreeNode<TKey, TElement, minDegree> *splitChild(BTreeNode<TKey, TElement, minDegree> *node, int childIndex) { 
		if (node->keyCount() == 2 * minDegree - 1)
			throw BadExecutionException("BadExecutionException thrown at BTree::splitChild().", "Parent node is full.");
		
		Sequence<KeyNode<TKey, TElement> *> *knseq = keyNodeSeqConstructor(); 
		Sequence<BTreeNode<TKey, TElement, minDegree> *> *btseq = BTreeNodeSeqConstructor();
		BTreeNode<TKey, TElement, minDegree> *newNode = new BTreeNode<TKey, TElement, minDegree>(knseq, btseq);

		BTreeNode<TKey, TElement, minDegree> *child = node->getChild(childIndex);
		
		for (int i = 0; i < minDegree - 1; i++) {
			newNode->addKeyNode(nullptr);
		}
		
		for (int i = 2 * minDegree - 2, j = minDegree - 2; i >= minDegree; i--, j--) {
			BTreeNode<TKey, TElement, minDegree> *rchild = nullptr;
			if (i + 1 < child->childCount())
				rchild = child->getChild(i + 1);
			newNode->setKeyNode(child->removeKeyNode(i), j);
			newNode->setChild(rchild, j + 1);
		}
		newNode->setChild(child->getChild(minDegree), 0);
		
		KeyNode<TKey, TElement> *midNode = child->removeKeyNode(minDegree - 1);
		node->insertKeyNode(midNode, childIndex);
		node->setChild(newNode, childIndex + 1);
		newNode->setIsLeaf(child->getIsLeaf());
		return newNode;
	} // should it be static?

	void move(BTreeNode<TKey, TElement, minDegree> **curp, const TKey &key, BTreeNode<TKey, TElement, minDegree> **prevp, int &prevIndex);

	void makeNodeRemovable(BTreeNode<TKey, TElement, minDegree> **curp, BTreeNode<TKey, TElement, minDegree> **prevp, int &prevIndex);

	void remove(const TKey &key, BTreeNode<TKey, TElement, minDegree> *subtreeRoot);

public:
	BTree();

	BTree(const function<Sequence<KeyNode<TKey, TElement> *> *()> &keyNodeSeqConstructor,
		const function<Sequence<BTreeNode<TKey, TElement, minDegree> *> *()> &BTreeNodeSeqConstructor);

	BTree(Sequence<KeyNode<TKey, TElement> *> *seq, const function<Sequence<KeyNode<TKey, TElement> *> *()> &keyNodeSeqConstructor,
		const function<Sequence<BTreeNode<TKey, TElement, minDegree> *> *()> &BTreeNodeSeqConstructor);

	~BTree();

	void setKeyNodeSeqConstructor(const function<Sequence<KeyNode<TKey, TElement> *> *()> &keyNodeSeqConstructor);

	void setBTreeNodeSeqConstructor(const function<Sequence<BTreeNode<TKey, TElement, minDegree> *> *()> &BTreeNodeSeqConstructor);

	void insert(const TKey &key, const TElement &element);

	void insert(KeyNode<TKey, TElement> *keyNode);

	TElement find(const TKey &value, TElement null) const; //null is returned if no match found
	
	int getSize() const;

	bool isReady() const;

	void remove(const TKey &key) { this->remove(key, root); }

};

template <typename TKey, typename TElement, unsigned int minDegree>
BTree<TKey, TElement, minDegree>::BTree() : size(0), root(nullptr) {}

template <typename TKey, typename TElement, unsigned int minDegree>
BTree<TKey, TElement, minDegree>::BTree(const function<Sequence<KeyNode<TKey, TElement> *> *()> &keyNodeSeqConstructor,
	const function<Sequence<BTreeNode<TKey, TElement, minDegree> *> *()> &BTreeNodeSeqConstructor) : size(0), root(nullptr) {
	this->keyNodeSeqConstructor = keyNodeSeqConstructor;
	this->BTreeNodeSeqConstructor = BTreeNodeSeqConstructor;
}

template <typename TKey, typename TElement, unsigned int minDegree>
BTree<TKey, TElement, minDegree>::~BTree() {
	if (root)
		root->clearSubtree();
	delete root;
}

template <typename TKey, typename TElement, unsigned int minDegree>
void BTree<TKey, TElement, minDegree>::setKeyNodeSeqConstructor(const function<Sequence<KeyNode<TKey, TElement> *> *()> &keyNodeSeqConstructor) {
	this->keyNodeSeqConstructor = keyNodeSeqConstructor;
}

template <typename TKey, typename TElement, unsigned int minDegree>
void BTree<TKey, TElement, minDegree>::setBTreeNodeSeqConstructor(const function<Sequence<BTreeNode<TKey, TElement, minDegree> *> *()> &BTreeNodeSeqConstructor) {
	this->BTreeNodeSeqConstructor = BTreeNodeSeqConstructor;
}

template <typename TKey, typename TElement, unsigned int minDegree>
void BTree<TKey, TElement, minDegree>::insert(const TKey &key, const TElement &element) {
	if (!this->isReady())
		throw BadExecutionException("BadExecutionException thrown at BTree::insert().", "BTree has one or more uninitialized sequence constructors.");

	BTreeNode<TKey, TElement, minDegree> *cur = root; //if root  == nullptr || size == 0 to be written
	
	
	if (cur == nullptr) {
		root = new BTreeNode<TKey, TElement, minDegree>(this->keyNodeSeqConstructor(), this->BTreeNodeSeqConstructor(), true);
		cur = root;
	}
	BTreeNode<TKey, TElement, minDegree> *prev = nullptr;
	int prev_index = -1;
	this->move(&cur, key, &prev, prev_index);
	if (cur->keyCount() == 2 * minDegree - 1) {
		if (prev_index == -1) {
			prev = new BTreeNode<TKey, TElement, minDegree>((this->keyNodeSeqConstructor)(), (this->BTreeNodeSeqConstructor)(), false);
			prev->setChild(cur, 0);
			prev_index = 0;
			root = prev;
		}
		this->splitChild(prev, prev_index);
	}
	cur->addKeyNode(new KeyNode<TKey, TElement>(key, element));
	size++;
}

template <typename TKey, typename TElement, unsigned int minDegree>
void BTree<TKey, TElement, minDegree>::insert(KeyNode<TKey, TElement> *keyNode) {
	if (keyNode == nullptr)
		throw BadExecutionException("BadExecutionException thrown at BTree::insert().", "keyNode passed as parameter is nullptr.");
	this->insert(keyNode->getKey(), keyNode->getElement());
}

template <typename TKey, typename TElement, unsigned int minDegree>
int BTree<TKey, TElement, minDegree>::getSize() const {
	return size;
}

template <typename TKey, typename TElement, unsigned int minDegree>
bool BTree<TKey, TElement, minDegree>::isReady() const {
	bool flag = true;
	if (keyNodeSeqConstructor == nullptr)
		flag = false;
	if (BTreeNodeSeqConstructor == nullptr)
		flag = false;
	return flag;
}

template <typename TKey, typename TElement, unsigned int minDegree>
BTree<TKey, TElement, minDegree>::BTree(Sequence<KeyNode<TKey, TElement> *> *seq, const function<Sequence<KeyNode<TKey, TElement> *> *()> &keyNodeSeqConstructor,
	const function<Sequence<BTreeNode<TKey, TElement, minDegree> *> *()> &BTreeNodeSeqConstructor) {
	if (seq == nullptr)
		throw InvalidArgumentException("InvalidArgumentException thrown at void BTree<TKey, TElement, minDegree>::initialize(Sequence<KeyNode<TKey, TElement> *> *seq)",
			"Nullptr passed.");
	this->keyNodeSeqConstructor = keyNodeSeqConstructor;
	this->BTreeNodeSeqConstructor = BTreeNodeSeqConstructor;

	KeyNode<TKey, TElement> **arr = seq->GetArray();
	for (int i = 0; i < seq->getLength(); i++) {
		this->insert(arr[i]);
	}
}

template <typename TKey, typename TElement, unsigned int minDegree>
TElement BTree<TKey, TElement, minDegree>::find(const TKey &value, TElement null) const {
	if (size <= 0)
		throw BadExecutionException("BadExecutionException thrown at TElement BTree<TKey, TElement, minDegree>::find(const TKey &value) const", 
			"Size is " + to_string(size) + " <= 0.");

	BTreeNode<TKey, TElement, minDegree> *cur = root;
	
	if (cur->keyCount() == 0)
		return null;
	while (cur != nullptr) {
		for (int i = 0; cur != nullptr && i < cur->keyCount(); i++) {
			KeyNode<TKey, TElement> *knode = cur->getKeyNode(i);
			if (knode->getKey() == value) {
				return knode->getElement();
			}
			else if (knode->getKey() > value) {
				cur = cur->getChild(i);
				break;
			}
			if (i == cur->keyCount() - 1) {
				cur = cur->getChild(cur->keyCount());
			}
		}
		if (cur == nullptr)
			return null;
	}
	
	return null;
}

template <typename TKey, typename TElement, unsigned int minDegree>
void BTree<TKey, TElement, minDegree>::move(BTreeNode<TKey, TElement, minDegree> **curp, const TKey &key, BTreeNode<TKey, TElement, minDegree> **prevp, int &prevIndex) {
	BTreeNode<TKey, TElement, minDegree> *cur = *curp;
	BTreeNode<TKey, TElement, minDegree> *prev = *prevp;
	while (!cur->getIsLeaf()) {
		KeyNode<TKey, TElement> *curKN = nullptr;
		int index = -1;
		for (int i = 0; i < cur->keyCount(); i++) { //should use an iterator, but that's a hard one
			curKN = cur->getKeyNode(i);
			if (curKN->getKey() >= key) {
				index = i;
				break;
			}
		}
		if (index == -1)
			index = cur->keyCount();

		if (cur->keyCount() == minDegree * 2 - 1) { //split if full
			if (prevIndex == -1) {
				prev = new BTreeNode<TKey, TElement, minDegree>((this->keyNodeSeqConstructor)(), (this->BTreeNodeSeqConstructor)(), false);
				prev->setChild(cur, 0);
				prevIndex = 0;
				root = prev;
			}
			BTreeNode<TKey, TElement, minDegree> *temp = this->splitChild(prev, prevIndex);
			if (index > minDegree - 1) {
				cur = temp;
				index -= minDegree;
			}
		}

		prev = cur;
		prevIndex = index;
		if (!cur->getIsLeaf())
			cur = cur->getChild(index);
	}
	*curp = cur;
	*prevp = prev;
}

template <typename TKey, typename TElement, unsigned int minDegree>
void BTree<TKey, TElement, minDegree>::remove(const TKey &key, BTreeNode<TKey, TElement, minDegree> *subtreeRoot) {
	if (subtreeRoot == nullptr)
		throw BadExecutionException("BadExecutionException thrown at BTree::remove()", "SubtreeRoot is nullptr.");

	BTreeNode<TKey, TElement, minDegree> *cur = subtreeRoot;
	BTreeNode<TKey, TElement, minDegree> *prev = nullptr;
	int prevIndex = -1;
	if (cur->keyCount() == 0)
		return;
	
	bool found = false;
	int index = -1;
	while (cur != nullptr && index == -1) {
		this->makeNodeRemovable(&cur, &prev, prevIndex);
		for (int i = 0; cur != nullptr && i < cur->keyCount(); i++) {
			KeyNode<TKey, TElement> *knode = cur->getKeyNode(i);
			if (knode->getKey() == key) {
				index = i;
				break;
			}
			else if (knode->getKey() > key) {
				prev = cur;
				prevIndex = i;
				cur = cur->getChild(i);
				break;
			}
			if (i == cur->keyCount() - 1) {
				prev = cur;
				prevIndex = cur->keyCount();
				cur = cur->getChild(cur->keyCount());
			}
		}
		if (cur == nullptr)
			return;
	}

	
	if (index != -1) {
		if (cur->getIsLeaf()) { //if leaf, ensure the (minDegree - 1)+ keys and remove
			this->makeNodeRemovable(&cur, &prev, prevIndex);
			cur->removeKeyNode(index);
		}
		else { 
			auto child = cur->getChild(index);
			if (child) { //if has left child
				auto child2 = cur->getChild(index + 1);
				if (!child2) { //if has lchild and no rchild
					cur->removeKeyNode(index);
				} 
				else { //if has lchild and rchild, pull up a node from one of them, or merge
					KeyNode<TKey, TElement> *replacerNode = nullptr;
					if (child->keyCount() >= minDegree) {
						replacerNode = child->getKeyNode(child->keyCount() - 1);
						auto temp = cur->getKeyNode(index);
						cur->setKeyNode(replacerNode, index);
						delete temp;
						this->remove(replacerNode->getKey(), child);
					}
					else if (child2->keyCount() >= minDegree) {
						replacerNode = child2->getKeyNode(0);
						auto temp = cur->getKeyNode(index);
						cur->setKeyNode(replacerNode, index);
						delete temp;
						this->remove(replacerNode->getKey(), child2);
					}
					else { //else merge
						cur->removeKeyNode(index);
						while (child2->keyCount() > 0) {
							auto ch0 = child2->getChild(0);
							auto ch1 = child2->getChild(1);
							auto node = child2->removeKeyNode(0);
							
							child2->setChild(ch1, 0);

							child->addKeyNode(node);
							child->setChild(ch0, child->keyCount());
						}
						child->setChild(child2->getChild(0), child->keyCount());
						child2->setChild(nullptr, 0);
						delete child2;
					}
				}
			}
			else { //if no left child
				this->makeNodeRemovable(&cur, &prev, prevIndex);
				cur->setChild(cur->getChild(index + 1), index);
				cur->removeKeyNode(index);
			}
		}
		if (subtreeRoot == root)
			size--;
	}
}


template <typename TKey, typename TElement, unsigned int minDegree> //ensures that cur has at least minDegree keys
void BTree<TKey, TElement, minDegree>::makeNodeRemovable(BTreeNode<TKey, TElement, minDegree> **curp, BTreeNode<TKey, TElement, minDegree> **prevp, int &prevIndex) {
	BTreeNode<TKey, TElement, minDegree> *cur = *curp;
	BTreeNode<TKey, TElement, minDegree> *prev = *prevp;
	if (cur->keyCount() >= minDegree || cur == this->root)
		return;

	/*
	1. If isLeaf
	2. If !isLeaf
		2.1 HAS AT LEAST ONE SIBLING
			a) if has a sibling with >= minDegree keys, then we simply take a key from him
			b) otherwise, cur and sibling have minDegree-1 keys, so we unite them and insert the keynode from parent
		2.3 HAS NO SIBLINGS
			a) parent has >= minDegree keys, we steal one
			b) unite with parent
	*/

	if (cur->getIsLeaf()) {//if cur is leaf
		BTreeNode<TKey, TElement, minDegree> *sibling = prev->getChild(prevIndex - 1);
		if (prevIndex > 0 && prev->getChild(prevIndex - 1) != nullptr && sibling->keyCount() > minDegree - 1) { //try stealing from lsibling
			
			auto sibChild = sibling->getChild(sibling->keyCount());
			auto parentKNode = prev->getKeyNode(prevIndex - 1);

			prev->setKeyNode(sibling->removeKeyNode(sibling->keyCount()), prevIndex - 1);
			cur->addKeyNode(parentKNode);
			cur->setChild(cur->getChild(0), 1);
			cur->setChild(sibChild, 0);
		}
		else if (prev && prevIndex < prev->keyCount() && (sibling = prev->getChild(prevIndex + 1)) != nullptr && sibling->keyCount() > minDegree - 1) { //try stealing from rsib
			BTreeNode<TKey, TElement, minDegree> *sibling = prev->getChild(prevIndex + 1);
			auto sibChild0 = sibling->getChild(0);
			auto sibChild1 = sibling->getChild(1);
			auto parentKNode = prev->getKeyNode(prevIndex);

			prev->setKeyNode(sibling->removeKeyNode(0), prevIndex);
			sibling->setChild(sibChild1, 0);
			cur->addKeyNode(parentKNode);
			cur->setChild(sibChild0, cur->keyCount());
		}
		else { //unstealable from lsib & rsib
			if (prev == root && prev->keyCount() == 0) { //if prev is empty root, cut is the new root
				root->setChild(nullptr, 0);
				delete root;
				root = cur;
				return;
			}

			if (prev->keyCount() >= minDegree || (prev == root && prevIndex != 0)) { //try stealing from prev
				if (prevIndex != 0) {
					auto parentKNode = prev->getKeyNode(prevIndex - 1);
					auto parentChild = prev->getChild(prevIndex - 1);

					cur->addKeyNode(parentKNode);
					cur->setChild(cur->getChild(0), 1);
					cur->setChild(parentChild, 0);

					prev->setChild(cur, prevIndex - 1);
					prev->removeKeyNode(prevIndex - 1);
					prevIndex--;
				}
				else {
					auto parentKNode = prev->getKeyNode(prevIndex);
					auto parentChild = prev->getChild(prevIndex + 1);

					cur->addKeyNode(parentKNode);
					cur->setChild(parentChild, cur->keyCount());

					prev->removeKeyNode(prevIndex);
				}
			}
			else { //else merge with prev
				while (cur->keyCount() > 0) {
					prev->addKeyNode(cur->removeKeyNode(cur->keyCount() - 1));
				}
				prev->setIsLeaf(true);

				cur->setChild(nullptr, 0);
				delete cur;

				cur = prev;
			}
		}
	}
	else { //if cur not isLeaf
		if (prevIndex > 0 && prev->getChild(prevIndex - 1) != nullptr) { //try stealing from or merging with lsib
			BTreeNode<TKey, TElement, minDegree> *sibling = prev->getChild(prevIndex - 1);
			if (sibling->keyCount() >= minDegree) {
				auto childFromSib = sibling->getChild(sibling->childCount() - 1);
				auto knodeFromSib = sibling->removeKeyNode(sibling->keyCount() - 1);
				auto parentKNode = prev->getKeyNode(prevIndex - 1);
				
				prev->setKeyNode(knodeFromSib, prevIndex - 1);
				cur->addKeyNode(parentKNode);
				
				cur->setChild(cur->getChild(0), 1);
				cur->setChild(childFromSib, 0);
			}
			else {
				auto parentKNode = prev->getKeyNode(prevIndex - 1);
				sibling->addKeyNode(parentKNode);
				sibling->setChild(cur->getChild(0), sibling->keyCount());
				while (cur->keyCount() > 0) {
					auto curChild = cur->getChild(1);
					sibling->addKeyNode(cur->removeKeyNode(0));
					sibling->setChild(curChild, cur->keyCount());
				}
				
				cur->setChild(nullptr, 0);
				delete cur;
				cur = sibling;
				prev->removeKeyNode(prevIndex - 1);
				prevIndex--;
			}
		}
		else if (prevIndex < prev->keyCount() - 1 && prev->getChild(prevIndex + 1) != nullptr) { //try stealing from or merging with rsib
			BTreeNode<TKey, TElement, minDegree> *sibling = prev->getChild(prevIndex + 1);
			if (sibling->keyCount() >= minDegree) {
				auto childFromSib0 = sibling->getChild(0);
				auto childFromSib1 = sibling->getChild(1);
				auto knodeFromSib = sibling->removeKeyNode(0);
				auto parentKNode = prev->getKeyNode(prevIndex);

				prev->setKeyNode(knodeFromSib, prevIndex);
				cur->addKeyNode(parentKNode);
				cur->setChild(childFromSib0, cur->keyCount());

				sibling->setChild(childFromSib1, 0);
			}
			else {
				auto parentKNode = prev->getKeyNode(prevIndex);
				cur->addKeyNode(parentKNode);
				cur->setChild(sibling->getChild(0), cur->keyCount());
				
				while (sibling->keyCount() > 0) {
					auto sibChild = sibling->getChild(1);
					cur->addKeyNode(sibling->removeKeyNode(0));
					cur->setChild(sibChild, cur->keyCount());
				}

				sibling->setChild(nullptr, 0);
				delete sibling;
				prev->removeKeyNode(prevIndex);
				prevIndex--;
			}
		}
		else { //ELSE
			if (prev == root && prev->keyCount() == 0) {
				root->setChild(nullptr, 0);
				delete root;
				root = cur;
				return;
			}
			
			if (prev->keyCount() >= minDegree || (prev == root &&  prevIndex != 0)) { //try stealing from prev
				if (prevIndex != 0) {
					auto parentKNode = prev->getKeyNode(prevIndex - 1);
					auto parentChild = prev->getChild(prevIndex - 1);
					
					cur->addKeyNode(parentKNode);
					cur->setChild(cur->getChild(0), 1);
					cur->setChild(parentChild, 0);

					prev->setChild(cur, prevIndex - 1);
					prev->removeKeyNode(prevIndex - 1);
					prevIndex--;
				}
				else {
					auto parentKNode = prev->getKeyNode(prevIndex);
					auto parentChild = prev->getChild(prevIndex + 1);

					cur->addKeyNode(parentKNode);
					cur->setChild(parentChild, cur->keyCount());

					prev->removeKeyNode(prevIndex);
				}
			}
			else { //or merge with prev
				while (cur->keyCount() > 0) {
					auto child = cur->getChild(cur->keyCount());
					
					prev->addKeyNode(cur->removeKeyNode(cur->keyCount() - 1));
					prev->setChild(child, prevIndex + 1);
				}
				prev->setChild(cur->getChild(0), prevIndex);
				
				cur->setChild(nullptr, 0);
				delete cur;
				
				cur = prev;
			}
		}
	}
	*curp = cur;
	*prevp = prev;
} 


#endif
