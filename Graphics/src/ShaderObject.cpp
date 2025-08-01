#include "ShaderObject.h"
#include "DX11Manager.h"

#include <assert.h>
#include <string>

ShaderObject::ShaderObject(ShaderObject::Name name)
	: 
	name(name), 
	poInputLayout(nullptr),
	poVertexShader(nullptr), 
	poPixelShader(nullptr)
{}
ShaderObject::~ShaderObject()
{
	SafeRelease(poInputLayout);
	SafeRelease(poVertexShader);
	SafeRelease(poPixelShader);
}

void ShaderObject::CreateVertexShader(const unsigned char* pCompiledVertexShaderObject,
	size_t codeSize)
{
	assert(pCompiledVertexShaderObject);

	HRESULT hr;
	hr = DX11Manager::GetDevice()->CreateVertexShader(pCompiledVertexShaderObject, codeSize, nullptr, &poVertexShader);
	assert(SUCCEEDED(hr));

	assert(std::string("vs_5_0") == (GetLatestProfile_VertexShader()));

	assert(poVertexShader);
}
void ShaderObject::CreatePixelShader(const unsigned char* pCompiledPixelShaderObject,
	size_t codeSize)
{
	assert(pCompiledPixelShaderObject);

	HRESULT hr;
	hr = DX11Manager::GetDevice()->CreatePixelShader(pCompiledPixelShaderObject, codeSize, nullptr, &poPixelShader);
	assert(SUCCEEDED(hr));

	assert(std::string("ps_5_0") == (GetLatestProfile_PixelShader()));

	assert(poPixelShader);
}
void ShaderObject::CreateInputLayout(const unsigned char* pCompiledVertexShaderObject,
	size_t codeSize, D3D11_INPUT_ELEMENT_DESC* pDesc, unsigned int SizeInBytes)
{
	assert(pCompiledVertexShaderObject);
	assert(pDesc);

	HRESULT hr;
	hr = DX11Manager::GetDevice()->CreateInputLayout(pDesc,
		SizeInBytes / sizeof(D3D11_INPUT_ELEMENT_DESC),
		pCompiledVertexShaderObject,
		codeSize,
		&poInputLayout);
	assert(SUCCEEDED(hr));

	assert(poInputLayout);
}
void ShaderObject::ActivateShader(ID3D11DeviceContext* pDeviceContext)
{
	assert(pDeviceContext);

	pDeviceContext->VSSetShader(poVertexShader, nullptr, 0);
	pDeviceContext->IASetInputLayout(poInputLayout);
	pDeviceContext->PSSetShader(poPixelShader, nullptr, 0);
}

const char* ShaderObject::GetLatestProfile_VertexShader() const
{
	// Query the current feature level:
	D3D_FEATURE_LEVEL featureLevel = DX11Manager::GetDevice()->GetFeatureLevel();

	switch (featureLevel)
	{
	case D3D_FEATURE_LEVEL_11_1:
	case D3D_FEATURE_LEVEL_11_0:
	{
		return "vs_5_0";
	}
	break;

	case D3D_FEATURE_LEVEL_10_1:
	{
		return "vs_4_1";
	}
	break;

	case D3D_FEATURE_LEVEL_10_0:
	{
		return "vs_4_0";
	}
	break;

	case D3D_FEATURE_LEVEL_9_3:
	{
		return "vs_4_0_level_9_3";
	}
	break;

	case D3D_FEATURE_LEVEL_9_2:
	case D3D_FEATURE_LEVEL_9_1:
	{
		return "vs_4_0_level_9_1";
	}
	break;

	default:
		assert(false);

	}

	return "";
}
const char* ShaderObject::GetLatestProfile_PixelShader() const
{
	// Query the current feature level:
	D3D_FEATURE_LEVEL featureLevel = DX11Manager::GetDevice()->GetFeatureLevel();
	switch (featureLevel)
	{
	case D3D_FEATURE_LEVEL_11_1:
	case D3D_FEATURE_LEVEL_11_0:
	{
		return "ps_5_0";
	}
	break;
	case D3D_FEATURE_LEVEL_10_1:
	{
		return "ps_4_1";
	}
	break;
	case D3D_FEATURE_LEVEL_10_0:
	{
		return "ps_4_0";
	}
	break;
	case D3D_FEATURE_LEVEL_9_3:
	{
		return "ps_4_0_level_9_3";
	}
	break;
	case D3D_FEATURE_LEVEL_9_2:
	case D3D_FEATURE_LEVEL_9_1:
	{
		return "ps_4_0_level_9_1";
	}
	break;
	}
	return "";
}


