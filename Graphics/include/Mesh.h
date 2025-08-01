#ifndef MESH_H
#define MESH_H

#include "MathEngine.h"
#include "ConstantBuffer.h"

#include <d3d11.h>

class DNode;

class Mesh
{
public:
	enum class Name
	{
		Quad,
	};

	Name name;

	Mesh(Mesh::Name name, unsigned int numVerts = 0, unsigned int numIndicies = 0);
	Mesh() = delete;
	Mesh(Mesh&) = delete;
	Mesh& operator = (Mesh&) = delete;
	virtual ~Mesh() = default;

	// Binds the vertex and constant buffers to the GPU pipeline.
	virtual void Activate() = 0;
	// Tells the GPU pipeline to draw using the index data of this mesh.
	virtual void Draw() = 0;
	virtual void SendMeshData(Mat4* pWorld);

protected:
	unsigned int numVerts;
	unsigned int numIndices;

	// Struct used to load data into the constant buffer.
	ModelData modelData;
	
	ConstantBuffer CBModelData;
};

#endif
