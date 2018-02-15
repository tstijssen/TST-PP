#pragma once

#include "Defines.h"

namespace ent
{
	class CEntity;

	class CEntityComponent
	{
	public:
		CEntityComponent
		(const string& type, TEntityUID UID, CEntity* entity)
		{
			m_Type = type;
			m_UID = UID;
			m_Entity = entity;
		}

		// Getters
		const string& GetType()
		{
			return m_Type;
		}
		TEntityUID GetUID()
		{
			return m_UID;
		}
		CEntity* Entity()
		{
			return m_Entity;
		}
	};
}