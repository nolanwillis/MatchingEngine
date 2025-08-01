#include "IndexBuffer.h"
#include "DX11Manager.h"

#include <assert.h>

IndexBuffer::IndexBuffer()
	: 
	numBytes(0),
	poGPUIndexBuffer(nullptr),
	isInitialized(false)
{}
IndexBuffer::IndexBuffer(UINT numBytes, void* pData)
	: 
	numBytes(numBytes), 
	poGPUIndexBuffer(nullptr),
	isInitialized(true)
{
	assert(pData);

	// Create the descriptors for the index buffer.
	D3D11_BUFFER_DESC indexBufferDesc{ 0 };
	D3D11_SUBRESOURCE_DATA resourceData{ 0 };
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.ByteWidth = this->numBytes;
	indexBufferDesc.CPUAccessFlags = 0;
	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	resourceData.pSysMem = pData;

	// Create the index buffer on the GPU. 
	HRESULT hr;
	hr = DX11Manager::GetDevice()->CreateBuffer
	(
		&indexBufferDesc,
		&resourceData,
		&this->poGPUIndexBuffer
	);

	assert(SUCCEEDED(hr));
	assert(this->poGPUIndexBuffer);
}
IndexBuffer::~IndexBuffer()
{
	SafeRelease(this->poGPUIndexBuffer);
}

//void IndexBuffer::Initialize(size_t _numBytes, void* pData)
//{
//	assert(!this->isInitialized);
//	assert(pData);
//
//	this->numBytes = _numBytes;
//	this->poGPUIndexBuffer = nullptr;
//
//	// Create the descriptors for the index buffer.
//	D3D11_BUFFER_DESC indexBufferDesc{ 0 };
//	D3D11_SUBRESOURCE_DATA resourceData{ 0 };
//	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
//	indexBufferDesc.ByteWidth = this->numBytes;
//	indexBufferDesc.CPUAccessFlags = 0;
//	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
//	resourceData.pSysMem = pData;
//
//	// Create the index buffer on the GPU. 
//	HRESULT hr;
//	hr = DX11Manager::GetDevice()->CreateBuffer
//	(
//		&indexBufferDesc,
//		&resourceData,
//		&this->poGPUIndexBuffer
//	);
//
//	assert(SUCCEEDED(hr));
//	assert(this->poGPUIndexBuffer);
//	
//	this->isInitialized = true;
//}

void IndexBuffer::SetActive()
{
	DX11Manager::GetDeviceContext()->IASetIndexBuffer
	(
		this->poGPUIndexBuffer,
		DXGI_FORMAT_R32_UINT,
		0
	);
}