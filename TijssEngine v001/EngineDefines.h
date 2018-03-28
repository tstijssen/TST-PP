#pragma once
#include "_DLLExport.h"

#define _XM_NO_INTINSICS_

#include <d3dx11.h>
#include <xnamath.h>
#include <string>
#include "Camera.h"
#include "Window.h"
//#include "Scene.h"

#define _RELEASE(p)		{ if(p){(p)->Release(); (p)=nullptr;} }
#define _RELEASE_DELETE(p)	{ if(p){(p)->Release(); delete (p); (p)=nullptr;} }

namespace Tijss
{


	// end of basic math stuff


	extern TIJSSEN_DECLSPEC HRESULT hr;


	class cEngineDescription
	{

	public:

		bool m_Windowed;
		bool m_VSync;

		cCamera *m_Camera2D;
		cCamera *m_Camera3D;
		cWindow *m_Window;



		cEngineDescription()
		{
			m_VSync = false;
			m_Windowed = false;
			m_Window = 0;
			m_Camera2D = 0;
			m_Camera3D = 0;
		}

		bool Test()
		{
			// Must have 1-2 start camera
			if (!(m_Camera2D || m_Camera3D))
				return false;
			if (!m_Window)	return false;
			return true;
		}
	};
}