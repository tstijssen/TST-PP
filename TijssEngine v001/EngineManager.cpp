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
			// error
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
		//m_RootScene = nullptr;

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

		//if (!pEngineOptions.Test())
		//	Log::Error("Engine::Initialize: EngineDescription Failed");

		// Graphics block

		m_GFX = new cGraphics();
		m_GFX->Init(m_Window, pEngineOptions.m_Windowed, pEngineOptions.m_VSync);
		m_Context = m_GFX->GetContext();
		m_Device = m_GFX->GetDevice();

		//m_DefaultShaderBase.LoadShaders();

		//Log::Success("Engine::Initialized.");
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
				//Log::Error("Engine::GetActive2DCamera - Camera2D is null");
			}
		}
		/*else
			Log::Error("Engine::GetActive2DCamera - engine is not created.");*/

		return NULL;
	}



	Camera* Engine::GetActive3DCamera()
	{
		if (Me)
		{
			if (Me->mCamera3D)
			{
				return Me->mCamera3D;
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

	ID3D11Device* Engine::GetDevice()
	{
		if (Me)
		{
			if (Me->Device)
			{
				return Me->Device;
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



	ID3D11DeviceContext* Engine::GetContext()
	{
		if (Me)
		{
			if (Me->Context)
			{
				return Me->Context;
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



	void Engine::SetActiveCamera2D(Camera *inCamera)
	{
		mCamera2D = inCamera;
	}


	void Engine::SetActiveCamera3D(Camera *inCamera)
	{
		mCamera3D = inCamera;
	}


	void Engine::Draw()
	{
		if (mCamera2D)
			mCamera2D->Update();

		if (mCamera3D)
			mCamera3D->Update();

		if (mRootScene)
			mRootScene->Draw();
	}


	void Engine::Update()
	{
		if (mRootScene)
			mRootScene->Update();
	}


	void Engine::Release()
	{

		mDefaultShaderBase.ReleaseShaders();

		_RELEASE_DELETE(mGraphics);

		Context = nullptr;
		Device = nullptr;
		mWindow = nullptr;
		mCamera2D = nullptr;
		mCamera3D = nullptr;
		mRootScene = nullptr;

		Log::Success("Engine - Released");
	}

	Engine::~Engine()
	{
		Me = nullptr;
	}

	void Engine::SetRootScene(Scene* pScene)
	{
		mRootScene = pScene;
	}

}