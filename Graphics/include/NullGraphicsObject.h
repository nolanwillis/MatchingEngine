#ifndef NULL_GRAPHICS_OBJECT_H
#define NULL_GRAPHICS_OBJECT_H

#include "GraphicsObject.h"

class Mesh;

class NullGraphicsObject : public GraphicsObject
{
public:
	NullGraphicsObject();
	NullGraphicsObject(const NullGraphicsObject&) = delete;
	NullGraphicsObject& operator = (const NullGraphicsObject&) = delete;
	virtual ~NullGraphicsObject() = default;
};

#endif

