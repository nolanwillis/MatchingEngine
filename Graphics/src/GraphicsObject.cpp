#include "GraphicsObject.h"
#include "DX11Manager.h"
#include "ShaderObject.h"
#include "Mesh.h"

#include <assert.h>

GraphicsObject::GraphicsObject(Mesh* pMesh, ShaderObject* pShaderObj)
	:
	worldMatrix(Identity),
	pMesh(pMesh),
	pShaderObject(pShaderObj)
{}

void GraphicsObject::Draw()
{
	this->SetState();
	this->SendGPUData();
	this->Render();
	this->ResetState();
}

Mesh* GraphicsObject::GetMesh() const
{
	return this->pMesh;
}
void GraphicsObject::SetMesh(Mesh* _pMesh)
{
	assert(_pMesh);
	this->pMesh = _pMesh;
}
void GraphicsObject::SetShaderObject(ShaderObject* _pShaderObject)
{
	assert(_pShaderObject);
	this->pShaderObject = _pShaderObject;
}

void GraphicsObject::SetState()
{
	// Create the rasterizer descriptor.
	D3D11_RASTERIZER_DESC rasterizerDesc;
	memset(&rasterizerDesc, 0, sizeof(D3D11_RASTERIZER_DESC));
	rasterizerDesc.AntialiasedLineEnable = FALSE;
	rasterizerDesc.CullMode = D3D11_CULL_FRONT;
	rasterizerDesc.DepthBias = 0;
	rasterizerDesc.DepthBiasClamp = 0.0f;
	rasterizerDesc.DepthClipEnable = TRUE;
	rasterizerDesc.FillMode = D3D11_FILL_SOLID;
	rasterizerDesc.FrontCounterClockwise = FALSE;
	rasterizerDesc.MultisampleEnable = FALSE;
	rasterizerDesc.ScissorEnable = FALSE;
	rasterizerDesc.SlopeScaledDepthBias = 0.0f;

	// Create the rasterizer state object.
	ID3D11RasterizerState* pRasterState;
	HRESULT hr;
	hr = DX11Manager::GetDevice()->CreateRasterizerState(&rasterizerDesc, &pRasterState);
	assert(SUCCEEDED(hr));

	DX11Manager::GetDeviceContext()->RSSetState(pRasterState);

	SafeRelease(pRasterState);
}
void GraphicsObject::SendGPUData()
{
	pShaderObject->ActivateShader(DX11Manager::GetDeviceContext());
	this->pMesh->SendMeshData(&this->worldMatrix);
	this->pMesh->Activate();
}
void GraphicsObject::Render()
{
	pMesh->Draw();
}
void GraphicsObject::ResetState()
{
	// Create the rasterizer descriptor.
	D3D11_RASTERIZER_DESC rasterizerDesc;
	memset(&rasterizerDesc, 0, sizeof(D3D11_RASTERIZER_DESC));
	rasterizerDesc.AntialiasedLineEnable = FALSE;
	rasterizerDesc.CullMode = D3D11_CULL_FRONT;
	rasterizerDesc.DepthBias = 0;
	rasterizerDesc.DepthBiasClamp = 0.0f;
	rasterizerDesc.DepthClipEnable = TRUE;
	rasterizerDesc.FillMode = D3D11_FILL_SOLID;
	rasterizerDesc.FrontCounterClockwise = FALSE;
	rasterizerDesc.MultisampleEnable = FALSE;
	rasterizerDesc.ScissorEnable = FALSE;
	rasterizerDesc.SlopeScaledDepthBias = 0.0f;

	// Create the rasterizer state object.
	ID3D11RasterizerState* pRasterState;
	HRESULT hr;
	hr = DX11Manager::GetDevice()->CreateRasterizerState(&rasterizerDesc, &pRasterState);
	assert(SUCCEEDED(hr));

	DX11Manager::GetDeviceContext()->RSSetState(pRasterState);

	SafeRelease(pRasterState);
}
