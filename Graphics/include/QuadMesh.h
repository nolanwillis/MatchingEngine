#ifndef QUAD_MESH_H
#define QUAD_MESH_H

#include "Mesh.h"

#include <cstdint>

class VertexBuffer;
class IndexBuffer;

class QuadMesh : public Mesh
{
public:
	QuadMesh();
	QuadMesh(const QuadMesh& rhs) = delete;
	QuadMesh& operator = (QuadMesh& rhs) = delete;
	virtual ~QuadMesh();

	virtual void Activate() override;
	virtual void Draw() override;

private:
	VertexBuffer* poVBPos;
	VertexBuffer* poVBColor;
	VertexBuffer* poVBNorm;
	VertexBuffer* poVBTexCoord;
	IndexBuffer*  poIndexBuffer;

	// Data to load into the buffers.
	VertexPos* poVertexPos;
	VertexColor* poVertexColor;
	VertexNorm* poVertexNorm;
	VertexTexCoord* poVertexTexCoord;
	uint32_t* poIndices;
};

#endif
