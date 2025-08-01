#ifndef DNODE_ITERATOR_H
#define DNODE_ITERATOR_H

class DNode;

class DNodeIterator
{
public:
	DNodeIterator();
	DNodeIterator(DNode* pHead);
	DNodeIterator(const DNodeIterator& rhs) = delete;
	DNodeIterator& operator=(const DNodeIterator& rhs) = delete;
	virtual ~DNodeIterator() = default;

	// Moves the DNodeIterator to it's head DNode.
	DNode* First();
	// Returns the current DNode the DNodeIterator is pointing to.
	DNode* Current();
	// Moves the DNodeIterator to the next DNode and returns it (can go out of bounds).
	DNode* Next();
	// Moves the DNodeIterator to the previous DNode and returns it (stops at the head).
	DNode* Prev();
	// Returns if this DNodeIterator actually points to something.
	bool IsDone();
	// Resets this DNodeIterator, with the passed in DNode as the head.
	void Reset(DNode* pDNode);

private:
	DNode* pHead;
	DNode* pCurrent;
	bool isDone;
};

#endif