#include "VertexBuffer.h"
#include "DX11Manager.h"

#include <assert.h>

VertexBuffer::VertexBuffer()
	:
	numVerts(0),
	strideSize(0),
	offset(0),
	poGPUVertexBuffer(nullptr),
	isInitialized(false)
{}
VertexBuffer::VertexBuffer(UINT numVerts, UINT strideSize, void* pData)
	: 
	numVerts(numVerts),
	strideSize(strideSize),
	offset(0),
	poGPUVertexBuffer(nullptr),
	isInitialized(true)
{
	assert(pData);

	// Create the descriptors for the vertex buffer.
	D3D11_BUFFER_DESC vertexBufferDesc{ 0 };
	D3D11_SUBRESOURCE_DATA resourceData{ 0 };
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.ByteWidth = this->numVerts * this->strideSize;
	vertexBufferDesc.CPUAccessFlags = 0;
	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	resourceData.pSysMem = pData;

	// Create the vertex buffer on the GPU. 
	HRESULT hr;
	hr = DX11Manager::GetDevice()->CreateBuffer
	(
		&vertexBufferDesc, 
		&resourceData, 
		&this->poGPUVertexBuffer
	);

	assert(SUCCEEDED(hr));
	assert(this->poGPUVertexBuffer);
}
VertexBuffer::~VertexBuffer()
{
	SafeRelease(this->poGPUVertexBuffer);
}

//void VertexBuffer::Initialize(UINT _numVerts, UINT _strideSize, void* pData)
//{
//	assert(!this->isInitialized);
//	assert(pData);
//
//	this->numVerts = _numVerts;
//	this->strideSize = _strideSize;
//	this->offset = 0;
//	this->poGPUVertexBuffer = nullptr;
//
//	// Create the descriptors for the vertex buffer.
//	D3D11_BUFFER_DESC vertexBufferDesc{ 0 };
//	D3D11_SUBRESOURCE_DATA resourceData{ 0 };
//	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
//	vertexBufferDesc.ByteWidth = this->numVerts * this->strideSize;
//	vertexBufferDesc.CPUAccessFlags = 0;
//	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
//	resourceData.pSysMem = pData;
//
//	// Create the vertex buffer on the GPU. 
//	HRESULT hr;
//	hr = DX11Manager::GetDevice()->CreateBuffer(
//		&vertexBufferDesc,
//		&resourceData,
//		&this->poGPUVertexBuffer
//	);
//
//	assert(SUCCEEDED(hr));
//	assert(this->poGPUVertexBuffer);
//
//	this->isInitialized = true;
//}

void VertexBuffer::SetActive(VertexSlot slot)
{
	DX11Manager::GetDeviceContext()->IASetVertexBuffers
	(
		(UINT)slot,
		1,
		&this->poGPUVertexBuffer,
		&this->strideSize,
		&this->offset
	);
}