#include "BaseSprite.h"

namespace Tijss
{
	cBaseSprite::cBaseSprite()
	{
		m_Visible = true;
		m_Frame = 0;

		m_Position = { 0, 0, 0 };
		m_Colour = { 1,1,1,1 };

		m_Scale = 1.0f;
		m_Rotation = 0.0f;
	}

	void cBaseSprite::SetPosition(float32 x, float32 y)
	{
		m_Position.x = x;
		m_Position.y = y;
		m_Position.z = 0;	//necessary, maybe should be float2 instead of 3
	}

	void cBaseSprite::SetRotation(float32 rotation)
	{
		m_Rotation = rotation;
	}

	void cBaseSprite::SetScale(float32 scale)
	{
		m_Scale = scale;
	}

	void cBaseSprite::SetFrame(int32 frame)
	{
		m_Frame = frame;
	}

	void cBaseSprite::SetVisible(bool visible)
	{
		m_Visible = visible;
	}

	void cBaseSprite::SetColour(sColour colour)
	{
		m_Colour = colour;
	}
}