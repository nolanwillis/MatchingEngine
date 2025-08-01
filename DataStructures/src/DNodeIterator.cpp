#include "DNodeIterator.h"
#include "DNode.h"

DNodeIterator::DNodeIterator()
	: 
	pHead(nullptr), 
	pCurrent(nullptr), 
	isDone(true)
{}
DNodeIterator::DNodeIterator(DNode* pHead)
	:	
	pHead(pHead), 
	pCurrent(pHead), 
	isDone(false)
{}

DNode* DNodeIterator::First()
{
	if (this->pHead != nullptr)
	{
		this->isDone = false;
	}
	else
	{
		this->isDone = true;
	}
	this->pCurrent = this->pHead;
	return this->pCurrent;
}
DNode* DNodeIterator::Current()
{
	return this->pCurrent;
}
DNode* DNodeIterator::Next()
{
	// Move to the next node if it is not null.
	if (this->pCurrent != nullptr)
	{
		this->pCurrent = this->pCurrent->pNext;
	}
	// Update the done status of the DNodeIterator.
	if (this->pCurrent == nullptr)
	{
		this->isDone = true;
	}
	else
	{
		this->isDone = false;
	}
	return this->pCurrent;
}
DNode* DNodeIterator::Prev()
{
	// Move to the previous node if it is not null.
	if (this->pCurrent != nullptr && this->pCurrent->pPrev != nullptr)
	{
		this->pCurrent = this->pCurrent->pPrev;
	}
	return this->pCurrent;
}
bool DNodeIterator::IsDone()
{
	return this->isDone;
}
void DNodeIterator::Reset(DNode* pDNode)
{
	if (pDNode != nullptr)
	{
		this->isDone = false;
		this->pCurrent = pDNode;
		this->pHead = pDNode;
	}
	else
	{
		this->isDone = true;
		this->pCurrent = nullptr;
		this->pHead = nullptr;
	}
}
