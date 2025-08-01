#ifndef INDEX_BUFFER_H
#define INDEX_BUFFER_H

#include "ShaderMappings.h"

#include <d3d11.h>

class IndexBuffer
{
public:
	UINT numBytes;
	ID3D11Buffer* poGPUIndexBuffer;
	
	IndexBuffer();
	IndexBuffer(UINT numBytes, void* pData);
	IndexBuffer(const IndexBuffer&) = delete;
	IndexBuffer& operator=(const IndexBuffer&) = delete;
	virtual ~IndexBuffer();

	// Initializes the index buffer. Should only called if the index buffer was
	// created using the default constructor.
	//void Initialize(size_t numBytes, void* pData);
	// Binds the index buffer to the GPU pipeline.
	void SetActive();		

private:
	bool isInitialized;
};

#endif
