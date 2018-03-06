#include "Graphics.h"

Graphics::Graphics()
{
	m_Factory = NULL;
	m_RenderTarget = NULL;
	m_Brush = NULL;
}

Graphics::~Graphics()
{
	if(m_Factory) m_Factory->Release();
	if(m_RenderTarget) m_RenderTarget->Release();
	if (m_Brush) m_Brush->Release();

}


bool Graphics::Init(HWND windowHandle)
{
	HRESULT result = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &m_Factory);
	if (result != S_OK) return false;
	
	RECT rect;
	GetClientRect(windowHandle, &rect);

	result = m_Factory->CreateHwndRenderTarget(
				D2D1::RenderTargetProperties(),
				D2D1::HwndRenderTargetProperties(windowHandle, D2D1::SizeU(rect.right, rect.bottom)),
				&m_RenderTarget);
	if (result != S_OK) return false;

	result = m_RenderTarget->CreateSolidColorBrush(D2D1::ColorF(0,0,0,0), &m_Brush);
	if (result != S_OK) return false;

	return true;
}

void Graphics::ClearScreen(float r, float g, float b)
{
	m_RenderTarget->Clear(D2D1::ColorF(r,g,b));
}

void Graphics::DrawCircle(float x, float y, float radius, float r, float g, float b, float a)
{
	m_Brush->SetColor(D2D1::ColorF(r,g,b,a));

	m_RenderTarget->DrawEllipse(D2D1::Ellipse(D2D1::Point2F(x,y), radius, radius), m_Brush, 3.0f);
}
//// test global var
//LPWSTR gFileName;
//
//GraphicsClass::GraphicsClass() :
//	m_pDirect2dFactory(NULL),
//	m_pRenderTarget(NULL),
//	m_pLightSlateGrayBrush(NULL),
//	m_pCornflowerBlueBrush(NULL)
//{
//	bitmapPos.x = 0;
//	bitmapPos.y = 0;
//	bitmapPos.z = 0;
//}
//
//
//GraphicsClass::GraphicsClass(const GraphicsClass& other):
//m_pDirect2dFactory(NULL),
//m_pRenderTarget(NULL),
//m_pLightSlateGrayBrush(NULL),
//m_pCornflowerBlueBrush(NULL)
//{
//}
//
//
//GraphicsClass::~GraphicsClass()
//{
//	SafeRelease(&m_pDirect2dFactory);
//	SafeRelease(&m_pRenderTarget);
//	SafeRelease(&m_pLightSlateGrayBrush);
//	SafeRelease(&m_pCornflowerBlueBrush);
//}
//
//// Initialize device-independent resources.
//bool GraphicsClass::Initialize(int screenWidth, int screenHeight)
//{
//	HRESULT hr = S_OK;
//
//	// Create a Direct2D factory.
//	hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &m_pDirect2dFactory);
//	bitmapTest->Initialize();
//	secondBitmap->Initialize();
//	return hr;
//}
//
//
//void GraphicsClass::Shutdown()
//{
//
//	return;
//}
//
//
//bool GraphicsClass::Frame()
//{
//
//	return true;
//}
//
//D2D_VECTOR_2F GraphicsClass::GetDPI()
//{
//	D2D_VECTOR_2F systemDPI;
//	m_pDirect2dFactory->GetDesktopDpi(&systemDPI.x, &systemDPI.y);
//	return systemDPI;
//}
//
//// Initialize device-dependent resources.
//HRESULT GraphicsClass::CreateDeviceResources(HWND hwnd)
//{
//	HRESULT hr = S_OK;
//
//	if (!m_pRenderTarget)
//	{
//		RECT rc;
//		GetClientRect(hwnd, &rc);
//
//		D2D1_SIZE_U size = D2D1::SizeU(
//			rc.right - rc.left,
//			rc.bottom - rc.top
//		);
//
//		// Create a Direct2D render target.
//		hr = m_pDirect2dFactory->CreateHwndRenderTarget(
//			D2D1::RenderTargetProperties(),
//			D2D1::HwndRenderTargetProperties(hwnd, size),
//			&m_pRenderTarget
//		);
//
//		if (SUCCEEDED(hr))
//		{
//			// Create a gray brush.
//			hr = m_pRenderTarget->CreateSolidColorBrush(
//				D2D1::ColorF(D2D1::ColorF::LightSlateGray),
//				&m_pLightSlateGrayBrush
//			);
//		}
//		if (SUCCEEDED(hr))
//		{
//			// Create a blue brush.
//			hr = m_pRenderTarget->CreateSolidColorBrush(
//				D2D1::ColorF(D2D1::ColorF::CornflowerBlue),
//				&m_pCornflowerBlueBrush
//			);
//		}
//
//		// create bitmap
//		if (SUCCEEDED(hr))
//		{
//			WCHAR pszFileName[MAX_PATH];
//			//if (LocateImageFile(hwnd, pszFileName, ARRAYSIZE(pszFileName)))
//			//{
//			//}
//			hr = bitmapTest->CreateBitmap(L"F:\\TijssEngine v001\\TijssEngine v001\\shipsall.gif", m_pRenderTarget);
//			hr = secondBitmap->CreateBitmap(L"F:\\TijssEngine v001\\TijssEngine v001\\yellowSquare.jpg", m_pRenderTarget);
//
//		}
//	}
//
//	return hr;
//}
//
//bool GraphicsClass::LocateImageFile(HWND hwnd, LPWSTR fileName, DWORD name)
//{
//	fileName[0] = L'\0';
//
//	OPENFILENAME ofn;
//	ZeroMemory(&ofn, sizeof(ofn));
//
//	ofn.lStructSize = sizeof(ofn);
//	ofn.hwndOwner = hwnd;
//	ofn.lpstrFilter = NULL;
//	ofn.lpstrFile = (LPSTR)fileName;
//	ofn.nMaxFile = name;
//	ofn.lpstrTitle = (LPSTR)"Open Image";
//	ofn.Flags = OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST;
//	gFileName = (LPWSTR)ofn.lpstrFile;
//	// Display the Open dialog box.  
//	return (GetOpenFileName(&ofn) == TRUE);
//}
//
//// Release device-dependent resource.
//void GraphicsClass::DiscardDeviceResources()
//{
//	SafeRelease(&m_pRenderTarget);
//	SafeRelease(&m_pLightSlateGrayBrush);
//	SafeRelease(&m_pCornflowerBlueBrush);
//}
//
//HRESULT GraphicsClass::OnRender(HWND hwnd)
//{
//	HRESULT hr = S_OK;
//
//	hr = CreateDeviceResources(hwnd);
//
//
//	if (SUCCEEDED(hr))
//	{
//		m_pRenderTarget->BeginDraw();
//
//		m_pRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
//
//		m_pRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::White));
//
//		D2D1_SIZE_F rtSize = m_pRenderTarget->GetSize();
//
//		if (bitmapTest->GetBitmap())
//		{
//			D2D1_SIZE_F bitmapSize = bitmapTest->GetBitmap()->GetSize();
//			D2D_VECTOR_2F scaledSize = { bitmapSize.width, bitmapSize.height };
//			auto rectangle = D2D1::RectF(0.0f, 0.0f, scaledSize.x, scaledSize.y);
//
//			m_pRenderTarget->DrawBitmap(bitmapTest->GetBitmap(), rectangle);
//		}
//
//
//
//		if (secondBitmap->GetBitmap())
//		{
//			D2D1_SIZE_F bitmapSize = secondBitmap->GetBitmap()->GetSize();
//			D2D_VECTOR_2F scaledSize = { bitmapSize.width / 2.f, bitmapSize.height / 2.f };
//			auto rectangle = D2D1::RectF(bitmapPos.x, bitmapPos.y, scaledSize.x + bitmapPos.x, scaledSize.y + bitmapPos.y);
//			//auto rot = D2D1::Matrix3x2F::Rotation(20);
//			//m_pRenderTarget->SetTransform(rot);
//
//			m_pRenderTarget->DrawBitmap(secondBitmap->GetBitmap(), rectangle);
//			m_pRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
//		}
//
//
//		// Draw a grid background.
//		int width = static_cast<int>(rtSize.width);
//		int height = static_cast<int>(rtSize.height);
//
//		for (int x = 0; x < width; x += 10)
//		{
//			m_pRenderTarget->DrawLine(
//				D2D1::Point2F(static_cast<FLOAT>(x), 0.0f),
//				D2D1::Point2F(static_cast<FLOAT>(x), rtSize.height),
//				m_pLightSlateGrayBrush,
//				0.5f
//			);
//		}
//
//		for (int y = 0; y < height; y += 10)
//		{
//			m_pRenderTarget->DrawLine(
//				D2D1::Point2F(0.0f, static_cast<FLOAT>(y)),
//				D2D1::Point2F(rtSize.width, static_cast<FLOAT>(y)),
//				m_pLightSlateGrayBrush,
//				0.5f
//			);
//		}
//
//		// Draw two rectangles.
//		D2D1_RECT_F rectangle1 = D2D1::RectF(
//			rtSize.width / 2 - 50.0f,
//			rtSize.height / 2 - 50.0f,
//			rtSize.width / 2 + 50.0f,
//			rtSize.height / 2 + 50.0f
//		);
//
//		D2D1_RECT_F rectangle2 = D2D1::RectF(
//			rtSize.width / 2 - 100.0f,
//			rtSize.height / 2 - 100.0f,
//			rtSize.width / 2 + 100.0f,
//			rtSize.height / 2 + 100.0f
//		);
//
//		// Draw a filled rectangle.
//		m_pRenderTarget->FillRectangle(&rectangle1, m_pLightSlateGrayBrush);
//
//		// Draw the outline of a rectangle.
//		m_pRenderTarget->DrawRectangle(&rectangle2, m_pCornflowerBlueBrush);
//
//
//		hr = m_pRenderTarget->EndDraw();
//	}
//	if (hr == D2DERR_RECREATE_TARGET)
//	{
//		hr = S_OK;
//		DiscardDeviceResources();
//	}
//
//	return hr;
//}
//
//void GraphicsClass::OnResize(UINT width, UINT height)
//{
//	if (m_pRenderTarget)
//	{
//		// Note: This method can fail, but it's okay to ignore the
//		// error here, because the error will be returned again
//		// the next time EndDraw is called.
//		m_pRenderTarget->Resize(D2D1::SizeU(width, height));
//	}
//}