#include "DefaultShaderBase.h"

namespace Tijss
{
	cDefaultShaderBase* cDefaultShaderBase::m_Instance = nullptr;
	bool cDefaultShaderBase::m_Loaded = false;


	cDefaultShaderBase::cDefaultShaderBase()
	{
		if (m_Instance == nullptr)
		{
			m_Instance = this;
		}
		else
			Log::Warning("DefaultShaderBase::DefaultShaderBase already created.");

		m_ShaderSprite = nullptr;
		m_ShaderSpriteGroup = nullptr;
		m_ShaderText = nullptr;
		m_ShaderTiledSprite = nullptr;
		m_ShaderTiledSpriteGroup = nullptr;

	}

	void cDefaultShaderBase::LoadShaders()
	{
		m_ShaderSprite = new cShader();
		m_ShaderSpriteGroup = new cShader();
		m_ShaderText = new cShader();
		m_ShaderTiledSprite = new cShader();
		m_ShaderTiledSpriteGroup = new cShader();

		m_ShaderSprite->Load(wstring(Path::DEFAULT_SHADERS + L"TxSprite.fx").c_str());
		m_ShaderSpriteGroup->Load(wstring(Path::DEFAULT_SHADERS + L"TxSpriteGroup.fx").c_str());
		m_ShaderText->Load(wstring(Path::DEFAULT_SHADERS + L"TxText.fx").c_str());
		m_ShaderTiledSprite->Load(wstring(Path::DEFAULT_SHADERS + L"TxTiledSprite.fx").c_str());
		m_ShaderTiledSpriteGroup->Load(wstring(Path::DEFAULT_SHADERS + L"TxTiledSpriteGroup.fx").c_str());

		m_ShaderSprite->CreateInputLayout(ShaderLayouts::SpriteLayout, 2);
		m_ShaderSpriteGroup->CreateInputLayout(ShaderLayouts::SpriteGroupLayout, 5);
		m_ShaderText->CreateInputLayout(ShaderLayouts::StandartLayout, 3);
		m_ShaderTiledSprite->CreateInputLayout(ShaderLayouts::SpriteLayout, 2);
		m_ShaderTiledSpriteGroup->CreateInputLayout(ShaderLayouts::TiledSpriteGroupLayout, 5);

		m_Loaded = true;

		Log::Success("DefaultShaderBase::LoadShaders");
	}

	void cDefaultShaderBase::ReleaseShaders()
	{
		if (m_Loaded)
		{
			_RELEASE_DELETE(m_ShaderSprite)
				_RELEASE_DELETE(m_ShaderSpriteGroup)
				_RELEASE_DELETE(m_ShaderText)
				_RELEASE_DELETE(m_ShaderTiledSprite)
				_RELEASE_DELETE(m_ShaderTiledSpriteGroup)
		}
		m_Loaded = false;
		Log::Success("DefaultShaderBase::ReleaseShaders");
	}

	cDefaultShaderBase::~cDefaultShaderBase()
	{
		if (m_Instance)
			if (m_Loaded)
			{
				ReleaseShaders();
			}
		m_Instance = nullptr;
	}

	cDefaultShaderBase* cDefaultShaderBase::Instance()
	{
		if (m_Instance == nullptr)
		{
			Log::Error("DefaultShaderBase::GetInstance: you must create object before.");
			return nullptr;
		}
		else
			return m_Instance;
	}
}