#ifndef DX11_MANAGER_H
#define DX11_MANAGER_H

#include <d3d11.h>

// Macro for releasing COM objects.
#define SafeRelease(x) { if(x){x->Release(); x = 0;} }

class DX11Manager
{
public:
	DX11Manager() = delete;
	DX11Manager(const DX11Manager& rhs) = delete;
	DX11Manager operator=(const DX11Manager& rhs) = delete;
	~DX11Manager() = default;

	static void Create(HWND pWindowHandle, HINSTANCE hInstance, bool vSync);
	static void Destroy();
	
	// Function that swaps the swap chain.
	static void Present();
	// Changes the way the clear buffer function works.
	static void ClearDepthStencilBuffer();
	static ID3D11Device* GetDevice();
	static ID3D11DeviceContext* GetDeviceContext();
	static ID3D11RenderTargetView* GetRenderTargetView();
	static ID3D11DepthStencilView* GetDepthStencilView();
	static float GetAspectRatio();
	static void SetDefaultTargetMode();


private:
	static DX11Manager* poInstance;

	HWND dx11WindowHandle;
	ID3D11Device* dx11Device;
	ID3D11DeviceContext* dx11DeviceContext;
	IDXGISwapChain* dx11SwapChain;
	// Render target view for the back buffer of the swap chain.
	ID3D11RenderTargetView* dx11RenderTargetView;
	// Depth/stencil view for use as a depth buffer.
	ID3D11DepthStencilView* dx11DepthStencilView;
	// A texture to associate to the depth stencil view.
	ID3D11Texture2D* dx11DepthStencilBuffer;
	// Define the functionality of the depth/stencil stages.
	ID3D11DepthStencilState* dx11DepthStencilState;
	// Define the functionality of the rasterizer stage.
	ID3D11RasterizerState* dx11RasterizerState;
	D3D11_VIEWPORT dx11Viewport;
	bool vSync;
	
	static DX11Manager* GetInstance();
	
	DX11Manager(HWND pWindowHandle, HINSTANCE hInstance, bool vSync);
	// Find Refresh rate: http://www.rastertek.com/dx11tut03.html
	DXGI_RATIONAL QueryRefreshRate(UINT screenWidth, UINT screenHeight, BOOL vsync);
};

#endif
