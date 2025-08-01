#ifndef CONSTANT_BUFFER_H
#define CONSTANT_BUFFER_H

#include "Mat4.h"
#include "ShaderMappings.h"
#include "Vec3.h"

#include <d3d11.h>

// Structs used to load data into a constant buffer.
struct CameraData
{
	Mat4 view; 
	Mat4 proj;
};
struct ModelData
{
	Mat4 world;
};
struct ColorData
{
	Vec4 color;
};
struct LightPos
{
	Vec3 position;
};

class ConstantBuffer
{
public:
	UINT structSize;
	ID3D11Buffer* poGPUConstantBuffer;
	
	ConstantBuffer() = delete;
	ConstantBuffer(const ConstantBuffer& r) = delete;
	ConstantBuffer& operator=(const ConstantBuffer&) = delete;
	virtual ~ConstantBuffer();

	ConstantBuffer(UINT structSize);

	// Transfers data to the constant buffer on the GPU.
	void Transfer(void* pBuff);
	// Binds the constant buffer to the vertex shader.
	void SetActive(ConstantBufferSlot slot);
};

#endif
