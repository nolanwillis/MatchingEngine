#ifndef COLOR_GRAPHICS_OBJECT_H
#define COLOR_GRAPHICS_OBJECT_H

#include "GraphicsObject.h"
#include "ConstantBuffer.h"

class ColorGraphicsObject : public GraphicsObject
{
public:
	ColorGraphicsObject(Mesh* pMesh, ShaderObject* pShaderObj, Vec4& color);
	ColorGraphicsObject() = delete;
	ColorGraphicsObject(const ColorGraphicsObject&) = delete;
	ColorGraphicsObject& operator = (const ColorGraphicsObject&) = delete;
	virtual ~ColorGraphicsObject() = default;

protected:
	virtual void SetState() override;
	virtual void SendGPUData() override;

private:
	// Struct used to load data into the constant buffer.
	ColorData colorData;

	ConstantBuffer cbColorData;
};

#endif;
