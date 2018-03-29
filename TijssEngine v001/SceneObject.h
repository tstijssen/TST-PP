#pragma once
#include "_DllExport.h"

namespace Tijss
{

	class TIJSSEN_DECLSPEC cSceneObject
	{
	public:
		cSceneObject();

		void SetVisible(bool value);
		void SetIgnoreUpdate(bool value);
		void SetChanged(bool value);

		bool IsChanged();
		bool IsVisible();
		bool IsIgnoreUpdate();

		virtual void Draw() = 0;
		virtual void Update() = 0;
	protected:
		bool m_Changed;
		bool m_Visible;
		bool m_Ignored;
	};

}