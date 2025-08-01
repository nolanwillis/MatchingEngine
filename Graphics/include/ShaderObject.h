#ifndef SHADER_OBJECT_H
#define SHADER_OBJECT_H

#include <d3d11.h>

class ShaderObject
{
public:
	enum class Name
	{
		Null,
		Color, 
		LitTexture,
	};
	
	ShaderObject::Name name;
	ID3D11InputLayout* poInputLayout;
	ID3D11VertexShader* poVertexShader;
	ID3D11PixelShader* poPixelShader;
	
	ShaderObject(ShaderObject::Name name);
	ShaderObject() = delete;
	ShaderObject(const ShaderObject&) = delete;
	ShaderObject& operator = (const ShaderObject&) = delete;
	virtual ~ShaderObject();

	void CreateVertexShader(const unsigned char* pCompiledVertexShaderObject,
		size_t codeSize);
	void CreatePixelShader(const unsigned char* pCompiledPixelShaderObject,
		size_t codeSize);
	void CreateInputLayout(const unsigned char* compiledVertexShaderObject,
		size_t codeSize,
		D3D11_INPUT_ELEMENT_DESC* pDesc,
		unsigned int SizeInBytes);
	void ActivateShader(ID3D11DeviceContext* pDeviceContext);

	// Get the latest profile for the specified pixel shader type.
	const char* GetLatestProfile_PixelShader() const;
	// Get the latest profile for the specified vertex shader type.
	const char* GetLatestProfile_VertexShader() const;
};

#endif
