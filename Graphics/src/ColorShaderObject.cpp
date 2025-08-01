#include "ColorShaderObject.h"
#include "ShaderMappings.h"
#include "Color.Px.h"
#include "Color.Vx.h"

ColorShaderObject::ColorShaderObject()
	: ShaderObject(ShaderObject::Name::Color)
{
	// Create the input layout for the vertex shader.
	D3D11_INPUT_ELEMENT_DESC vertexLayoutDesc[] =
	{
		{ 
			"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, (UINT)VertexSlot::Position, 
			offsetof(VertexPos, Position), D3D11_INPUT_PER_VERTEX_DATA, 0 
		}
	};

	this->CreateVertexShader(Color_VxShader, sizeof(Color_VxShader));
	this->CreateInputLayout(Color_VxShader, sizeof(Color_VxShader), vertexLayoutDesc, 
		sizeof(vertexLayoutDesc));
	this->CreatePixelShader(Color_PxShader, sizeof(Color_PxShader));
}


