#include "ConstantBuffer.h"
#include "DX11Manager.h"

#include <assert.h>

ConstantBuffer::ConstantBuffer(UINT structSize)
	: 
	structSize(structSize),
	poGPUConstantBuffer(nullptr)
{
	assert(structSize > 0);

	// Create the descriptor for the constant buffer.
	D3D11_BUFFER_DESC BufferDesc{ 0 };
	BufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	BufferDesc.ByteWidth = this->structSize;
	BufferDesc.CPUAccessFlags = 0;
	BufferDesc.Usage = D3D11_USAGE_DEFAULT;
	BufferDesc.MiscFlags = 0;
	BufferDesc.StructureByteStride = 0;

	// Create the constant buffer on the GPU. 
	HRESULT hr;
	hr = DX11Manager::GetDevice()->CreateBuffer
	(
		&BufferDesc,
		nullptr,
		&this->poGPUConstantBuffer
	);
	
	assert(SUCCEEDED(hr));
	assert(this->poGPUConstantBuffer);
}
ConstantBuffer::~ConstantBuffer()
{
	SafeRelease(this->poGPUConstantBuffer);
}

void ConstantBuffer::Transfer(void* pBuff)
{
	assert(pBuff);

	DX11Manager::GetDeviceContext()->UpdateSubresource
	(
		poGPUConstantBuffer,
		0,
		nullptr,
		pBuff,
		0,
		0
	);
}
void ConstantBuffer::SetActive(ConstantBufferSlot slot)
{
	DX11Manager::GetDeviceContext()->VSSetConstantBuffers
	(
		(UINT)slot,
		1,
		&this->poGPUConstantBuffer
	);
}