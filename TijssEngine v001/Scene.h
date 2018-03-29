#pragma once
#include "_DllExport.h"

#include "SceneObject.h"
#include "Logger.h"

#include <vector>

namespace Tijss
{

	class TIJSSEN_DECLSPEC cScene : public cSceneObject
	{
	public:
		cScene();
		~cScene();

		void AttachChild(cSceneObject *obj);
		void DetachChild(cSceneObject *obj);
		void DetachAllChilds();

		void On();
		void Off();

		virtual void Draw();
		virtual void Update();

	protected:

		vector <cSceneObject*> m_ChildObjects;

		bool m_Visible;
		bool m_Ignored;
	};

}