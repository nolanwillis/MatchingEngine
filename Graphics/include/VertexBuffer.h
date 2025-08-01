#ifndef VERTEX_BUFFER_H
#define VERTEX_BUFFER_H

#include "ShaderMappings.h"
#include "Vec3.h"
#include "Vec2.h"

#include <d3d11.h>

class VertexBuffer
{
public:
	UINT numVerts;
	UINT strideSize;
	UINT offset;
	ID3D11Buffer* poGPUVertexBuffer;
	
	VertexBuffer();
	VertexBuffer(UINT numVerts, UINT strideSize, void* pData);
	VertexBuffer(const VertexBuffer& r) = delete;
	VertexBuffer& operator=(const VertexBuffer&) = delete;
	virtual ~VertexBuffer();

	// Initializes the vertex buffer. Should only called if the vertex buffer was
	// created using the default constructor.
	//void Initialize(UINT numVerts, UINT strideSize, void* pData);
	// Binds the vertex buffer to the GPU pipeline.
	void SetActive(VertexSlot slot);

private:
	bool isInitialized;
};

#endif
