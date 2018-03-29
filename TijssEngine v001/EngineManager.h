#pragma once

#include "_DLLExport.h"
#include "Camera.h"
#include "EngineDefines.h"
#include "Graphics.h"
#include "Window.h"
#include "Logger.h"

namespace Tijss
{
	class TIJSSEN_DECLSPEC cEngine
	{
	public:
		static cEngine* GetInstance();

		cEngine();
		~cEngine();

		void Init(cEngineDescription pEngineOptions);
		void Release();

		void SetRootScene(cScene* pScene);

		// static stuff
		static cGraphics*			GetGFX();
		static cCamera*				GetActive2DCamera();
		static cCamera*				GetActive3DCamera();
		static ID3D11Device*		GetDevice();
		static ID3D11DeviceContext* GetContext();

		cWindow* GetWindow();

		void SetActiveCamera2D(cCamera* newCamera);
		void SetActiveCamera3D(cCamera* newCamera);

		void SetScene(cScene *pScene);

		void Update();
		void Draw();

	private:
		cWindow * m_Window;
		cCamera * m_Camera2D;
		cCamera * m_Camera3D;
		// shaderbase

		// gfx
		cGraphics			* m_GFX;
		ID3D11Device		* m_Device;
		ID3D11DeviceContext	* m_Context;

		// root scene (start)
		cScene * m_RootScene;

		static cEngine * m_EngineInst;

	};
}





//#define WIN32_LEAN_AND_MEAN
//
//#include <windows.h>
//#include <vector>
//#include <memory>
//#include "Graphics.h"
//#include "Input.h"
//
//#ifndef HINST_THISCOMPONENT
//EXTERN_C IMAGE_DOS_HEADER __ImageBase;
//#define HINST_THISCOMPONENT ((HINSTANCE)&__ImageBase)
//#endif
//
//class TijssEngine
//{
//public:
//	TijssEngine();
//	TijssEngine(const TijssEngine&);
//	~TijssEngine();
//
//	bool Initialize(int&, int&);
//	// Process and dispatch messages
//	void RunMessageLoop();
//
//	void AddLibrary() {};
//
//	//LRESULT CALLBACK MessageHandler(HWND, UINT, WPARAM, LPARAM);
//	// The windows procedure.
//	static LRESULT CALLBACK WndProc(
//		HWND hWnd,
//		UINT message,
//		WPARAM wParam,
//		LPARAM lParam
//	);
//private:
//	void InitializeWindows(int&, int&, char* windowName = "TijssEngine");
//
//private:
//	LPCWSTR m_applicationName;
//	HINSTANCE m_hinstance;
//	HWND m_hwnd;
//
//	std::unique_ptr<InputClass> m_Input;
//	std::unique_ptr<GraphicsClass> m_Graphics = std::make_unique<GraphicsClass>();
//};