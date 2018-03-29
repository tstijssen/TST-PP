#include "Scene.h"

namespace Tijss
{
	cScene::cScene()
	{
		On();
	}

	cScene::~cScene()
	{

	}

	void cScene::On()
	{
		m_Visible = true;
		m_Ignored = false;
	}

	void cScene::Off()
	{
		m_Visible = false;
		m_Ignored = true;
	}

	void cScene::AttachChild(cSceneObject *obj)
	{
		if (!obj)
			Log::Error("Scene::AttachChild: obj - null");
		m_ChildObjects.push_back(obj);
	}

	void cScene::DetachChild(cSceneObject *obj)
	{
		if (!obj)
			Log::Error("Scene::AttachChild: obj - null");

		for (int i = 0; i< m_ChildObjects.size(); i++)
		{
			if (m_ChildObjects.at(i) == obj)
			{
				m_ChildObjects.erase(m_ChildObjects.begin() + i);
				break;
			}
		}
	}

	void cScene::DetachAllChilds()
	{
		m_ChildObjects.clear();
	}


	void cScene::Draw()
	{
		if (m_Visible)
		{
			int NumberOfObjects = m_ChildObjects.size();

			cSceneObject *pObject;

			for (int i = 0; i<NumberOfObjects; i++)
			{
				pObject = m_ChildObjects.at(i);
				if (pObject->IsVisible())
				{
					pObject->Draw();
				}
			}
		}
	}

	void cScene::Update()
	{
		if (!m_Ignored)
		{
			int NumberOfObjects = m_ChildObjects.size();
			cSceneObject *pObject;

			for (int i = 0; i<NumberOfObjects; i++)
			{
				pObject = m_ChildObjects.at(i);

				if (!pObject->IsIgnoreUpdate())
				{
					m_ChildObjects.at(i)->Update();
				}
			}
		}
	}



}