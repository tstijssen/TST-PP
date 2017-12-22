#pragma once
#define DIRECTINPUT_VERSION 0x0800

#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

#include <windowsx.h>
#include <dinput.h>

class InputClass
{
public:
	InputClass();
	InputClass(const InputClass&);
	~InputClass();
	
	bool Initialize(HINSTANCE, HWND, int, int);

	void Shutdown();
	bool Frame();

	bool IsKeyPressed(unsigned int);
	void GetMouseLocation(int&, int&);

private:
	bool ReadKeyboard();
	bool ReadMouse();
	void ProcessInput();

private:
	IDirectInput8* m_DirectInput;
	IDirectInputDevice8* m_Keyboard;
	IDirectInputDevice8* m_Mouse;

	unsigned char m_KeyboardState[256];
	DIMOUSESTATE m_MouseState;

	int m_ScreenWidth, m_ScreenHeight;
	int m_MouseX, m_MouseY;
};