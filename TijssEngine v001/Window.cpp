#include "Window.h"
#include "Input.h"

namespace Tijss
{
	cWindow::cWindow()
	{
		m_Created = false;

		m_Name = L"TijssEngineWindow";
		m_WindowHandle = NULL;

		m_hInstance = GetModuleHandle(NULL);

		WNDCLASSEX wc;
		wc.cbSize = sizeof(WNDCLASSEX);
		wc.style = CS_HREDRAW | CS_VREDRAW;
		wc.lpfnWndProc = WndProc;
		wc.cbClsExtra = 0;
		wc.cbWndExtra = 0;
		wc.hInstance = m_hInstance;
		wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
		wc.hCursor = LoadCursor(NULL, IDC_ARROW);
		wc.hbrBackground = (HBRUSH)COLOR_GRAYTEXT;
		wc.lpszMenuName = NULL;
		wc.lpszClassName = m_Name.c_str;
		wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

		// check if successful
		if (!RegisterClassEx(&wc))
		{
			Log::Error("Window::Window: RegisterClassEx(&wc)");
		}
	}

	cWindow::~cWindow()
	{
		Release();
		// unregister
		if (!m_Name.empty() && !UnregisterClassW(m_Name.c_str, m_hInstance))
		{
			Log::Error("Window::~Window: Could Not Unregister Class.");
		}
	}

	void cWindow::Instantiate(INT32 width, INT32 height, const WCHAR* caption, bool enableBTN)
	{
		if (m_Created)
		{
			Log::Error("Window::Create: Window already created!");
		}

		m_WindowHandle = NULL;
		m_Width = width;
		m_Height = height;
		m_Caption = caption;

		DWORD Style;

		if(enableBTN)
		{
			Style = WS_OVERLAPPEDWINDOW & ~WS_THICKFRAME & ~WS_MAXIMIZEBOX;
		}
		else
		{
			Style = WS_BORDER;
		}

		m_WindowHandle = CreateWindowW(
			m_Name.c_str, m_Caption.c_str,
			Style, CW_USEDEFAULT, CW_USEDEFAULT,
			m_Width + GetSystemMetrics(SM_CXFIXEDFRAME) * 2,
			m_Height + GetSystemMetrics(SM_CYFIXEDFRAME) * 2 + GetSystemMetrics(SM_CYCAPTION),
			NULL, NULL,
			m_hInstance, NULL
		);

		if (!m_WindowHandle)
		{
			Log::Error("Window::Window: Window not created!");
		}

		ShowWindow(m_WindowHandle, SW_SHOW);
		SetForegroundWindow(m_WindowHandle);
		SetFocus(m_WindowHandle);
		UpdateWindow(m_WindowHandle);

		m_Created = true;

		Log::Success("Window created.");
	}

	bool cWindow::GetRunning()
	{
		if (m_Created)
			return IsWindow(m_WindowHandle) ? true : false;
		else
			return false;
	}

	void cWindow::SetWindow(HWND hwnd, INT32 width, INT32 height)
	{
		m_WindowHandle = hwnd;
		m_Width = width;
		m_Height = height;
		m_Caption = L"";

		Log::Success("Window: selected exist by HWND.");
	}

	void cWindow::Release()
	{
		if (IsWindow(m_WindowHandle))
		{
			if (!DestroyWindow(m_WindowHandle))
			{
				Log::Error("Window::Release: Could Not Destroy Window.");
				m_WindowHandle = NULL;
			}
			m_Created = false;
			Log::Success("Window - Released");
		}
	}


	HWND cWindow::GetHandle()
	{
		return m_WindowHandle;
	}
	INT32 cWindow::GetWidth()
	{
		return m_Width;
	}
	INT32 cWindow::GetHeight()
	{
		return m_Height;		
	}

	LRESULT CALLBACK WndProc(
		HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam
	)
	{
		// read keys and buttons
		switch (uMsg)
		{

		case WM_DESTROY:
			{
				PostQuitMessage(0);
				return 0;
			}

		case WM_CLOSE:
			{
				DestroyWindow(hwnd);
				Log::Success("Window - Released by WndProc");
				return 0;
			}

		case WM_KEYDOWN:
			{
				KeyCodes eKeyCode = static_cast<KeyCodes>(wParam);
				KeyDownEvent(eKeyCode);
				break;
			}

		case WM_KEYUP:
			{
				KeyCodes eKeyCode = static_cast<KeyCodes>(wParam);
				KeyUpEvent(eKeyCode);
				break;
			}

		case WM_LBUTTONDOWN:
			{
				KeyDownEvent(LeftMouseButton);
				break;
			}
		case WM_LBUTTONUP:
			{
				KeyUpEvent(LeftMouseButton);
				break;
			}
		case WM_RBUTTONDOWN:
			{
				KeyDownEvent(RightMouseButton);
				break;
			}
		case WM_RBUTTONUP:
			{
				KeyUpEvent(RightMouseButton);

				break;
			}
		case WM_MBUTTONDOWN:
			{
				KeyDownEvent(MiddleMouseButton);
				break;
			}
		case WM_MBUTTONUP:
			{
				KeyUpEvent(MiddleMouseButton);
				break;
			}
		}

		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
}