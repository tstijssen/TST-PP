#include "SceneObject.h"

namespace Tijss
{
	cSceneObject::cSceneObject()
	{
		m_Visible = true;
		m_Ignored = false;
		m_Changed = true;
	}

	void cSceneObject::SetVisible(bool value)
	{
		m_Visible = value;
	}

	void cSceneObject::SetIgnoreUpdate(bool value)
	{
		m_Ignored = value;
	}

	void cSceneObject::SetChanged(bool value)
	{
		m_Changed = value;
	}


	bool cSceneObject::IsVisible()
	{
		return m_Visible;
	}

	bool cSceneObject::IsIgnoreUpdate()
	{
		return m_Ignored;
	}

	bool cSceneObject::IsChanged()
	{
		return m_Changed;
	}
}