#include "EngineManager.h"

namespace Tijss
{
	cEngine* cEngine::m_EngineInst = NULL;

	cEngine* cEngine::GetInstance()
	{
		if (m_EngineInst)
		{
			return m_EngineInst;
		}
		else
		{
			Log::Error("Engine::GetMe() - engine not created");
		}
		return NULL;
	}

	cWindow* cEngine::GetWindow()
	{
		return m_Window;
	}

	cEngine::cEngine()
	{
		m_GFX = nullptr;
		m_Context = nullptr;
		m_Device = nullptr;
		m_Window = nullptr;
		m_Camera2D = nullptr;
		m_Camera3D = nullptr;
		m_RootScene = nullptr;

		if (m_EngineInst)
		{
			// error, engine already exists
			return;
		}
		m_EngineInst = this;
	}

	void cEngine::Init(cEngineDescription pEngineOptions)
	{
		m_Window = pEngineOptions.m_Window;
		m_Camera2D = pEngineOptions.m_Camera2D;
		m_Camera3D = pEngineOptions.m_Camera3D;

		if (!pEngineOptions.Test())
			Log::Error("Engine::Initialize: EngineDescription Failed");

		// Graphics block

		m_GFX = new cGraphics();
		m_GFX->Init(m_Window, pEngineOptions.m_Windowed, pEngineOptions.m_VSync);
		m_Context = m_GFX->GetContext();
		m_Device = m_GFX->GetDevice();

		//m_DefaultShaderBase.LoadShaders();

		Log::Success("Engine::Initialized.");
	}

	cCamera* cEngine::GetActive2DCamera()
	{
		if (m_EngineInst)
		{
			if (m_EngineInst->m_Camera2D)
			{
				return m_EngineInst->m_Camera2D;
			}
			else
			{
				Log::Error("Engine::GetActive2DCamera - Camera2D is null");
			}
		}
		else
			Log::Error("Engine::GetActive2DCamera - engine is not created.");

		return NULL;
	}

	cCamera* cEngine::GetActive3DCamera()
	{
		if (m_EngineInst)
		{
			if (m_EngineInst->m_Camera3D)
			{
				return m_EngineInst->m_Camera3D;
			}
			else
			{
				Log::Error("Engine::GetActive3DCamera - Camera3D is null");
			}
		}
		else
			Log::Error("Engine::GetActive3DCamera - engine is not created.");

		return NULL;
	}

	ID3D11Device* cEngine::GetDevice()
	{
		if (m_EngineInst)
		{
			if (m_EngineInst->m_Device)
			{
				return m_EngineInst->m_Device;
			}
			else
			{
				Log::Error("Engine::GetDevice - Device is null");
			}
		}
		else
			Log::Error("Engine::GetDevice - engine is not created.");

		return NULL;
	}

	ID3D11DeviceContext* cEngine::GetContext()
	{
		if (m_EngineInst)
		{
			if (m_EngineInst->m_Context)
			{
				return m_EngineInst->m_Context;
			}
			else
			{
				Log::Error("Engine::GetContext - Context is null");
			}
		}
		else
			Log::Error("Engine::GetContext - engine is not created.");

		return NULL;
	}

	void cEngine::SetActiveCamera2D(cCamera *inCamera)
	{
		m_Camera2D = inCamera;
	}

	void cEngine::SetActiveCamera3D(cCamera *inCamera)
	{
		m_Camera3D = inCamera;
	}

	void cEngine::Draw()
	{
		if (m_Camera2D)
			m_Camera2D->Update();

		if (m_Camera3D)
			m_Camera3D->Update();

		if (m_RootScene)
			m_RootScene->Draw();
	}

	void cEngine::Update()
	{
		if (m_RootScene)
			m_RootScene->Update();
	}

	void cEngine::Release()
	{
		//DefaultShaderBase.ReleaseShaders();

		_RELEASE_DELETE(m_GFX);

		m_Context = nullptr;
		m_Device = nullptr;
		m_Window = nullptr;
		m_Camera2D = nullptr;
		m_Camera3D = nullptr;
		m_RootScene = nullptr;

		Log::Success("Engine - Released");
	}

	cEngine::~cEngine()
	{
		m_EngineInst = nullptr;
	}

	void cEngine::SetRootScene(cScene* pScene)
	{
		m_RootScene = pScene;
	}
}