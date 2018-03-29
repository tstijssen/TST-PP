#pragma once
#include "_DLLExport.h"

#define _XM_NO_INTINSICS_

#include <d3dx11.h>
#include <d3d11.h>
#include <xnamath.h>
#include <string>
#include "Camera.h"
#include "Window.h"
#include "Scene.h"

#define _RELEASE(p)		{ if(p){(p)->Release(); (p)=nullptr;} }
#define _RELEASE_DELETE(p)	{ if(p){(p)->Release(); delete (p); (p)=nullptr;} }

namespace Tijss
{

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


	extern TIJSSEN_DECLSPEC HRESULT hr;

	namespace ShaderLayouts
	{
		extern TIJSSEN_DECLSPEC D3D11_INPUT_ELEMENT_DESC SpriteLayout[];
		extern TIJSSEN_DECLSPEC D3D11_INPUT_ELEMENT_DESC StandartLayout[];
		extern TIJSSEN_DECLSPEC D3D11_INPUT_ELEMENT_DESC SpriteGroupLayout[];
		extern TIJSSEN_DECLSPEC D3D11_INPUT_ELEMENT_DESC TiledSpriteGroupLayout[];
		extern TIJSSEN_DECLSPEC D3D11_INPUT_ELEMENT_DESC PrimitiveLayout[];
		extern TIJSSEN_DECLSPEC D3D11_INPUT_ELEMENT_DESC TestLayout[];
	}

	namespace Path
	{
		extern TIJSSEN_DECLSPEC wstring  DEFAULT_SHADERS;
	}

	// Sprite constant buffer value
	struct CBSprite
	{
		CBSprite()
		{
			COLOR = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
		}

		XMMATRIX FINAL_MATRIX;
		XMFLOAT4 COLOR;
	};

	namespace Vertex
	{
		struct vtxSprite
		{
			vtxSprite()
			{
				Position = XMFLOAT3(0.0f, 0.0f, 0.0f);
				TexCoord = XMFLOAT2(0.0f, 0.0f);

			}

			XMFLOAT3 Position;
			XMFLOAT2 TexCoord;
		};

		struct SpriteVertex
		{
			SpriteVertex()
			{
				Position = XMFLOAT3(0.0f, 0.0f, 0.0f);
				TexCoord = XMFLOAT2(0.0f, 0.0f);
				Color = XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f);
			}

			XMFLOAT3 Position;
			XMFLOAT2 TexCoord;
			XMFLOAT4 Color;

		};

		struct TiledSpriteVertex
		{
			TiledSpriteVertex()
			{
				Position = XMFLOAT3(0.0f, 0.0f, 0.0f);
				TexCoord = XMFLOAT2(0.0f, 0.0f);
			}

			XMFLOAT3 Position;
			XMFLOAT2 TexCoord;

		};


		struct SpriteGroupVertex
		{
			SpriteGroupVertex()
			{
				Position = XMFLOAT3(0.0f, 0.0f, 0.0f);
				Rotation = XMFLOAT3(0.0f, 0.0f, 0.0f);
				Scale = 1.0f;
				TexCoord = XMFLOAT2(0.0f, 0.0f);
				Color = XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f);
			}

			XMFLOAT3 Position;
			XMFLOAT3 Rotation;
			float Scale;
			XMFLOAT2 TexCoord;
			XMFLOAT4 Color;

		};

		struct PrimitiveVertex
		{
			PrimitiveVertex()
			{
				Position = XMFLOAT3(0.0f, 0.0f, 0.0f);
				Color = XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f);
			}

			XMFLOAT3 Position;
			XMFLOAT4 Color;

		};

		struct VertexTest
		{
			XMFLOAT3 Position;
			XMFLOAT2 Texture;
		};
	}
}