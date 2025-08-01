#include "NullShaderObject.h"
#include "ShaderMappings.h"
#include "Null.Px.h"
#include "Null.Vx.h"

NullShaderObject::NullShaderObject()
	: ShaderObject(ShaderObject::Name::Null)
{
	// Create the input layout for the vertex shader.
	D3D11_INPUT_ELEMENT_DESC vertexLayoutDesc[] =
	{
		{ 
			"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, (UINT)VertexSlot::Position, 
			offsetof(VertexPos, Position), D3D11_INPUT_PER_VERTEX_DATA, 0 
		},
		{ 
			"COLOR", 0, DXGI_FORMAT_R32G32B32_FLOAT, (UINT)VertexSlot::Color, 
			offsetof(VertexColor, Color),  D3D11_INPUT_PER_VERTEX_DATA, 0 
		}
	};

	this->CreateVertexShader(Null_VxShader, sizeof(Null_VxShader));
	this->CreateInputLayout(Null_VxShader, sizeof(Null_VxShader), vertexLayoutDesc, 
		sizeof(vertexLayoutDesc));
	this->CreatePixelShader(Null_PxShader, sizeof(Null_PxShader));
}