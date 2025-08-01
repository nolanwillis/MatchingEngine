#include "ColorGraphicsObject.h"
#include "DX11Manager.h"
#include "Vec4.h"
#include "ShaderObject.h"
#include "Mesh.h"

#include <assert.h>
#include <d3d11.h>

ColorGraphicsObject::ColorGraphicsObject(Mesh* pMesh, ShaderObject* pShaderObj, Vec4& color)
	: 
	GraphicsObject(pMesh, pShaderObj),
	cbColorData(sizeof(Vec4))
{
	this->colorData.color = color;
}

void ColorGraphicsObject::SetState()
{
	GraphicsObject::SetState();
	
	this->cbColorData.SetActive(ConstantBufferSlot::ColorData);
}
void ColorGraphicsObject::SendGPUData()
{
	GraphicsObject::SendGPUData();
	
	cbColorData.Transfer(&this->colorData);
}