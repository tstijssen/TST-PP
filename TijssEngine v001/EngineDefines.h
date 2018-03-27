#pragma once
#include "_DLLExport.h"

#define _XM_NO_INTINSICS_

#include <d3dx11.h>
#include <xnamath.h>
#include <string>

#define _RELEASE(p)		{ if(p){(p)->Release(); (p)=nullptr;} }
#define _RELEASE_DELETE(p)	{ if(p){(p)->Release(); delete (p); (p)=nullptr;} }

namespace Tijss
{


	// end of basic math stuff


	extern TIJSSEN_DECLSPEC HRESULT hr;



}