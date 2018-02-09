#pragma once

// includes
#include <string>
#include "Bitmap.h"
#include <map>
using namespace std;


namespace ent
{
	class CEntityTemplate
	{
	public:
		// base constructor for all entities
		CEntityTemplate(const string& type, const string& name, const string& spriteFileName)
		{
			m_Type = type;
			m_Name = name;

			// load sprite
		}

		virtual ~CEntityTemplate() {};

		//	Getters

		const string& GetType()
		{
			return m_Type;
		}

		const string& GetName()
		{
			return m_Name;
		}

		BitmapClass* const Mesh()
		{
			return m_Sprite.get();
		}

	private:
		// disable copy and assignment
		CEntityTemplate(const CEntityTemplate&);
		CEntityTemplate& operator=(const CEntityTemplate&);

		// entity variables
		string m_Type;
		string m_Name;

		unique_ptr<BitmapClass> m_Sprite;
	};


	// basic entity class
	class CEntity
	{
	public:
		CEntity();

		virtual ~CEntity();

		Vector3& Position()
		{
			return m_Pos;
		}

		//  Component Code

		// Add a component
		void AddComponent(CEntityComponent* component);

		// Get the component with the given UID
		CEntityComponent* GetComponent(TEntityUID UID);

		// Get the component with the given type from this entity, or 0 if no such component exists
		// Will only return the first component of the given type
		CEntityComponent* GetComponent(const string& type);

		// Remove the component with the given UID from this entity, returns true if component was found and removed
		bool RemoveComponent(TEntityUID UID);

		// Remove the component with the given type from this entity, returns true if component was found and removed
		bool RemoveComponent(const string& type);

		// Remove all components from this entity
		void RemoveAllComponents();

		// Return false if the entity is to be destroyed
		bool Update(float updateTime);

		// Render the entity from the given camera
		void Render(CCamera* camera);

	private:
		// disable copy and assignment
		CEntity(const CEntity&);
		CEntity& operator=(const CEntity&);
		
		// private variables
		CEntityTemplate* m_Template;

		// Unique identifier and name for the entity
		TEntityUID  m_UID;
		string      m_Name;

		// position of this entity
		Vector3 m_Pos;

		// Map of Components attached to this entity
		map<TEntityUID, CEntityComponent*> m_Components;
	};
}