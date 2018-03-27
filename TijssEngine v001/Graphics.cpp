#include "Graphics.h"

namespace Tijss
{
	bool cGraphics::m_Ready = false;
	cGraphics* cGraphics::m_Instance = nullptr;

	cGraphics::cGraphics()
	{
		if (m_Instance == nullptr)
		{
			m_Instance = this;
		}
		else
			return;	// log error, graphics obj already exists

		ZeroInit();

		m_pDSState = 0;
		m_FeatureLevel = D3D_FEATURE_LEVEL_10_0;

		m_ClearColour(0.5f, 0.5f, 0.9f, 1.0f);	// default clear screen colour

		m_Ready = false;	// double ensure ready is false, graphics not yet initialized
	}

	cGraphics::cGraphics(cWindow* window, bool windowed, bool vsync) : cGraphics()	// does this work?
	{
		Init(window, windowed, vsync);
	}

	cGraphics::~cGraphics()
	{
		m_Instance = nullptr;
		m_Ready = false;
	}

	bool cGraphics::GFXReady()
	{
		return m_Ready;
	}

	cGraphics* cGraphics::GFXInstance()
	{
		if (m_Instance == nullptr)
		{
			// log error, graphics not created
			return nullptr;
		}
		else
		{
			return m_Instance;
		}
	}

	bool cGraphics::Init(cWindow* window, bool windowed, bool vsync)
	{
		m_WindowHandle = window->GetHandle();
		m_Width = window->GetWidth();
		m_Height = window->GetHeight();

		m_Windowed = windowed;
		m_VSync = vsync;

		m_Depth = 32;

		hr = 0;
		m_FPS = 0;

		m_Ready = InitializeDirectX();
		return m_Ready;
	}

	ID3D11Device* cGraphics::GetDevice()
	{
		return m_Device;
	}

	ID3D11DeviceContext* cGraphics::GetContext()
	{
		return m_Context;
	}

	int32 cGraphics::GetWidth()
	{
		return m_Width;
	}

	int32 cGraphics::GetHeight()
	{
		return m_Height;
	}

	void cGraphics::Clear()
	{
		m_Context->ClearRenderTargetView(m_CurrentRenderTarget, (float32*)&m_ClearColour);
		if (m_isDepthStencilView)
		{
			m_Context->ClearDepthStencilView(m_isDepthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
		}
	}

	void cGraphics::SetClearColour(sColour colour)
	{
		m_ClearColour = colour;
	}

	void cGraphics::SetRenderTarget(ID3D11RenderTargetView* rt)
	{
		if (rt == 0)
			m_CurrentRenderTarget = m_BackBuffer;
		else
			m_CurrentRenderTarget = rt;

		m_Context->OMSetRenderTargets(1, &m_CurrentRenderTarget, m_isDepthStencilView);
	}

	ID3D11DepthStencilView* cGraphics::GetDepthStencilView()
	{
		return m_DepthStencilView;
	}

	void cGraphics::EnableStencil()
	{
		m_isDepthStencilView = m_DepthStencilView;
		m_Context->OMSetRenderTargets(1, &m_CurrentRenderTarget, m_isDepthStencilView);
	}

	void cGraphics::DisableStencil()
	{
		m_isDepthStencilView = 0;
		m_Context->OMSetRenderTargets(1, &m_CurrentRenderTarget, m_isDepthStencilView);
	}

	bool cGraphics::InitializeDirectX()
	{
		CreateDeviceAndSwapChain();
		CreateBackBuffer();

		CreateWireframeState();
		CreateBlendState();
		CreateRasterState();

		CreateDepthStencilBuffer();
		m_Context->OMSetRenderTargets(1, &m_BackBuffer, m_isDepthStencilView);
		SetViewport(0.0f, 0.0f, (float32)m_Width, (float32)m_Height);

		return true;
	}

	void cGraphics::CreateDepthStencilBuffer()
	{

		ID3D11Texture2D* DepthStencilBuffer = NULL;
		D3D11_TEXTURE2D_DESC descDepth;
		descDepth.Width = m_Width;
		descDepth.Height = m_Height;
		descDepth.MipLevels = 1;
		descDepth.ArraySize = 1;
		descDepth.Format = DXGI_FORMAT_D32_FLOAT;
		descDepth.SampleDesc.Count = 1;
		descDepth.SampleDesc.Quality = 0;
		descDepth.Usage = D3D11_USAGE_DEFAULT;
		descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;
		descDepth.CPUAccessFlags = 0;
		descDepth.MiscFlags = 0;

		m_Device->CreateTexture2D(&descDepth, NULL, &DepthStencilBuffer);

		// Create the depth stencil view
		D3D11_DEPTH_STENCIL_VIEW_DESC descDSV;
		descDSV.Format = DXGI_FORMAT_D32_FLOAT;
		descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
		descDSV.Texture2D.MipSlice = 0;

		// Create the depth stencil view
		hr = m_Device->CreateDepthStencilView(DepthStencilBuffer, 0, &m_DepthStencilView);
		//if (FAILED(hr))	Log::Error("Graphics::CreateDepthStencilBuffer()");
		m_isDepthStencilView = m_DepthStencilView;

		DepthStencilBuffer->Release();
	}


	void cGraphics::CreateDeviceAndSwapChain()
	{
		DXGI_SWAP_CHAIN_DESC scd;
		ZeroMemory(&scd, sizeof(DXGI_SWAP_CHAIN_DESC));
		scd.BufferCount = 1;
		scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		scd.OutputWindow = m_WindowHandle;
		scd.SampleDesc.Count = 1;
		scd.SampleDesc.Quality = 0;
		scd.Windowed = m_Windowed;
		scd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

		int DEVICE_CREATION_MODE;

#ifdef _DEBUG
		DEVICE_CREATION_MODE = D3D11_CREATE_DEVICE_DEBUG;
#else
		DEVICE_CREATION_MODE = D3D11_CREATE_DEVICE_SINGLETHREADED;
#endif

		hr = D3D11CreateDeviceAndSwapChain(NULL,
			D3D_DRIVER_TYPE_HARDWARE,
			NULL,
			DEVICE_CREATION_MODE,
			&m_FeatureLevel,
			1,
			D3D11_SDK_VERSION,
			&scd,
			&m_SwapChain,
			&m_Device,
			NULL,
			&m_Context);



		//if (FAILED(hr))	Log::Error("Graphics::CreateDeviceAndSwapChain()");
	}


	void cGraphics::SetViewport(float pX, float pY, float pWidth, float pHeight)
	{
		m_ViewPort.Width = pWidth;
		m_ViewPort.Height = pHeight;
		m_ViewPort.MinDepth = 0.0f;
		m_ViewPort.MaxDepth = 1.0f;
		m_ViewPort.TopLeftX = pX;
		m_ViewPort.TopLeftY = pY;
		m_Context->RSSetViewports(1, &m_ViewPort);
	}


	void cGraphics::SetWireframe(bool pEnable)
	{
		if (m_RasterState && m_WireFrameState)
		{
			if (pEnable)
			{
				m_Context->RSSetState(m_WireFrameState);
			}
			else
			{
				m_Context->RSSetState(m_RasterState);
			}
		}
	}

	void cGraphics::SetViewport(float32 x, float32 y, float32 width, float32 height)
	{
		m_ViewPort.Width = width;
		m_ViewPort.Height = height;
		m_ViewPort.MinDepth = 0.0f;
		m_ViewPort.MaxDepth = 1.0f;
		m_ViewPort.TopLeftX = x;
		m_ViewPort.TopLeftY = y;
		m_Context->RSSetViewports(1, &m_ViewPort);
	}


	void cGraphics::CreateBackBuffer()
	{
		ID3D11Texture2D *pBackBuffer;

		hr = m_SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID *)&pBackBuffer);
		//if (FAILED(hr))	Log::Error("Graphics::CreateBackBuffer: SwapChain->GetBuffer");

		hr = m_Device->CreateRenderTargetView(pBackBuffer, NULL, &m_BackBuffer);
		//if (FAILED(hr))	Log::Error("Graphics::CreateBackBuffer: Device->CreateRenderTargetView");

		_RELEASE(pBackBuffer)

			m_CurrentRenderTarget = m_BackBuffer;
	}


	void cGraphics::CreateBlendState()
	{
		D3D11_BLEND_DESC blendDesc;
		ZeroMemory(&blendDesc, sizeof(blendDesc));

		blendDesc.RenderTarget[0].BlendEnable = TRUE;
		blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
		blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
		blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
		blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
		blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
		blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ONE;//D3D11_BLEND_ZERO;
		blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;


		hr = m_Device->CreateBlendState(&blendDesc, &m_BlendState);
		//if (FAILED(hr))	Log::Error("Graphics::CreateBlendState: Device->CreateBlendState");

		float blendFactor[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
		m_Context->OMSetBlendState(m_BlendState, blendFactor, 0xFFFFFFFF);
	}

	void cGraphics::CreateWireframeState()
	{
		D3D11_RASTERIZER_DESC RasterStateDesc;
		ZeroMemory(&RasterStateDesc, sizeof(D3D11_RASTERIZER_DESC));

		RasterStateDesc.FillMode = D3D11_FILL_WIREFRAME;
		RasterStateDesc.CullMode = D3D11_CULL_NONE;

		hr = m_Device->CreateRasterizerState(&RasterStateDesc, &m_WireFrameState);
		//if (FAILED(hr))	Log::Error("Graphics::CreateWireframeState: Device->CreateRasterizerState");
	}

	void cGraphics::CreateRasterState()
	{
		D3D11_RASTERIZER_DESC RasterStateDesc;
		RasterStateDesc.FillMode = D3D11_FILL_SOLID;
		RasterStateDesc.CullMode = D3D11_CULL_BACK;

		RasterStateDesc.FrontCounterClockwise = false;

		RasterStateDesc.DepthBias = D3D11_DEFAULT_DEPTH_BIAS;
		RasterStateDesc.DepthBiasClamp = D3D11_DEFAULT_DEPTH_BIAS_CLAMP;
		RasterStateDesc.SlopeScaledDepthBias = D3D11_DEFAULT_SLOPE_SCALED_DEPTH_BIAS;
		RasterStateDesc.DepthClipEnable = true;

		RasterStateDesc.ScissorEnable = false;
		RasterStateDesc.MultisampleEnable = false; //true;
		RasterStateDesc.AntialiasedLineEnable = false; //true;

		hr = m_Device->CreateRasterizerState(&RasterStateDesc, &m_RasterState);
		//if (FAILED(hr));//	Log::Error("Graphics::CreateRasterState: Device->CreateRasterizerState");

		m_Context->RSSetState(m_RasterState);
	}

	int cGraphics::GetFPS()
	{
		return m_FPS;
	}


	void cGraphics::Flip()
	{
		hr = m_SwapChain->Present(m_VSync, 0);
		CalcFramerate();
		//if (FAILED(hr)); //Log::Error("SwapChain->Present( 0, 0 )");


#ifdef _DEBUG
		ID3D11ShaderResourceView *const pSRV[1] = { NULL };
		m_Context->PSSetShaderResources(0, 1, pSRV);
#endif

	}

	void  cGraphics::CalcFramerate()
	{
		static float framesPerSecond = 0.0f;
		static float lastTime = 0.0f;

		float currentTime = timeGetTime() * 0.001f;

		++framesPerSecond;

		if (currentTime - lastTime > 1.0f)
		{
			lastTime = currentTime;
			m_FPS = (int)framesPerSecond;
			framesPerSecond = 0;
		}

	}


	void cGraphics::ZeroInit()
	{
		m_Device = 0;
		m_Context = 0;
		m_SwapChain = 0;
		m_BackBuffer = 0;
		m_BlendState = 0;
		m_RasterState = 0;
		m_WireFrameState = 0;
		m_DepthStencilView = 0;
		m_isDepthStencilView = 0;
	}

	void  cGraphics::Release()
	{
		hr = m_SwapChain->SetFullscreenState(FALSE, NULL);
		//if (FAILED(hr));//Log::Error("SwapChain->SetFullscreenState");

		_RELEASE(m_BackBuffer)
		_RELEASE(m_DepthStencilView)
		_RELEASE(m_BlendState)
		_RELEASE(m_RasterState)
		_RELEASE(m_WireFrameState)
		_RELEASE(m_SwapChain)
		_RELEASE(m_Device)
		_RELEASE(m_Context)

		m_Ready = false;
	}


	cDirect2DGraphics::cDirect2DGraphics()
	{
		m_Factory = NULL;
		m_RenderTarget = NULL;
		m_Brush = NULL;
	}

	cDirect2DGraphics::~cDirect2DGraphics()
	{
		if (m_Factory) m_Factory->Release();
		if (m_RenderTarget) m_RenderTarget->Release();
		if (m_Brush) m_Brush->Release();

	}


	bool cDirect2DGraphics::Init(HWND windowHandle)
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

		result = m_RenderTarget->CreateSolidColorBrush(D2D1::ColorF(0, 0, 0, 0), &m_Brush);
		if (result != S_OK) return false;

		return true;
	}

	void cDirect2DGraphics::ClearScreen(float r, float g, float b)
	{
		m_RenderTarget->Clear(D2D1::ColorF(r, g, b));
	}

	void cDirect2DGraphics::DrawCircle(float x, float y, float radius, float r, float g, float b, float a)
	{
		m_Brush->SetColor(D2D1::ColorF(r, g, b, a));

		m_RenderTarget->DrawEllipse(D2D1::Ellipse(D2D1::Point2F(x, y), radius, radius), m_Brush, 3.0f);
	}
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