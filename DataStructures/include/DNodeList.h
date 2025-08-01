#ifndef DNODE_LIST_H
#define DNODE_LIST_H

class DNode;
class DNodeIterator;

class DNodeList
{
public:
	DNodeList();
	DNodeList(const DNodeList& rhs) = delete;
	DNodeList& operator= (const DNodeList& rhs) = delete;
	~DNodeList();

	// Adds a DNode to the front of the DNodeList.
	void AddToFront(DNode* const pDNode);
	// Adds a DNode to the end of the DNodeList.
	void AddToEnd(DNode* const pDNode);
	// Removes a given DNode from the DNodeList.
	void Remove(DNode* const pDNode);
	// Pops the DNode off the front of the DNodeList.
	DNode* RemoveFromFront();
	// Finds a given DNode. If it doesn't exist returns nullptr.
	DNode* Find(DNode* const pDNode);
	// Returns the DNodeIterator created for ths DNodeList on construction.
	DNodeIterator* GetDNodeIterator();
	// Prints all the DNodes in this DNodeList.
	void Print();

private:
	DNode* poHead;
	DNodeIterator* poDNodeIterator;
};

#endif
