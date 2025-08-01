#include "DX11Manager.h"
#include "Colors.h"
#include "Vec4.h"

#include <assert.h>
#include <cstdio>
#include <d3dcompiler.h>
#include <exception>

#if _DEBUG
#define createDeviceFlags_define  D3D11_CREATE_DEVICE_DEBUG
#else
#define createDeviceFlags_define  0
#endif

DX11Manager* DX11Manager::poInstance = nullptr;

void DX11Manager::Create(HWND pWindowHandle, HINSTANCE hInstance, bool vSync)
{
	assert(!poInstance);
	if (!poInstance)
	{
		poInstance = new DX11Manager(pWindowHandle, hInstance, vSync);
	}
}
void DX11Manager::Destroy()
{
	DX11Manager* pMan = DX11Manager::GetInstance();
	assert(pMan);

	SafeRelease(pMan->dx11DepthStencilView);
	SafeRelease(pMan->dx11RenderTargetView);
	SafeRelease(pMan->dx11DepthStencilBuffer);
	SafeRelease(pMan->dx11DepthStencilState);
	SafeRelease(pMan->dx11RasterizerState);
	SafeRelease(pMan->dx11SwapChain);
	SafeRelease(pMan->dx11DeviceContext);

#ifdef _DEBUG
	HRESULT hr = S_OK;

	// Now we set up the Debug interface, to be queried on shutdown
	ID3D11Debug* debugDev = nullptr;
	hr = pMan->dx11Device->QueryInterface(__uuidof(ID3D11Debug), 
		reinterpret_cast<void**>(&debugDev));

	//debugDev->ReportLiveDeviceObjects(D3D11_RLDO_IGNORE_INTERNAL);
	//debugDev->ReportLiveDeviceObjects(D3D11_RLDO_DETAIL);
	//debugDev->ReportLiveDeviceObjects(D3D11_RLDO_SUMMARY | D3D11_RLDO_DETAIL);
	SafeRelease(debugDev);
#endif

	SafeRelease(pMan->dx11Device);

	delete poInstance;
}

void DX11Manager::Present()
{
	DX11Manager* pMan = DX11Manager::GetInstance();
	assert(pMan);
	assert(pMan->dx11SwapChain);
	if (pMan->vSync)
	{
		pMan->dx11SwapChain->Present(1, 0);
	}
	else
	{
		pMan->dx11SwapChain->Present(0, 0);
	}
}
void DX11Manager::ClearDepthStencilBuffer()
{
	DX11Manager* pMan = DX11Manager::GetInstance();
	assert(pMan);
#ifdef _DEBUG
	const Vec4 ClearColor = Colors::Teal;
#else
	const Vec4 ClearColor = Colors::Wheat;
#endif
	float clearDepth = 1.0f;
	uint8_t clearStencil = 0;
	DX11Manager::GetDeviceContext()->ClearRenderTargetView(DX11Manager::GetRenderTargetView(),
		(const float*)&ClearColor);
	DX11Manager::GetDeviceContext()->ClearDepthStencilView(DX11Manager::GetDepthStencilView(),
		D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, clearDepth, clearStencil);
}
ID3D11Device* DX11Manager::GetDevice()
{
	DX11Manager* pMan = DX11Manager::GetInstance();
	assert(pMan);
	assert(pMan->dx11Device);
	return pMan->dx11Device;
}
ID3D11DeviceContext* DX11Manager::GetDeviceContext()
{
	DX11Manager* pMan = DX11Manager::GetInstance();
	assert(pMan);
	assert(pMan->dx11DeviceContext);
	return pMan->dx11DeviceContext;
}
ID3D11RenderTargetView* DX11Manager::GetRenderTargetView()
{
	DX11Manager* pMan = DX11Manager::GetInstance();
	assert(pMan);
	assert(pMan->dx11RenderTargetView);
	return pMan->dx11RenderTargetView;
}
ID3D11DepthStencilView* DX11Manager::GetDepthStencilView()
{
	DX11Manager* pMan = DX11Manager::GetInstance();
	assert(pMan);
	assert(pMan->dx11DepthStencilView);
	return pMan->dx11DepthStencilView;
}
float DX11Manager::GetAspectRatio()
{
	DX11Manager* pMan = DX11Manager::GetInstance();
	assert(pMan);
	RECT clientRect;
	GetClientRect(pMan->dx11WindowHandle, &clientRect);

	float clientWidth = static_cast<float>(clientRect.right - clientRect.left);
	float clientHeight = static_cast<float>(clientRect.bottom - clientRect.top);

	float ratio = clientWidth / clientHeight;

	return ratio;
}
void DX11Manager::SetDefaultTargetMode()
{
	DX11Manager* pMan = DX11Manager::GetInstance();
	assert(pMan);
	assert(pMan->dx11Device);
	assert(pMan->dx11DeviceContext);

	pMan->dx11DeviceContext->RSSetState(pMan->dx11RasterizerState);
	pMan->dx11DeviceContext->RSSetViewports(1, &pMan->dx11Viewport);
	pMan->dx11DeviceContext->OMSetRenderTargets(1, &pMan->dx11RenderTargetView, 
		pMan->dx11DepthStencilView);
	pMan->dx11DeviceContext->OMSetDepthStencilState(pMan->dx11DepthStencilState, 1);
}

DX11Manager* DX11Manager::GetInstance()
{
	// Ensure Create() has been called.
	assert(poInstance != nullptr);
	return poInstance;
}

DX11Manager::DX11Manager(HWND pWindowHandle, HINSTANCE hInstance, bool vSync)
	:
	dx11WindowHandle(pWindowHandle),
	dx11Device(nullptr),
	dx11DeviceContext(nullptr),
	dx11SwapChain(nullptr),
	dx11RenderTargetView(nullptr),
	dx11DepthStencilView(nullptr),
	dx11DepthStencilBuffer(nullptr),
	dx11DepthStencilState(nullptr),
	dx11RasterizerState(nullptr),
	dx11Viewport(),
	vSync(vSync)
{
	assert(pWindowHandle != nullptr);

	RECT clientRect;
	GetClientRect(pWindowHandle, &clientRect);

	// Compute the exact client dimensions. This will be used to initialize the render 
	// targets for our swap chain.
	unsigned int clientWidth = clientRect.right - clientRect.left;
	unsigned int clientHeight = clientRect.bottom - clientRect.top;

	DXGI_SWAP_CHAIN_DESC swapChainDesc{ 0 };

	// Create two buffers (front + back).
	swapChainDesc.BufferCount = 2;
	swapChainDesc.BufferDesc.Width = clientWidth;
	swapChainDesc.BufferDesc.Height = clientHeight;
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	// Gets the refresh rate of the monitor (60Hz unless you have a crazy fast monitor).
	swapChainDesc.BufferDesc.RefreshRate = QueryRefreshRate(clientWidth, clientHeight, vSync);
	// Use the surface or resource as an output render target.
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	// Output window.
	swapChainDesc.OutputWindow = pWindowHandle;
	// multisample setup
	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.SampleDesc.Quality = 0;
	// Drop the back buffer after flip.
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
	// Sub window of the screen.
	swapChainDesc.Windowed = TRUE;

	UINT createDeviceFlags = createDeviceFlags_define;

	// These are the feature levels that we will accept.
	D3D_FEATURE_LEVEL featureLevels[] =
	{
		D3D_FEATURE_LEVEL_11_1,
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,
		D3D_FEATURE_LEVEL_9_3,
		D3D_FEATURE_LEVEL_9_2,
		D3D_FEATURE_LEVEL_9_1
	};

	// This will be the feature level that 
	// is used to create our device and swap chain.
	D3D_FEATURE_LEVEL featureLevel;

	HRESULT hr = D3D11CreateDeviceAndSwapChain
	(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		createDeviceFlags,
		featureLevels,
		_countof(featureLevels),
		D3D11_SDK_VERSION,
		&swapChainDesc,
		&dx11SwapChain,
		&dx11Device,
		&featureLevel,
		&dx11DeviceContext
	);

	assert(SUCCEEDED(hr));

	// The Direct3D device and swap chain were successfully created.
	// Now we need to initialize the buffers of the swap chain.
	// Next initialize the back buffer of the swap chain and associate it to a 
	// render target view.
	ID3D11Texture2D* backBuffer = nullptr;
	hr = dx11SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&backBuffer);
	assert(SUCCEEDED(hr));

	hr = dx11Device->CreateRenderTargetView(backBuffer, nullptr, &dx11RenderTargetView);
	assert(SUCCEEDED(hr));

	SafeRelease(backBuffer);

	// Create the depth buffer for use with the depth/stencil view.
	D3D11_TEXTURE2D_DESC depthStencilBufferDesc{ 0 };

	depthStencilBufferDesc.ArraySize = 1;
	depthStencilBufferDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthStencilBufferDesc.CPUAccessFlags = 0; // No CPU access required.
	// 24-bit depth/8-bit stencil --> future make it 32 bit depth
	depthStencilBufferDesc.Format = DXGI_FORMAT_D32_FLOAT;
	depthStencilBufferDesc.Width = clientWidth;
	depthStencilBufferDesc.Height = clientHeight;
	depthStencilBufferDesc.MipLevels = 1;
	depthStencilBufferDesc.SampleDesc.Count = 1;
	depthStencilBufferDesc.SampleDesc.Quality = 0;
	depthStencilBufferDesc.Usage = D3D11_USAGE_DEFAULT;

	hr = dx11Device->CreateTexture2D(&depthStencilBufferDesc, nullptr,
		&dx11DepthStencilBuffer);
	assert(SUCCEEDED(hr));

	hr = dx11Device->CreateDepthStencilView(dx11DepthStencilBuffer, nullptr,
		&dx11DepthStencilView);
	assert(SUCCEEDED(hr));

	// Setup depth/stencil state.
	D3D11_DEPTH_STENCIL_DESC depthStencilStateDesc{ 0 };

	depthStencilStateDesc.DepthEnable = TRUE;
	depthStencilStateDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	depthStencilStateDesc.DepthFunc = D3D11_COMPARISON_LESS;
	// not using any stencil... its disabled
	depthStencilStateDesc.StencilEnable = FALSE;

	hr = dx11Device->CreateDepthStencilState(&depthStencilStateDesc, 
		&dx11DepthStencilState);

	// Setup rasterizer state.
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
	hr = dx11Device->CreateRasterizerState(&rasterizerDesc, &dx11RasterizerState);
	assert(SUCCEEDED(hr));

	// Initialize the viewport to occupy the entire client area.
	dx11Viewport.Width = static_cast<float>(clientWidth);
	dx11Viewport.Height = static_cast<float>(clientHeight);
	dx11Viewport.TopLeftX = 0.0f;
	dx11Viewport.TopLeftY = 0.0f;
	dx11Viewport.MinDepth = 0.0f;
	dx11Viewport.MaxDepth = 1.0f;
}
DXGI_RATIONAL DX11Manager::QueryRefreshRate(UINT screenWidth, UINT screenHeight, 
	BOOL vsync)
{
	DXGI_RATIONAL refreshRate = { 0, 1 };
	if (vsync)
	{
		IDXGIFactory* factory = nullptr;
		IDXGIAdapter* adapter;
		IDXGIOutput* adapterOutput;
		DXGI_MODE_DESC* displayModeList;

		// Create a DirectX graphics interface factory.
		HRESULT hr = CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&factory);
		if (FAILED(hr))
		{
			MessageBox(0,
				TEXT("Could not create DXGIFactory instance."),
				TEXT("Query Refresh Rate"),
				MB_OK);

			throw new std::exception("Failed to create DXGIFactory.");
		}

		hr = factory->EnumAdapters(0, &adapter);
		if (FAILED(hr))
		{
			MessageBox(0,
				TEXT("Failed to enumerate adapters."),
				TEXT("Query Refresh Rate"),
				MB_OK);

			throw new std::exception("Failed to enumerate adapters.");
		}

		hr = adapter->EnumOutputs(0, &adapterOutput);
		if (FAILED(hr))
		{
			MessageBox(0,
				TEXT("Failed to enumerate adapter outputs."),
				TEXT("Query Refresh Rate"),
				MB_OK);

			throw new std::exception("Failed to enumerate adapter outputs.");
		}

		UINT numDisplayModes;
		hr = adapterOutput->GetDisplayModeList(DXGI_FORMAT_B8G8R8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &numDisplayModes, nullptr);
		if (FAILED(hr))
		{
			MessageBox(0,
				TEXT("Failed to query display mode list."),
				TEXT("Query Refresh Rate"),
				MB_OK);

			throw new std::exception("Failed to query display mode list.");
		}

		displayModeList = new DXGI_MODE_DESC[numDisplayModes];
		assert(displayModeList);

		hr = adapterOutput->GetDisplayModeList(DXGI_FORMAT_B8G8R8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &numDisplayModes, displayModeList);
		if (FAILED(hr))
		{
			MessageBox(0,
				TEXT("Failed to query display mode list."),
				TEXT("Query Refresh Rate"),
				MB_OK);

			throw new std::exception("Failed to query display mode list.");
		}

		// Now store the refresh rate of the monitor that matches the width and height of 
		// the requested screen.
		for (UINT i = 0; i < numDisplayModes; ++i)
		{
			if (displayModeList[i].Width == screenWidth && 
				displayModeList[i].Height == screenHeight)
			{
				refreshRate = displayModeList[i].RefreshRate;
			}
		}

		delete[] displayModeList;
		SafeRelease(adapterOutput);
		SafeRelease(adapter);
		SafeRelease(factory);
	}

	return refreshRate;
}

