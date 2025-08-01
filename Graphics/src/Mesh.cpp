#include "Mesh.h"
#include "DX11Manager.h"
#include "ShaderMappings.h"

#include <assert.h>

Mesh::Mesh(Mesh::Name name, unsigned int numVerts, unsigned int numIndices)
	:
	name(name),
	numVerts(numVerts),
	numIndices(numIndices),
	CBModelData(sizeof(Mat4))
{}

void Mesh::SendMeshData(Mat4* pWorld)
{
	assert(pWorld);
	modelData.world = *pWorld;
	CBModelData.Transfer(&modelData);
}	