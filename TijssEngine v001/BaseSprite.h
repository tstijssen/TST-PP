#pragma once
#include "_DLLExport.h"

#include "EngineDefines.h"
#include "TypeDefines.h"

namespace Tijss
{
	class TIJSSEN_DECLSPEC cBaseSprite
	{
	public:
		cBaseSprite();

		void SetRotation(float32 rotation);
		void SetPosition(float32 x, float32 y);
		void SetFrame(int32 frame);
		void SetVisible(bool visible);
		void SetScale(float32 scale);
		void SetColour(sColour colour);

		bool m_Visible;
		int32 m_Frame;
		
		sFloat3 m_Position;
		float32 m_Scale;
		float32 m_Rotation;
		sColour m_Colour;
	};
}