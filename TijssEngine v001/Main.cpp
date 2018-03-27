// TijssEngineconsoleappv1.cpp : Defines the entry point for the console application.

// Windows Header Files:
#include <windows.h>
#include "Graphics.h"
#include "Level1.h"
#include "GameController.h"
#include "Input.h"

Graphics* graphics;

LRESULT CALLBACK WindowProc(
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

int WINAPI WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow
)
{
	WNDCLASSEX windowClass;
	ZeroMemory(&windowClass, sizeof(WNDCLASSEX));

	windowClass.cbSize = sizeof(WNDCLASSEX);
	windowClass.hbrBackground = (HBRUSH)COLOR_WINDOW;
	windowClass.hInstance = hInstance;
	windowClass.lpfnWndProc = WindowProc;
	windowClass.lpszClassName = "MainWindow";
	windowClass.style = CS_HREDRAW | CS_VREDRAW;

	RegisterClassEx(&windowClass);

	RECT rect = {0,0, 1280, 980};
	AdjustWindowRectEx(&rect, WS_OVERLAPPEDWINDOW, false, WS_EX_OVERLAPPEDWINDOW);

	HWND windowHandle = CreateWindowEx(WS_EX_OVERLAPPEDWINDOW, "MainWindow", "TijssEngine!", WS_OVERLAPPEDWINDOW, 100, 100, 
										rect.right - rect.left, rect.bottom - rect.top, NULL, NULL, hInstance, 0);

	if (!windowHandle) return -1;

	graphics = new Graphics();

	if (!graphics->Init(windowHandle))
	{
		delete graphics;
		return -1;
	}
	GameController::Init();
	GameLevel::Init(graphics);
	SpriteManager::FolderInit("Media");

	ShowWindow(windowHandle, nCmdShow);

	GameController::LoadInitialLevel(new Level1());

	MSG message;
	message.message = WM_NULL;
	PeekMessage(&message, NULL, 0, 0, PM_REMOVE);
	while (message.message != WM_QUIT)
	{
		if (PeekMessage(&message, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&message);
			DispatchMessage(&message);
		}
		else
		{
			if (KeyHit(Key_Escape))
			{
				message.message = WM_QUIT;
				DispatchMessage(&message);
			}
			GameController::Update();
			// render
			graphics->BeginDraw();
			GameController::Render();
			graphics->EndDraw();
		}
	}

	delete graphics;
	return 0;
}