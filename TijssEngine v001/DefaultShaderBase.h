#pragma once
#include "_DllExport.h"

#include "EngineDefines.h"
#include "Logger.h"
#include "Shader.h"

namespace Tijss
{
	class TIJSSEN_DECLSPEC cDefaultShaderBase
	{
	public:
		cDefaultShaderBase();
		~cDefaultShaderBase();

		void LoadShaders();
		void ReleaseShaders();

		static cDefaultShaderBase* Instance();

		// Shaders
		cShader *m_ShaderSprite;
		cShader *m_ShaderSpriteGroup;
		cShader *m_ShaderText;
		cShader *m_ShaderTiledSprite;
		cShader *m_ShaderTiledSpriteGroup;
	private:
		static cDefaultShaderBase* m_Instance;
		static bool m_Loaded;

	};

}