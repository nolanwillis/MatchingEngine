#ifndef NULL_SHADER_OBJECT_H
#define NULL_SHADER_OBJECT_H

#include "ShaderObject.h"

class NullShaderObject : public ShaderObject
{
public:
	NullShaderObject();
	NullShaderObject(const NullShaderObject& rhs) = delete;
	NullShaderObject& operator = (const NullShaderObject& rhs) = delete;
	virtual ~NullShaderObject() = default;
};

#endif
