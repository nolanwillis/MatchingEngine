#include "QuadMesh.h"
#include "DX11Manager.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"

QuadMesh::QuadMesh()
	: Mesh(Mesh::Name::Quad, 6, 6)
{
	this->poVertexPos = new VertexPos[this->numVerts]
	{
		// Triangle 0
		Vec3(-0.5f,  0.5f, 0.0f),
		Vec3(0.5f, 0.5f, 0.0f),
		Vec3(0.5f, -0.5f, 0.0f),
		// Triangle 1
		Vec3(-0.5f, 0.5f, 0.0f),
		Vec3(0.5f, -0.5f, 0.0f),
		Vec3(-0.5f,  -0.5f, 0.0f),
	};
	this->poVertexColor = new VertexColor[this->numVerts]
	{
		Vec3(1.0f, 0.0f, 0.0f),
		Vec3(1.0f, 0.0f, 0.0f),
		Vec3(1.0f, 0.0f, 0.0f),
		Vec3(1.0f, 0.0f, 0.0f),
		Vec3(1.0f, 0.0f, 0.0f),
		Vec3(1.0f, 0.0f, 0.0f),
	};
	this->poVertexNorm = new VertexNorm[this->numVerts]
	{
		// Triangle 0
		Vec3(0.0f, 0.0f, 1.0f),
		Vec3(0.0f, 0.0f, 1.0f),
		Vec3(0.0f, 0.0f, 1.0f),
		//// Triangle 1
		Vec3(0.0f, 0.0f, 1.0f),
		Vec3(0.0f, 0.0f, 1.0f),
		Vec3(0.0f, 0.0f, 1.0f),
	};
	this->poVertexTexCoord = new VertexTexCoord[this->numVerts]
	{
		// Triangle 0
		Vec2(0.0f, 0.0f),
		Vec2(1.0f, 0.0f),
		Vec2(1.0f, 1.0f),
		// Triangle 1
		Vec2(0.0f, 0.0f),
		Vec2(1.0f, 1.0f),
		Vec2(0.0f, 1.0f),
	};
	this->poIndices = new uint32_t[this->numIndices]
	{
		2, 1, 0,
		5, 4, 3
	};
	
	poVBPos = new VertexBuffer(this->numVerts, sizeof(VertexPos), poVertexPos);
	poVBColor = new VertexBuffer(this->numVerts, sizeof(VertexColor), poVertexColor);
	poVBNorm = new VertexBuffer(this->numVerts, sizeof(VertexNorm), poVertexNorm);
	poVBTexCoord = new VertexBuffer(this->numVerts, sizeof(VertexTexCoord), poVertexTexCoord);
	poIndexBuffer = new IndexBuffer(this->numIndices * sizeof(uint32_t), poIndices);	
}
QuadMesh::~QuadMesh()
{
	delete poIndexBuffer;
	delete poVBTexCoord;
	delete poVBNorm;
	delete poVBColor;
	delete poVBPos;
	delete[] poIndices;
	delete[] poVertexTexCoord;
	delete[] poVertexNorm;
	delete[] poVertexColor;
	delete[] poVertexPos;
}

void QuadMesh::Activate()
{
	this->poVBPos->SetActive(VertexSlot::Position);
	this->poVBColor->SetActive(VertexSlot::Color);
	this->poVBNorm->SetActive(VertexSlot::Norm);
	this->poVBTexCoord->SetActive(VertexSlot::TexCoord);
	
	CBModelData.SetActive(ConstantBufferSlot::MeshData);
}
void QuadMesh::Draw()
{
	this->poIndexBuffer->SetActive();
	DX11Manager::GetDeviceContext()->IASetPrimitiveTopology(
		D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	DX11Manager::GetDeviceContext()->DrawIndexed(this->numIndices, 0, 0);
}
