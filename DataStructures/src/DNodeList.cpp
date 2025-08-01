#include "DNodeList.h"
#include "DNode.h"
#include "DNodeIterator.h"

#include <assert.h>

DNodeList::DNodeList()
	:
	poDNodeIterator(new DNodeIterator()),
	poHead(nullptr)
{}
DNodeList::~DNodeList()
{
	// Delete all the nodes on the list.
	poDNodeIterator->First();
	while (!poDNodeIterator->IsDone())
	{
		DNode* pDeleteMe = poDNodeIterator->Current();
		poDNodeIterator->Next();
		if (pDeleteMe != nullptr)
		{
			delete pDeleteMe;
		}
	}
	// Delete the iterator itself.
	delete this->poDNodeIterator;
	// Ensure pointers are nullptr.
	this->poDNodeIterator = nullptr;
	this->poHead = nullptr;
}

void DNodeList::AddToFront(DNode* const pDNode)
{
	assert(pDNode);
	// Inserts the new node at the front.
	if (this->poHead == nullptr)
	{
		this->poHead = pDNode;
		pDNode->pNext = nullptr;
		pDNode->pPrev = nullptr;
	}
	else
	{
		pDNode->pPrev = nullptr;
		pDNode->pNext = poHead;
		poHead->pPrev = pDNode;
		poHead = pDNode;
	}
	// Reset the iterator to the front of the list.
	this->poDNodeIterator->Reset(poHead);
	assert(poHead != nullptr);
}
void DNodeList::AddToEnd(DNode* const pDNode)
{
	assert(pDNode != nullptr);
	if (poHead == nullptr)
	{
		poHead = pDNode;
		pDNode->pNext = nullptr;
		pDNode->pPrev = nullptr;
		// Reset the iterator to point at the new poHead.
		this->poDNodeIterator->Reset(poHead);
	}
	else
	{
		DNode* pTmp = nullptr;
		for (this->poDNodeIterator->First(); !this->poDNodeIterator->IsDone(); 
			this->poDNodeIterator->Next())
		{
			pTmp = this->poDNodeIterator->Current();
		}
		pDNode->pPrev = pTmp;
		pDNode->pNext = nullptr;
		pTmp->pNext = pDNode;
	}
	// Ensure the head has been set.
	assert(poHead != nullptr);
}
void DNodeList::Remove(DNode* const pDNode)
{
}
DNode* DNodeList::RemoveFromFront()
{
	return nullptr;
}

DNode* DNodeList::Find(DNode* const pDNode)
{
	assert(pDNode);
	for (this->poDNodeIterator->First(); !this->poDNodeIterator->IsDone(); 
			this->poDNodeIterator->Next())
	{
		if (this->poDNodeIterator->Current()->Compare(pDNode))
		{
			// We found it so return it.
			return this->poDNodeIterator->Current();
		}
	}
	// We did not find it so return nothing.
	return nullptr;
}
DNodeIterator* DNodeList::GetDNodeIterator()
{
	this->poDNodeIterator->Reset(this->poHead);
	return this->poDNodeIterator;
}

void DNodeList::Print()
{
	for (this->poDNodeIterator->First(); !this->poDNodeIterator->IsDone();
		this->poDNodeIterator->Next())
	{
		this->poDNodeIterator->Current()->Print();
	}
}
