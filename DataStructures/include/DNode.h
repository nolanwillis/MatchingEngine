#ifndef DNODE_H
#define DNODE_H

class DNode
{
public:
	DNode();
	DNode(const DNode& rhs) = default;
	DNode& operator= (const DNode& rhs) = default;
	virtual ~DNode() = default;

	virtual bool Compare(DNode* pDNode) = 0;
	virtual void Print();
	virtual void Reset();

	DNode* pPrev;
	DNode* pNext;
};

#endif
