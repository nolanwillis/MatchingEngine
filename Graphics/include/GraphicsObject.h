#ifndef GRAPHICS_OBJECT_H
#define GRAPHICS_OBJECT_H

#include "Mat4.h"

class Mesh;
class ShaderObject;

class GraphicsObject
{
public:
	GraphicsObject() = delete;
	GraphicsObject(const GraphicsObject& rhs) = delete;
	GraphicsObject& operator = (const GraphicsObject& rhs) = delete;
	virtual ~GraphicsObject() = default;
	
	void Draw();

	Mesh* GetMesh() const;
	void SetMesh(Mesh* _pMesh);
	void SetShaderObject(ShaderObject* _pShaderObject);

	Mat4 worldMatrix;

protected:
	Mesh* pMesh;
	ShaderObject* pShaderObject;
	
	GraphicsObject(Mesh* pMesh, ShaderObject* pShaderObj);
	
	virtual void SendGPUData();
	virtual void Render();
	virtual void SetState();
	virtual void ResetState();
};

#endif

