#pragma once
// Windows Header Files:
#include <windows.h>
#include "_DLLExport.h"
#include <string>

#define WIN32_LEAN_AND_MEAN

namespace Tijss
{
	class cWindow;
	typedef LRESULT(CALLBACK cWindow::*WNDPROC)(HWND, UINT, WPARAM, LPARAM);

	class TIJSSEN_DECLSPEC cWindow
	{
	public:
		cWindow();
		~cWindow();

		void Instantiate(INT32 width, INT32 height, const WCHAR* caption, bool enableBTN);
		void SetWindow(HWND hwnd, INT32 width, INT32 height);

		bool GetRunning();
		void Release();

		HWND GetHandle();
		INT32 GetWidth();
		INT32 GetHeight();

	private:
		// member variables

		bool m_Created;
		INT32 m_Width, m_Height;

		HWND m_WindowHandle;

		std::wstring m_Caption, m_Name;

		HINSTANCE m_hInstance;
	};

	TIJSSEN_DECLSPEC LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
}




//// C RunTime Header Files:
//#include <stdlib.h>
//#include <malloc.h>
//#include <memory.h>
//#include <wchar.h>
//#include <math.h>
//
//#include <d2d1.h>
//#include <d2d1helper.h>
//#include <dwrite.h>
//#include <wincodec.h>
//
//#ifndef HINST_THISCOMPONENT
//EXTERN_C IMAGE_DOS_HEADER __ImageBase;
//#define HINST_THISCOMPONENT ((HINSTANCE)&__ImageBase)
//#endif
//
//class WindowClass
//{
//public:
//	WindowClass() :	m_hwnd(NULL) {}
//	~WindowClass() {}
//
//	// Register the window class and call methods for instantiating drawing resources
//	HRESULT Initialize(char* windowName, int screenWidth, int screenHeight);
//
//	// Process and dispatch messages
//	void RunMessageLoop();
//
//private:
//
//	// The windows procedure.
//	static LRESULT CALLBACK WndProc(
//		HWND hWnd,
//		UINT message,
//		WPARAM wParam,
//		LPARAM lParam
//	);
//
//private:
//	HWND m_hwnd;
//};
//
//void WindowClass::RunMessageLoop()
//{
//	MSG msg;
//
//	while (GetMessage(&msg, NULL, 0, 0))
//	{
//		TranslateMessage(&msg);
//		DispatchMessage(&msg);
//	}
//}
//
//HRESULT WindowClass::Initialize(char* windowName = "TijssEngine", int screenWidth, int screenHeight)
//{
//	HRESULT hr;
//
//	// Initialize device-indpendent resources, such
//	// as the Direct2D factory.
//	hr = CreateDeviceIndependentResources();
//
//	if (SUCCEEDED(hr))
//	{
//		// Register the window class.
//		WNDCLASSEX wcex = { sizeof(WNDCLASSEX) };
//		wcex.style = CS_HREDRAW | CS_VREDRAW;
//		wcex.lpfnWndProc = WindowClass::WndProc;
//		wcex.cbClsExtra = 0;
//		wcex.cbWndExtra = sizeof(LONG_PTR);
//		wcex.hInstance = HINST_THISCOMPONENT;
//		wcex.hbrBackground = NULL;
//		wcex.lpszMenuName = NULL;
//		wcex.hCursor = LoadCursor(NULL, IDI_APPLICATION);
//		wcex.lpszClassName = "D2DDemoApp";
//
//		RegisterClassEx(&wcex);
//
//
//		// Because the CreateWindow function takes its size in pixels,
//		// obtain the system DPI and use it to scale the window size.
//		FLOAT dpiX, dpiY;
//
//		// The factory returns the current system DPI. This is also the value it will use
//		// to create its own windows.
//		m_pDirect2dFactory->GetDesktopDpi(&dpiX, &dpiY);
//
//
//		// Create the window.
//		m_hwnd = CreateWindow(
//			"D2DDemoApp",
//			windowName,
//			WS_OVERLAPPEDWINDOW,
//			CW_USEDEFAULT,
//			CW_USEDEFAULT,
//			static_cast<UINT>(ceil(screenWidth * dpiX / 96.f)),
//			static_cast<UINT>(ceil(screenHeight * dpiY / 96.f)),
//			NULL,
//			NULL,
//			HINST_THISCOMPONENT,
//			this
//		);
//		hr = m_hwnd ? S_OK : E_FAIL;
//		if (SUCCEEDED(hr))
//		{
//			ShowWindow(m_hwnd, SW_SHOWNORMAL);
//			UpdateWindow(m_hwnd);
//		}
//	}
//
//	return hr;
//}