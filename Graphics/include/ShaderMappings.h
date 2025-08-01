#ifndef SHADER_MAPPINGS_H
#define SHADER_MAPPINGS_H

#include "Vec2.h"
#include "Vec3.h"

// Needed for UINT.
#include <d3d11.h>

// Enums that represent the index for shader resources, buffers, etc.
enum class VertexSlot : UINT
{
	Position,
	Color,
	Norm,
	TexCoord
};
enum class ConstantBufferSlot : UINT
{
	CameraData, 
	MeshData, 
	ColorData,
	LightPos,
};
enum class ShaderResourceBufferSlot : UINT
{
	TextureA      
};
enum class ShaderSamplerSlot : UINT
{
	SampleA
};

// Structs for defining the input layout of a vertex shader.
struct VertexColor
{
	Vec3 Color;
};
struct VertexPos
{
	Vec3 Position;
};
struct VertexNorm
{
	Vec3 Norm;
};
struct VertexTexCoord
{
	Vec2 TexCoord;
};

#endif
