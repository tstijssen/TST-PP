#pragma once
#include <map>
#include <vector>
using namespace std;

#include "Entity.h"

namespace ent
{
	class EntityManager
	{
	public:

		// Constructor
		EntityManager();

		// Destructor
		~EntityManager();
	private:
		EntityManager(const EntityManager&);
		EntityManager& operator=(const EntityManager&);

	public:
		CEntityTemplate * EntityManager::CreateTemplate
		(
			const string& type,
			const string& name,
			const string& mesh
		);

		// Destroy the given template (name) - returns true if the template existed and was destroyed
		bool DestroyTemplate(const string& name);

		// Destroy all templates held by the manager
		void DestroyAllTemplates();
	};
}