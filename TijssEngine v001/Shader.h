#pragma once
#include "_DllExport.h"

#include <d3d11.h>
#include <d3dx11.h>
#include <xnamath.h>
#include <d3dcompiler.h>
#include <string>
using namespace std;

#include "Logger.h"
#include "EngineDefines.h"
#include "Graphics.h"

namespace Tijss
{
	class TIJSSEN_DECLSPEC cShader
	{
	public:

		ID3D10Blob			*VS_Buffer;
		ID3D10Blob			*PS_Buffer;
		ID3D11VertexShader	*VertexShader;
		ID3D11PixelShader	*PixelShader;
		ID3D11InputLayout	*InputLayout;


		cShader();
		~cShader();
		void Load(const WCHAR* FX_FileName);

		void CreateInputLayout(D3D11_INPUT_ELEMENT_DESC *pLayout, int pNumElements);
		void Release();

	private:



	};

}