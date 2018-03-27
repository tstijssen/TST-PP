#pragma once
#include "_DLLExport.h"

#include <d3d11.h>
#include <d2d1.h>
#include "Window.h"
#include "EngineDefines.h"
#include "TypeDefines.h"

namespace Tijss
{
	class TIJSSEN_DECLSPEC cGraphics
	{
	public:

		cGraphics();
		~cGraphics();

		ID3D11Device* GetDevice();
		ID3D11DeviceContext* GetContext();

		static cGraphics* GFXInstance();
		static bool GFXReady();

		cGraphics(cWindow* window, bool windowed, bool vsync);
		bool Init(cWindow* window, bool windowed, bool vsync);

		int32 GetWidth();
		int32 GetHeight();
		
		void SetRenderTarget(ID3D11RenderTargetView* rt);
		void SetWireframe(bool toggle);

		void EnableStencil();
		void DisableStencil();

		void Clear();
		void SetClearColour(sColour colour);

		int32 GetFPS();
		void Flip();
		void CalcFramerate();
		void Release();

		void SetViewport(float32 x, float32 y, float32 width, float32 height);

		ID3D11DepthStencilView* GetDepthStencilView();
	private:
		// member variables
		static bool m_Ready;
		static cGraphics* m_Instance;
		sColour m_ClearColour;

		HWND m_WindowHandle;
		D3D_FEATURE_LEVEL	m_FeatureLevel;

		ID3D11Device*				m_Device;
		ID3D11DeviceContext*		m_Context;
		IDXGISwapChain*				m_SwapChain;

		ID3D11BlendState*			m_BlendState;
		ID3D11RasterizerState*		m_RasterState;
		ID3D11RasterizerState*		m_WireFrameState;

		ID3D11RenderTargetView*		m_BackBuffer;
		ID3D11RenderTargetView*		m_CurrentRenderTarget;

		ID3D11DepthStencilView*		m_DepthStencilView;
		ID3D11DepthStencilView*		m_isDepthStencilView;
		ID3D11DepthStencilState*	m_pDSState;

		long m_hr;
		//LPCTSTR Caption;
		int32 m_Width, m_Height, m_Depth;
		bool m_Windowed, m_VSync;
		int32 m_FPS;
		D3D11_VIEWPORT m_ViewPort;


		//private member functions
		void ZeroInit();
		bool InitializeDirectX();

		void CreateDeviceAndSwapChain();
		void CreateBackBuffer();
		void CreateWireframeState();
		void CreateBlendState();
		void CreateRasterState();
		void CreateDepthStencilBuffer();
	};

	class TIJSSEN_DECLSPEC cDirect2DGraphics
	{
		ID2D1Factory* m_Factory;
		ID2D1HwndRenderTarget* m_RenderTarget;
		ID2D1SolidColorBrush* m_Brush;
	public:
		cDirect2DGraphics();
		~cDirect2DGraphics();

		bool Init(HWND windowHandle);

		ID2D1RenderTarget* GetRenderTarget()
		{
			return m_RenderTarget;
		}

		void BeginDraw() { m_RenderTarget->BeginDraw(); }
		void EndDraw() { m_RenderTarget->EndDraw(); }
		void ClearScreen(float r, float g, float b);
		void DrawCircle(float x, float y, float radius, float r, float g, float b, float a);
	};
}

