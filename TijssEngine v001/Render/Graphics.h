#pragma once
#pragma comment(lib, "d2d1")
#include <Windows.h>
#include <d2d1.h>

#include <memory>
#include "Bitmap.h"
#include <commdlg.h>
#include <wincodec.h>
#include <wincodecsdk.h>

const bool FULL_SCREEN = false;
const bool VSYNC_ENABLED = true;
const float SCREEN_DEPTH = 1000.0f;
const float SCREEN_NEAR = 0.1f;

class GraphicsClass
{
public:
	GraphicsClass();
	GraphicsClass(const GraphicsClass&);
	~GraphicsClass();

	// Initialize device-independent resources.
	bool Initialize(int, int);

	void Shutdown();
	bool Frame();
	D2D_VECTOR_2F GetDPI();

	// Draw content.
	HRESULT OnRender(HWND);

	void TemporaryMovePosition(D2D_VECTOR_3F add)
	{
		bitmapPos.x += add.x;
		bitmapPos.y += add.y;
		bitmapPos.z += add.z;
	}

	int TemporaryGetX()
	{
		return bitmapPos.x;
	}

	int TemporaryGetY()
	{
		return bitmapPos.y;
	}

	// Resize the render target.
	void OnResize(UINT width, UINT height);
private:

	// Initialize device-dependent resources.
	HRESULT CreateDeviceResources(HWND);

	// Release device-dependent resource.
	void DiscardDeviceResources();

	// locate image file (TODO: move to other cpp file)
	bool LocateImageFile(HWND, LPWSTR, DWORD);

	// array of bitmaps to draw
	std::unique_ptr<BitmapClass> bitmapTest = std::make_unique<BitmapClass>();	// 1 temp number to test drawing
	std::unique_ptr<BitmapClass> secondBitmap = std::make_unique<BitmapClass>();	// 1 temp number to test drawing
	D2D_VECTOR_3F bitmapPos;

	// device member vars
	ID2D1Factory* m_pDirect2dFactory;
	ID2D1HwndRenderTarget* m_pRenderTarget;
	ID2D1SolidColorBrush* m_pLightSlateGrayBrush;
	ID2D1SolidColorBrush* m_pCornflowerBlueBrush;
};