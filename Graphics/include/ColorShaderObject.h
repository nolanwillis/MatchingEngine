#ifndef COLOR_SHADER_OBJECT_H
#define COLOR_SHADER_OBJECT_H

#include "ShaderObject.h"

class ColorShaderObject : public ShaderObject
{
public:
	ColorShaderObject();
	ColorShaderObject(const ColorShaderObject& rhs) = delete;
	ColorShaderObject& operator = (const ColorShaderObject& rhs) = delete;
	virtual ~ColorShaderObject() = default;
};

#endif
