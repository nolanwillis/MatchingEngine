#include "DX11Manager.h"
#include "Engine.h"

#include <assert.h>
#include <cstdio>
#include <exception>
#include <windows.h>

LRESULT CALLBACK WindowProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) 
{
	PAINTSTRUCT paintStruct;
	HDC hDC;

	switch (message)
	{
	case WM_PAINT:
	{
		hDC = BeginPaint(hwnd, &paintStruct);
		EndPaint(hwnd, &paintStruct);
	}
	break;

	case WM_KEYDOWN:
		if (wParam < 256)
		{
		}
		break;

	case WM_KEYUP:
		if (wParam < 256)
		{
		}
		break;

	case WM_DESTROY:
	{
		PostQuitMessage(0);
	}
	break;

	default:
		return DefWindowProc(hwnd, message, wParam, lParam);
	}

	return 0;
}

int InitWindow(HWND& pWindowHandle, HINSTANCE hInstance, int cmdShow)
{
	WNDCLASSW wndClass = { 0 };
	wndClass.style = CS_HREDRAW | CS_VREDRAW;
	wndClass.lpfnWndProc = WindowProc;
	wndClass.hInstance = hInstance;
	wndClass.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wndClass.hIcon = nullptr;
	wndClass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wndClass.lpszMenuName = nullptr;
	wndClass.lpszClassName = L"WindowClass";

	if (!RegisterClassW(&wndClass))
	{
		return -1;
	}

	RECT windowRect = { 0, 0, 1200, 800 };
	AdjustWindowRect(&windowRect, WS_OVERLAPPEDWINDOW, FALSE);

	pWindowHandle = CreateWindowW(L"WindowClass", L"Matching Engine",
		WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
		windowRect.right - windowRect.left,
		windowRect.bottom - windowRect.top,
		nullptr, nullptr, hInstance, nullptr);

	assert(pWindowHandle);

	ShowWindow(pWindowHandle, cmdShow);
	UpdateWindow(pWindowHandle);

	return 0;
}

int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE prevInstance, 
	_In_ LPWSTR cmdLine, _In_ int cmdShow)
{
	// Create a console for debugging.
	AllocConsole();
	FILE* fp;
	freopen_s(&fp, "CONOUT$", "w", stdout);
	freopen_s(&fp, "CONIN$", "r", stdin);
	freopen_s(&fp, "CONOUT$", "w", stderr);
	SetConsoleTitle(L"Path To Folkvangr Console");

	// Create the window.
	HWND pWindowHandle = nullptr;
	if (InitWindow(pWindowHandle, hInstance, cmdShow) != 0)
	{
		MessageBox(nullptr, TEXT("Failed to create application window."), TEXT("Error"), 
			MB_OK);
		return -1;
	}
	// Initialize DirectX 11.
	DX11Manager::Create(pWindowHandle, hInstance, true);
	// Run the actual engine.
	Engine* poEngine = new Engine();
	assert(poEngine);
	MSG msg = { 0 };
	static float previousTime = (float)timeGetTime();
	if (!poEngine->LoadContent())
	{
		MessageBox(nullptr, TEXT("Failed to load content."), TEXT("Error"), MB_OK);
		return -1;
	}
	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			// Update values for delta time.
			float currentTime = timeGetTime();
			float deltaTime = (currentTime - previousTime) / 1000.0f;
			previousTime = currentTime;
			// Call the game loop.
			poEngine->Update(deltaTime);
			DX11Manager::ClearDepthStencilBuffer();
			poEngine->Draw();
			// Present the image to the screen.
			DX11Manager::Present();
		}
	}
	poEngine->UnloadContent();
	// Clean up. 
	delete poEngine;
	DX11Manager::Destroy();

	return static_cast<int>(msg.wParam);
}  
