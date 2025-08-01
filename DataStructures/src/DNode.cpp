#include "DNode.h"

#include <cstdio>

DNode::DNode() 
	: 
	pPrev(nullptr),
	pNext(nullptr)
{}

void DNode::Print()
{
	std::printf("\n");
	std::printf("DNODE (%p)\n", this);
	std::printf("	pPrev: %p\n", this->pPrev);
	std::printf("	pNext: %p\n", this->pNext);
}
void DNode::Reset()
{
	this->pPrev = nullptr;
	this->pNext = nullptr;
}
